#!/bin/bash

# Script for 54-nodes.csv
CSV_FILE="./54-nodes.csv"
NUM_SAMPLES=1488881
NUM_EXPERIMENTS=10

for NUM_THREADS in 1 2 4 8 16 32
do
  ./main $CSV_FILE $NUM_SAMPLES $NUM_THREADS $NUM_EXPERIMENTS
done
