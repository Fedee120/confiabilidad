#!/bin/bash
#SBATCH --job-name=montecarlo_fede
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=30
#SBATCH --mem=2048
#SBATCH --time=00:02:00
#SBATCH --tmp=9G
#SBATCH --partition=normal
#SBATCH --qos=normal
#SBATCH --mail-type=ALL
#SBATCH --mail-user=federico.gil@fing.edu.uy

source /etc/profile.d/modules.sh

cd ~/confiablidad/obj
./main ./54-nodes.csv 1000000 30