#!/bin/sh

rm *.csv

#PROBLEM 2:

#ADJUSTING NUMBER OF EPOCHS
echo "running problem2 epochs"
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 6 10 6 1 -e 1000 -lr 1.0 > output1.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 6 10 6 1 -e 2000 -lr 1.0 > output2.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 6 10 6 1 -e 4000 -lr 1.0 > output3.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 6 10 6 1 -e 10000 -lr 1.0 > output4.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 6 10 6 1 -e 50000 -lr 1.0 > output5.csv
#***************************************************************************************************************

#ADJUSTING LEARNING RATE
echo "running problem2 learning rate"
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 6 10 6 1 -e 10000 -lr .25 > output6.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 6 10 6 1 -e 10000 -lr 1.0 > output7.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 6 10 6 1 -e 10000 -lr 2.5 > output8.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 6 10 6 1 -e 10000 -lr 5.0 > output9.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 6 10 6 1 -e 10000 -lr 25 > output10.csv
#***************************************************************************************************************

#ADJUSTING NUMBER OF LAYERS
echo "running problem2 layers"
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 3 -n 3 22 1 -e 10000 -lr 1.0 > output11.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 4 -n 3 11 11 1 -e 10000 -lr 1.0 > output12.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 6 10 6 1 -e 10000 -lr 1.0 > output13.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 6 -n 3 6 5 5 6 1 -e 10000 -lr 1.0 > output14.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 7 -n 3 3 3 10 3 3 1 -e 10000 -lr 1.0 > output15.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 8 -n 3 3 3 5 5 3 3 1 -e 10000 -lr 1.0 > output16.csv
#***************************************************************************************************************

#ADJUSTING NUMBER OF NODES
echo "running problem2 nodes"
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 3 3 3 1 -e 10000 -lr 1.0 > output17.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 4 8 4 1 -e 10000 -lr 1.0 > output18.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 6 6 6 1 -e 10000 -lr 1.0 > output19.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 6 12 6 1 -e 10000 -lr 1.0 > output20.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 6 3 6 1 -e 10000 -lr 1.0 > output21.csv
./backPropogation2 -f training2.txt testing2.txt validation2.txt -l 5 -n 3 10 40 10 1 -e 10000 -lr 1.0 > output22.csv

mv *.csv problem2/
