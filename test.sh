#! /bin/sh

rm *.csv

#TESTING DATA AND, OR, XOR
echo "running test cases"
./backPropogation -f train_and.txt train_and.txt train_and.txt -l 5 -n 2 4 8 4 1 -e 10000 -lr 2.5 > test1.csv
./backPropogation -f train_or.txt train_or.txt train_or.txt -l 5 -n 2 4 8 4 1 -e 10000 -lr 2.5 > test2.csv
./backPropogation -f train_xor.txt train_xor.txt train_xor.txt -l 5 -n 2 4 8 4 1 -e 10000 -lr 2.5 > test3.csv
#***************************************************************************************************************

mv *.csv testing/

#ADJUSTING NUMBER OF EPOCHS
echo "running problem1 epochs"
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 6 10 6 1 -e 1000 -lr 1.0 > output1.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 6 10 6 1 -e 2000 -lr 1.0 > output2.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 6 10 6 1 -e 4000 -lr 1.0 > output3.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 6 10 6 1 -e 10000 -lr 1.0 > output4.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 6 10 6 1 -e 50000 -lr 1.0 > output5.csv
#***************************************************************************************************************

#ADJUSTING LEARNING RATE
echo "running problem1 learning rate"
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 6 10 6 1 -e 10000 -lr .25 > output6.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 6 10 6 1 -e 10000 -lr 1.0 > output7.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 6 10 6 1 -e 10000 -lr 2.5 > output8.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 6 10 6 1 -e 10000 -lr 5.0 > outpu9.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 6 10 6 1 -e 10000 -lr 25 > output10.csv
#***************************************************************************************************************

#ADJUSTING NUMBER OF LAYERS
echo "running problem1 layers"
./backPropogation -f training1.txt testing1.txt validation1.txt -l 3 -n 2 22 1 -e 10000 -lr 1.0 > output11.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 4 -n 2 11 11 1 -e 10000 -lr 1.0 > output12.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 6 10 6 1 -e 10000 -lr 1.0 > output13.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 6 -n 2 6 5 5 6 1 -e 10000 -lr 1.0 > output14.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 7 -n 2 3 3 10 3 3 1 -e 10000 -lr 1.0 > output15.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 8 -n 2 3 3 5 5 3 3 1 -e 10000 -lr 1.0 > output16.csv
#***************************************************************************************************************

#ADJUSTING NUMBER OF NODES
echo "running problem1 nodes"
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 3 3 3 1 -e 10000 -lr 1.0 > output17.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 4 8 4 1 -e 10000 -lr 1.0 > outpu18.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 6 6 6 1 -e 10000 -lr 1.0 > output19.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 6 12 6 1 -e 10000 -lr 1.0 > output20.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 6 3 6 1 -e 10000 -lr 1.0 > output21.csv
./backPropogation -f training1.txt testing1.txt validation1.txt -l 5 -n 2 10 40 10 1 -e 10000 -lr 1.0 > output22.csv
#*******************************************************************************************************************

mv *.csv problem1/










