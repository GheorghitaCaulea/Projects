#! /bin/bash
make
echo "Pentru 1 THREAD"
export OMP_NUM_THREADS=1
./parallel_snake big_input output 20000
echo "Pentru 2 THREAD-uri"
export OMP_NUM_THREADS=2
./parallel_snake big_input output 20000
echo "Pentru 4 THREAD-uri"
export OMP_NUM_THREADS=4
./parallel_snake big_input output 20000
echo "Pentru 6 THREAD-uri"
export OMP_NUM_THREADS=6
./parallel_snake big_input output 20000
echo "Pentru 8 THREAD-uri"
export OMP_NUM_THREADS=8
./parallel_snake big_input output 20000
