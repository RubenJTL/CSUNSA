#!/bin/sh
#PBS -N test_R //nombre tarea
#PBS -l nodes=1:ppn=1 //cantidad de nodos y núcleos
#PBS -M rtorresli@unsa.edu.pe
#PBS -o test.out
cd $PBS_O_WORKDIR
#Comandos utilizados para ejecutar su programa
/opt/shared/R-3.4.2/bin/R CMD BATCH te.serial.R
/opt/shared/openmpi-2.0.1/bin/mpicc
/opt/shared/gcc_5_4_0/bin/gcc

SH COM
#!/bin/sh
#PBS -N test_MPI //nombre tarea
#PBS -l nodes=1:ppn=1 //cantidad de nodos y núcleos
#PBS -M rtorresli@unsa.edu.pe
#PBS -o test.out
NPROC=`wc -l < $PBS_NODEFILE`
source /opt/shared/openmpi-2.0.1/environment.sh 
cd $PBS_O_WORKDIR
#Comandos utilizados para ejecutar su programa
mpicc mpi_hello.c -o mpi.out

SH RUN
#PBS -N ej6
#PBS -l nodes=2:ppn=3
NPROC=`wc -l < $PBS_NODEFILE`
source /opt/shared/openmpi-2.0.1/environment.sh
source /opt/shared/gcc_5_4_0/environmen.sh
cd $PBS_O_WORKDIR
mpiexec -np $NPROC mpi.out 
mpiexec -np 2 mpi.out
