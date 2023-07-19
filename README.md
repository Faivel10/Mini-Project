# Mini-Project
Mini Project in stochastic optimization.
## The problem:
We have passengers boarding on a plane. Each passenger has x and y values - where x is it's location in the line and y is it's seat.
In addition, each passenger has a weight - that means how low he is - everyone start at value 1.
We also define the slowest line as the longest line with the most weights in it.
Our mission is to check how many passenger weights can be increased to 2, while not surpassing the slowest line existing before the added weights.
## How To Run
This program was built using WSL with Ubuntu 22 distro.
To run the project, you first need to have the following packages installed
```bash
build-essential with g++.
python3
pip
xlrd - version 1.2.0 only
matplotlib
```
xlrd version 1.2.0 can be installed by running:
```bash
pip install xlrd==1.2.0
```
After installing the required packages, just run:
```bash
./run.sh
```
## How It Works:
* reader.py file is responsible to read the xlsx input file and parse the points from it to a text file that the main program can read.
* main.cpp takes the parsed file, calculates the heaviest paths and the points that will have their weights increased on all the parsed files.
* Main then outputs the points that will have their weights increased for each sheet to a parsed text file.
* Writer.py will convert the parsed points to csv file.

## Where is the output
When done, the output will be in output folder with each output file named with a "parsed-" prefix and then the original sheet title.

## Testing:
You can use add points to the plot.py file, which will show you a plot of the lines, while increasing lines only are connected.
You can then find manually the slowest-heviest line, the points where weight can be increased and compare it to the program output. 
  
