# Mini-Project
Mini Project in stochastic optimization.
## How To Run
To run the project, you first need to have the following packages installed
```bash
build-essential
python3
pip
xlrd - version 1.2.0 only - can be installed using: ```bash pip install xlrd==1.2.0 ```
```
After installing the required packages, just run:
```bash
./run.sh
```
## How It Works:
* reader.py file is responsible to read the xlxs input file and parse the points from it to a text file that the main program can read.
* After that that, main.cpp takes the parsed file, calculates the heaviest paths and the points that will have their weights increased on all the parsed files.
* Main then outputs the points that will have their weights increased for each sheet to a non-csv text file.
* Writer.py will convert the parsed points to csv file.

## Where is the output
When done, the output will be in output folder with each output file named with a "parsed-" prefix and then the original sheet title.

  
