#!/bin/bash

# Script for grafo.csv
CSV_FILE="./grafo.csv"
NUM_SAMPLES=1488881
NUM_EXPERIMENTS=10

for NUM_THREADS in 1 2 4 8 16 32
do
  ./main $CSV_FILE $NUM_SAMPLES $NUM_THREADS $NUM_EXPERIMENTS
done
