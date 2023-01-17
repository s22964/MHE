#!/bin/bash
#Run this in terminal
#+ Command to compile c++ program. here i used common one
g++ -pedantic-errors -Wall -c funkcjeImpl.cpp
g++ -o program main.cpp funkcjeImpl.o
exit 0