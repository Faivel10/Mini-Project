# Mini-Project
Mini Project in stochastic optimization.
## How To Run
To run the project, you first need to have the following packages installed
```bash
build-essential
python3
pip
xlrd - can be installed using pip
```
After installing the required packages, just run:
```bash
./run.sh
```
## How It Works:
* reader.py file is responsible to read the xlxs input file and parse the points from it to a text file.
* After that that, main.cpp takes the parsed file, and does all the calculations.
* Main then outputs the points in a parsed manner.
* Writer will write convert the parsed points to csv.

## Where is the output
When done, the output will be in output-csv folder with each output file named by the location of the sheet in the original file 
- from 1 to 20.

  
