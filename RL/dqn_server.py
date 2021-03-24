import keras
from keras.models import Sequential
from keras.layers import Dense, Activation, Flatten, Convolution2D, Permute
from keras.optimizers import Adam
import keras.backend as K

from rl.agents.dqn import DQNAgent
from rl.policy import LinearAnnealedPolicy, BoltzmannQPolicy, EpsGreedyQPolicy
from rl.memory import SequentialMemory
from rl.callbacks import FileLogger, ModelIntervalCheckpoint

from gym import Env, spaces

import os
import json
import numpy as np
from copy import deepcopy

from multiprocessing import Process
import signal
import sys

import time
import eventlet
import socketio


class AgentDQN:
    def __init__(self, nb_actions, nb_space_dims, observation_low, observation_high, window_length, log_interval, filename):
        self.nb_actions = nb_actions
        self.nb_space_dims = nb_space_dims
        self.observation_low = observation_low
        self.observation_high = observation_high
        self.window_length = window_length  # 连续多少观测状态作为神经网络的输入
        self.log_interval = log_interval
        self.filename = filename

        self.env = Env()
        self.env.action_space = spaces.Discrete(self.nb_actions)
        self.env.observation_space = spaces.Box(low=np.ones(self.nb_space_dims) * self.observation_low,
                                                high=np.ones(self.nb_space_dims) * self.observation_high,
                                                dtype=np.float32)

        self.logging = []

        self.model = self.generate_model_fully_connected()
        self.policy = self.generate_policy()
        self.memory = self.generate_memory()
        self.agent = self.generate_agent()

        self.observation_last = None
        self.action = None
        self.observation = None
        self.reward = None
        self.done = None
        self.info = None
        self.metrics = None

        self.agent.training = True
        self.agent.step = 0
        self.agent.episode = 0

    # 全连接网络
    def generate_model_fully_connected(self):
        model = Sequential()
        model.add(Flatten(input_shape=(self.window_length,) + self.env.observation_space.shape))
        model.add(Dense(32))
        model.add(Activation('relu'))
        model.add(Dense(32))
        model.add(Activation('relu'))
        model.add(Dense(32))
        model.add(Activation('relu'))
        model.add(Dense(self.env.action_space.n))
        model.add(Activation('linear'))
        # 画模型结构图 (使用 graphviz)
        # keras.utils.plot_model(model, to_file='.\\model.png', show_shapes=False, show_layer_names=True, rankdir='TB', expand_nested=False, dpi=96)
        return model

    def generate_policy(self):
        # return LinearAnnealedPolicy(EpsGreedyQPolicy(), attr='eps', value_max=.05, value_min=.05, value_test=.0,
                                # nb_steps=1000000000)
        return LinearAnnealedPolicy(EpsGreedyQPolicy(), attr='eps', value_max=.05, value_min=.05, value_test=.0,
                                    nb_steps=1000000000)

    def generate_memory(self):
        return SequentialMemory(limit=100000, window_length=self.window_length)

    def generate_agent(self):
        agent = DQNAgent(model=self.model, nb_actions=self.env.action_space.n, policy=self.policy, memory=self.memory,
                         processor=None, nb_steps_warmup=10, gamma=.99, target_model_update=1000,
                         train_interval=1, delta_clip=1.)
        agent.compile(Adam(lr=.00025), metrics=['mae'])
        return agent

    def save_logging(self):
        step_log = {
            'step': self.agent.step,
            'episode': self.agent.episode,
            'observation_last': [float(o) for o in self.observation_last],
            'action': self.action,
            'observation': [float(o) for o in self.observation],
            'reward': self.reward,
            'reward_mean': np.mean([logging['reward'] for logging in self.logging] + [self.reward]),
            'done': self.done,
            'info': self.info
        }
        self.logging.append(step_log)
        self.agent.step += 1

        # if self.agent.step%self.log_interval == 0:
        #     with open("record_"+self.filename+".json", "w") as f:
        #         json.dump(self.logging, f)

    def forward(self):
        self.action = int(self.agent.forward(self.observation_last))

    def backward(self):
        self.metrics = self.agent.backward(self.reward, terminal=self.done)
        self.save_logging()

    def save_model(self):
        self.model.save_weights("model_"+self.filename+"_"+str(self.agent.episode)+".h5")

    def load_model(self):
        self.model.load_weights("model_"+self.filename+"_2.h5")


########################################################################################################################

#overview platform(interaction,3D) result1 result2
agent = AgentDQN(nb_actions=2, nb_space_dims=1, observation_low=0, observation_high=10000, window_length=1, log_interval=100, filename="00")
agent.load_model()

########################################################################################################################

def start_server(port):
    sio = socketio.Server()
    app = socketio.WSGIApp(sio, static_files={
        '/': {'content_type': 'text/html', 'filename': 'static/index.html'}
    })

    @sio.event
    def connect(sid, environ):
        print('connect ', sid)

    @sio.on('reset')  # 接受到客户端 reset 指令, 接受初始 observation, 发送初始 action
    def reset(sid, data):
        print("reset")
        agent.load_model()
        # time.sleep(0.01)
        agent.observation_last = np.array(data["observation"])
        agent.action = None
        agent.observation = None
        agent.reward = None
        agent.done = None
        agent.info = None
        agent.metrics = None
        agent.forward()
        sio.emit('act', {"action": agent.action, "observation_last": [float(o) for o in agent.observation_last], "logging": agent.logging[-1] if len(agent.logging) > 0 else None})

    @sio.on('step')  # 接受到客户端 step 指令, 接受 observation, reward, done, info, 发送 action 或重启指令
    def step(sid, data):
        print("step")
        # time.sleep(0.01)
        agent.observation, agent.reward, agent.done, agent.info = np.array(data["observation"]), data["reward"], data["done"], data["info"]
        agent.backward()

        if agent.done:
            agent.agent.episode += 1
            agent.action = -1
            # agent.save_model()
        else:
            agent.forward()

        agent.observation_last = agent.observation
        sio.emit('act', {"action": agent.action, "observation_last": [float(o) for o in agent.observation_last], "logging": agent.logging[-1]})

    @sio.event
    def disconnect(sid):
        print('disconnect ', sid)

    print('启动服务器', port)
    eventlet.wsgi.server(eventlet.listen(('', port)), app)


if __name__ == '__main__':
    p = Process(target=start_server, args=(2333,))
    p.daemon = True
    p.start()
    # p.terminate()
    print('主进程启动')


    def signal_handler(signal, frame):
        print('关闭从进程')
        # p.terminate()
        print('主进程退出')
        sys.exit(0)


    signal.signal(signal.SIGINT, signal_handler)
    while True:
        pass
