# Multi-Body Systems Benchmark in OpenSim (MBS-BOS) 

MBS-BOS package is a set of programs that implement the Multi-Body Systems (MBS) Benchmark [[1]] using the OpenSim APIs [[2]]. 

The first objective is to compare output from these simulations with the validated reference solutions available in the MBS Benchmark package.
The second objective is to provide C++ solutions for common problems that can be found in the implementation of simulations of multi-body systems.

### Latest Version
MBS-BOS is an open project, released under GNU General Public License and hosted in GitHub: 

> https://github.com/RehabEngGroup/MBSbenchmarksInOpenSim

### Documentation
Descriptions of the five benchmark problems are available as PDF files in the *docs* directory available with the code.  

### Requirements
To compile MBS-BOS you need the following software:

1. OpenSim v. 3.2 [download][2]

2. CMake [download][3]

Windows users also need to install:

1. Visual Studio 

###MBS-BOS in Linux

####Configure OPENSIM_HOME environment variable

The successful compilation of MBS-BOS requires OpenSim libraries. If you installed OpenSim in a custom folder, please set the OPENSIM_HOME environment variable as follow:

1.Open a terminal and type

    gedit .bashrc
    
2.Add the following line at the end of the file:

    export OPENSIM_HOME = yourOpensimInstallDirectory

3.Save the file, close gedit, and close the terminal. 

4.Open a new terminal and write the following line. It should the OpenSim installation directory previously specified.

    echo $OPENSIM_HOME

####MBS-BOS Installation

1.Open a terminal

2.Change your working directory to where you want to work with MBS-BOS

3.Unzip the archive of MBS-BOS (available [here][5]) or download the software from the GitHub repository:

    git clone https://github.com/RehabEngGroup/MBSbenchmarksInOpenSim.git

4.Create a build directory inside the MBS-BOS folder

    mkdir build
	
5.Change your directory to build and run cmake:

    cd build
    cmake ..

6.Compile MBS-BOS programs:

    make

7.If everything went fine, the executable are available in the *build/bin* directory

####Execution

The execution of all the benchmark problems is composed of two steps

1. creation of the model  

2. execution of the simulation.  

#####Example: 

Suppose you want to execute the A01 benchmark problem: Simple Pendulum. The following are the steps to follow.

First you create the model:

    cd yourFolder/build/bin
    ./SimplePendulumCreateModel ../data/A01-SimplePendulum

The output is the OpenSim model of the Simple Pendulum, stored in the directory:

    yourFolder/build/data/A01-SimplePendulum

Second you run the simulation: 

    ./SimplePendulumSimulate ../data/A01-SimplePendulum

After the successful execution of the simulation, the output data files are available in:  

    yourFolder/build/data/A01-SimplePendulum/SimulationResults


###MBS-BOS in Windows

The successful compilation of MBS-BOS requires OpenSim libraries. If you installed OpenSim in a custom folder, please set the OPENSIM_HOME environment variable through the Windows Control Panel.

####MBS-BOS Installation

1.Change your working directory to where you want to work with MBS-BOS

2.Unzip the archive of MBS-BOS or download the software from the GitHub repository using the Git terminal:

    git clone https://github.com/RehabEngGroup/MBSbenchmarksInOpenSim.git
    
3.Create a build directory inside the MBS-BOS folder

4.Open Cmake GUI, select yours source and build directories and the Visual Studio version you are planning to use. If you have downloaded OpenSim binary you MUST select in Release as CompilationMode, Debug is not going to work.

5.Click on Generate

6.Open Visual Studio and import the project  MBSBenchmarks.stl created at the previous step
 
7.Build the project

####Execution

Open a new Command Prompt, then change your working directory and move to the folder where the project was built. Depending on the choice made during compilation the final directory will be slightly different, i.e. change CompilationMode to Debug or Release:

    cd yourBuildDirectory\bin\CompilationMode\
    
Then the execution of all the benchmark problems is composed of two steps:

1. creation of the model  

2. execution of the simulation.  

#####Example:

Suppose you want to execute the A01 benchmark problem: Simple Pendulum. The following are the steps to follow.

    
First you create the model:

    simplePendulumCreateModel.exe ..\..\data\A01-SimplePendulum

The output is the OpenSim model of the Simple Pendulum, stored in the directory:

    yourFolder\build\data\A01-SimplePendulum

Second you run the simulation: 

    SimplePendulumSimulate.exe ..\..\data\A01-SimplePendulum

After the successful execution of the simulation, the output data files are available in:  

    yourFolder\build\data\A01-SimplePendulum\SimulationResults


### Licensing
Please see the file called license.

    Multi-Body Systems Benchmark in OpenSim (MBS-BOS) Copyright (C) 2013-2014 Luca Tagliapietra, Michele Vivian, and Monica Reggiani.
    
    MBS-BOS is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
    
    MBS-BOS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with MBS-BOS. If not, see <http://www.gnu.org/licenses/>.
    
    The authors may be contacted via: tagliapietra@gest.unipd.it

### Contacts

- MBS-BOS bug report? Send an email to <tagliapietra@gest.unipd.it>

- Help with MBS-BOS? Send an email to <tagliapietra@gest.unipd.it> or <vivian@gest.unipd.it>

- Developer access to MBS-BOS repository? Send an email to <reg-info@gest.unipd.it>

### Links
Need more information? Check the following links:

- MBS Benchmark [click here][1]

- OpenSim [click here][2]

- CMake [click here][3]

- GitHub [click here][4]
 

[1]: http://lim.ii.udc.es/mbsbenchmark/
[2]: http://opensim.stanford.edu
[3]: http://cmake.org
[4]: http://github.com
[5]: https://github.com/RehabEngGroup/MBSbenchmarksInOpenSim
