#! /bin/bash

python3 ./reader.py

g++ ./main.cpp -o ./main

./main

python3 ./writer.py