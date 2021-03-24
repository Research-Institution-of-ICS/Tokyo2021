# Tokyo2021
Agent-based simulation of the pandemic during and after the Tokyo Olympic Games in 2021.

![1](./Images/Fig1.jpg)

## Unreal Engine Project

![1](./Images/Tokyo.jpg)

A video glancing this digital twin simulation of the entire Tokyo Olympic Games amid pandemic transmission is available at https://drive.google.com/file/d/1DRW0PJrI8OWlu-NYoM3ylsb4_z7s8XAZ/view?usp=sharing.
### Requirements

* Unreal Engine 4.26.x
* Visual Studio Community 2019

### Installation

Clone and open **ToolMan** in UnrealEngineProject. Then download and unzip `Compressed data for UE4 Project` in `Releases` to the root directory of **ToolMan**.

To ensure the successful compilation and operation of the project, you have to get code plugins `Socket.IO Client`  `Multi Task Pro` and asset packages `Automotive Materials` `Cel-Shader & Outline` `Cyberpunk FX Pack 2 - Neon Panels and Screens` `GOOD SKY` `Stylized Colorful Nature Pack` `Twinmotion Materials for Unreal Engine` `Water Planes`  `POLYGON - City Pack` `POLYGON - Prototype Pack` `Simple Port` from the Unreal Engine Marketplace. 

Please place `Automotive Materials` `Cel-Shader & Outline` `Cyberpunk FX Pack 2 - Neon Panels and Screens` `GOOD SKY` `Stylized Colorful Nature Pack` `Twinmotion Materials for Unreal Engine` `Water Planes` in the **Content** directory of **ToolMan**, and place `POLYGON - City Pack` `POLYGON - Prototype Pack` `Simple Port` in the **Resources** directory of **Content**.

Use Visual Studio Community 2019 to build the _.sln_ file.

### Usage

The file *FileName.json* in **Data** describes the scenario configuration file required for the simulation and the output result file:
<pre>
<code>["Data/Person0_main.json", "Data/Result0_test.json"]</code>
</pre>

Modify *"Data/Person0_main.json"* to run simulations of different scenarios.

Open *ToolMan.uproject* to run the agent-based simulation.


## Dynamic Policies Training & Testing
### Requirements

* Python 3.7

### Installation

Use pip to install `tensorflow` `gym` `keras-rl` and `python-socketio`.

### Usage

Modify paths of UE4Editor.exe and ToolMan.uproject in *RL/main.py*:

<pre>
<code>child = subprocess.Popen(["C:/Program Files/Epic Games/UE_4.26/Engine/Binaries/Win64/UE4Editor.exe", "***/ToolMan/ToolMan.uproject", "-game", "-windowed"])</code>
</pre>

Run *RL/main.py* to start the UE4 project.

Run *RL/dqn_server.py* to establish socket communication between the Python neural network and the UE4 game environment.

## Pandemic Transmission Aftermath
### Requirements

* MATLAB
### Usage

Take the default scene as an example, run *main.m* to get the evolution process data of infectious diseases. The **result** folder contains the data obtained from the experiment, including the sensitivity analysis and the final results of the different strategies.

Sensitivity analysis includes sensitivity analysis of some parameters such as *R0* and *gamma*. The specific procedures are *R0_gamma.m* and *beta_test*.

Data and programs for ploting with python are in **python_COVID19**, and codes for ploting with MATLAB are in **plot function**.

# Citing

If you use our work, you can cite: 
<cite>
Digital twin simulation and controllability of COVID-19 transmission dynamics amid and after Tokyo Olympic Games
</cite>


