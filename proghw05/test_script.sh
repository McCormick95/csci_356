#!/bin/bash

make clean all

# Test input
INPUT="1 0 12 5
2 0 9 5
3 3 6 6
4 7 4 7
0 0 0"

# Run FCFS
echo "$INPUT" | ./scheduler FCFS > fcfs_output.txt

# Run PP
echo "$INPUT" | ./scheduler PP > pp_output.txt

echo "Output files created: fcfs_output.txt and pp_output.txt"