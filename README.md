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


## Dynamic Policies Training
### Requirements

* Python 3.7
## Pandemic Transmission Aftermath
### Requirements

* MATLAB
### Usage
以默认场景为例，运行*main.m*可以得到默认场景下传染病的演化过程数据。**result**文件夹里面是实验所得的数据，包括敏感性分析和其中不同的策略最后所得的结果。

敏感性分析包括*R0*和*gamma*等一些参数的敏感性分析，具体程序为*R0_gamma.m*和*beta_test*等一些程序。

**python_COVID19**是用python进行画图的一些数据和程序，**plot function**是使用MATLAB进行画图的一些代码。




