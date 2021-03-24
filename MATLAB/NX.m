%%% 全球网络传染病的演变过程 1 年

clear,clc;
%无并行计算启动


%采用绝对人数
%%注意：本程序中航空时间均认为有直达航班，实际上可以通过修改F矩阵达到这一点。
%count = 1;
I_peak = [];
%读取一些数据
load('data.mat');
% E表示初始潜伏者人数(认为是疑似病例)
% S 表示初始状态易感人数
% I表示初始状态下感染者人数
% R表示移除者人数 （治愈者+死亡者）
% F表示航空路线花费时间
% w表示人口流动情况

%% 方程参数初始化:

E_change =[2871.97	4043.61	4181.36	4343.76	4446.46	4522.23	4549.84	4544.65	4511.97	4432.74	4325.05	4206.69	4081.37	3963.14	3830.14	3715.11	6308.41	
];
%I = 0.2*round*I;
%E = 0.2*round*E;

n = length(N); %国家数目

Num = sum(N); %人口总数目

delta = 1/7.5; %每个国家潜伏者变成感染者的概率



% 各个国家根据国家医疗水平计算治愈率+死亡率
% gamma(1) = 0.5; %North
% gamma(2) = 0.5; %Equator
% gamma(3) = 0.2+0.05*round; %South
gamma =  ones(234,1)* 1/7;
%gamma(1,2,3) = 0.2+0.05*round;
f = xlsread(strcat(cd,'/country_info.xlsx'),'J2:J235');
%f1 = f3 = 0.55+0.05*round
maxR =xlsread(strcat(cd,'/country_info.xlsx'),'L2:L235');
%maxR1 = 1.1+0.05*round;
phi = xlsread(strcat(cd,'/country_info.xlsx'),'K2:K235');
% beta_plane = 1.2;  %beta_plane = 0.6+0.6*round;
beta_plane = 1.2;

tmax = 382;

beta = zeros(tmax,n);
S_result = [];
I_result = [];
E_result =[];
R_result = [];


beta = zeros(tmax,n);
for i = 1: n
    for t=1:382
        beta(t,i) = gamma(i)*(f(i)*maxR(i)/2*cos(2*pi*(t-phi(i))/365)+maxR(i)-f(i)*maxR(i)/2);
        
    end
end
clear i t;


t = tmax; %进行为期1年的全球网络传播




%%在这里，我们假设，每个国家都是12点起飞，进行结算。不论何时降落，都按24点进行结算。
for p = 1:tmax
    display(p)
    Y = zeros(n,4);  %用来存储每一天的飞机降落人数
    if p<18
        W  = csvread(strcat(cd,'/array/Olympic/array', num2str(p - 1), '.csv'),1, 0);
    else
        W  = csvread(strcat(cd,'/array/year array/array', num2str(p - 18), '.csv'), 1, 0);
    end
    for j = 1:n
        %% j地区先演变12个小时
        y_1 = [S(j), E(j), I(j), R(j)];
        r_1 = [beta(p,j),delta,gamma(j)];
        t_1 = [0 0.5];
        [y_1,N_1] = local2(y_1,r_1,t_1);
        N(j) = N_1;
        
        %% j国家进行起飞出境
        y_2 = y_1;
        N_2 = N(j);
        W_1 = sum(W,2);
        W_2 = W_1(j);                                %出境人口总数
        
        Y_p = W(j,:);  %在飞机上的人口数
        Y_pp = zeros(n, 4);
        % 到不同国家去的四种人口
        for m = 1:n
            Y_pp(m,1) = Y_p(m)*S(j)/N(j);
            Y_pp(m,2) = Y_p(m)*E(j)/N(j);
            Y_pp(m,3) = Y_p(m)*I(j)/N(j);
            Y_pp(m,4) = Y_p(m)*R(j)/N(j);
        end
        % 在j国家进行起飞
        [y_2,N_2] = takeoff(y_2, N_2, W_2);
        N(j) = N_2;
        
        %% j国家进行人口转移，且在飞机上的演变过程
        for m = 1:n
            if m~=j
                y_m = Y_pp(m,:);
                r_2 = [beta_plane,delta];
                if F(j,m)>2
                    t_2 = [0,F(j,m)/24];
                    Y_pp(m,:) = plane(y_m,r_2,t_2);
                end
            end
        end
        Y = Y + Y_pp;
        
        %% j国家再进行演变12小时
        y_3 = y_2;
        r_3 = [beta(p,j),delta,gamma(j)];
        t_3 = [0 0.5];
        [y_3, N_3] = local2(y_3,r_3,t_3);
        N(j) = N_3;
        S(j)= y_3(1);
        E(j) = y_3(2);
        I(j) = y_3(3);
        R(j) =  y_3(4);
        N = S +E + I + R;
        clear y_1  y_2 y_3   W_1 W_2;
    end
    %% 对j国家进行降落操作：
    for m = 1:n
        y = [S(m), E(m), I(m), R(m)];
        N_d = N(m);
        W_m = Y(m,:);
        [y,N_d] = down(y,N_d,W_m);
        N(m) = N_d;
        S(m)=y(1);
        E(m)= y(2);
        I(m) = y(3);
        R(m) =y(4);
        clear W_m N_d
    end
    %东京人口直接转化为治愈者或者死亡
    R(108) = R(108) + I(108);
    I(108) = 0;
    if p<18
        E(108) = E_change(p);
    end
    S_result = [S_result;S'];
    I_result= [I_result;I'];
    E_result = [E_result;E'];
    R_result = [R_result;R'];
end
save(strcat(cd,'/result/NX.mat'), 'I_result','E_result','R_result');

index = max(I_result);
I_peak = [I_peak;index];
save(strcat(cd,'/result/NX_I_peak.mat'), 'I_peak');
% allresult(3*round-2:3*round,:) = O_test';
% round
% end

