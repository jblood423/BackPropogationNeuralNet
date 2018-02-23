/* John M. Blood
CS420 Lab 4 Back Propogation
3/12/2012
***************************/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "args.h"

typedef struct network{
int inputs;
int outputs;
int layers;
float rate;
//weights
float ***l_hidden; //hidden weights;
float *l_output; //output weights;
float **h_bias; //hidden bias;
float *o_bias; //output bias;
//values
float **hv_hidden; //hidden layer h values
float *hv_output; //output layer h values
float **sv_hidden; //hidden layer sigma values
float *sv_output; //output layer sigma values
float **dv_hidden; //hidden layer delta values 
float *dv_output; //output layer delta values
}network;

//FUNCTION PROTOTYPES
//*********************
void usage();
args init_args();
int isCommand(char *);
int verify_coms(args);
float ***init_hweight( float ***, float, int*, int*);
float **init_bweight(float **, float, int*, int);
float *init_oweight( float *, int, int); 
float sigmoid(float, float); //(input, alpha)
float dsigmoid(float, float); //(input, alpha)
void clearVals(network, int *);
network trainNet(network, char *, int *); // (network, filename)
void testNet(network, char *, int *, int); // (network, filename, nodes per layer, epoch)
void evaluateNet(network, char *, int *);
//*********************

int
main( int argc, char *argv[]) {

srand(time(NULL)); 

//*********COMMAND LINE INTERFACE CODE*************
	if(argc < 13){
		usage();
	}
	
int i = 1;
args commands = init_args();

while(i < argc) //maybe do check for garbage input? 
{
	if(strcmp(argv[i], "-l") == 0){
		commands.lv = atoi(argv[i+1]);
		commands.l = 1;	
	}
	if(strcmp(argv[i], "-n") == 0){
		
		commands.nv = (int*)malloc(sizeof(int)*commands.lv);
		
		int j;
		i++;
		for(j = 0; j < commands.lv; j++){
			
			if(!isCommand(argv[i])){
				commands.nv[j] = atoi(argv[i]);
				i++;
			}
			else usage();
		}
		
		commands.n = 1;
	}
	if(strcmp(argv[i], "-lr") == 0){
		commands.lrv = atof(argv[i+1]);
		commands.lr = 1;	
	}
	if(strcmp(argv[i], "-f") == 0){
		if(!isCommand(argv[i+1])){
			commands.fv[0] = strdup(argv[i+1]);
			commands.f[0] = 1;
		}
		if(!isCommand(argv[i+2])){
			commands.fv[1] = strdup(argv[i+2]);
			commands.f[1] = 1;
		}
		if(!isCommand(argv[i+3])){
			commands.fv[2] = strdup(argv[i+3]);
			commands.f[2] = 1;
		}
		else{
			printf("\a\nTOO FEW FILES SPECIFIED\n");
			usage();
		}
		i= i+2;
	}
	if(strcmp(argv[i], "-e") == 0){
		commands.ev = atof(argv[i+1]);
		commands.e = 1;	
	}
	
	//if(i <= 11)
	i= i+2;
}

if(verify_coms(commands) > 0){ //ensure all required commands are present
	usage();
	}
//************************************************ //commands parsed

network net;

net.inputs = commands.nv[0];
net.outputs = commands.nv[commands.lv-1];
net.layers = commands.lv;
net.rate = commands.lrv;

//weight initialization allocates and inits to random value between .1 and -.1
//****************************************************************************
net.l_hidden = init_hweight(net.l_hidden, commands.lv, commands.nv, commands.nv); //initialize hidden layer
net.h_bias = init_bweight( net.h_bias, commands.lv, commands.nv, 0); //initialize hidden layer bias 
net.l_output = init_oweight(net.l_output, commands.nv[commands.lv-2], 0); //initialize output layer
net.o_bias = init_oweight(net.o_bias, commands.nv[commands.lv-1], 0); //initialize output layer bias
//****************************************************************************

//value initialization uses weight initialization with different function flag to init to 0
//*****************************************************************************************
net.hv_hidden = init_bweight(net.hv_hidden, commands.lv, commands.nv, 1);
net.hv_output = init_oweight(net.hv_output, commands.nv[commands.lv-1], 1);
net.sv_hidden = init_bweight(net.sv_hidden, commands.lv, commands.nv, 1);
net.sv_output = init_oweight(net.sv_output, commands.nv[commands.lv-1], 1);
net.dv_hidden = init_bweight(net.dv_hidden, commands.lv, commands.nv, 1);
net.dv_output = init_oweight(net.dv_output, commands.nv[commands.lv-1], 1);
//******************************************************************************************

int z;
	printf("\t\t\tproblem: 2\n\t\t\tlayers: %d\n\t\t\tepochs: %d\n\t\t\trate: %f\n", commands.lv, commands.ev, commands.lrv);
	
	printf("\t\t\t");
	for(z=0; z < commands.lv; z++){
		printf("%d ",commands.nv[z]);
	}
	printf("\n\n");
	
	
for(z = 0; z < commands.ev; z++){
	net = trainNet(net, commands.fv[0], commands.nv);
	testNet(net, commands.fv[1], commands.nv, z);
}
	printf("\t\t\tvalidation_error: ");
	evaluateNet(net, commands.fv[2], commands.nv);

	
}

//*********************************************************************************
//INITIALIZE THE HIDDEN LAYER WEIGHTS
float***
init_hweight( float ***layer, float l, int* n, int* w) {

	int i,j,k;
	int sign;
	
	layer = (float ***)malloc(sizeof(float*)*l);
	for(i = 0; i < l-1; i++) {
		layer[i] = (float**)malloc(sizeof(float*)*n[i]);
	}

	for(i = 0; i < l-1; i++) {
		for(j = 0; j < n[i]; j++) {
		
			layer[i][j] = (float *)malloc(sizeof(float)*w[i-1]);
		}
	}
	
	for(i =1; i < (int)l-1; i++) {
		for(j = 0; j < n[i]; j++) {
			for(k = 0; k < w[i-1]; k++){
				sign = rand()%2;
				
				if(sign % 2 == 0)
					layer[i][j][k] = ( (float)(rand()%100)/(float)1000);
				else
				layer[i][j][k] = -1*( (float)(rand()%100)/(float)1000);
			}
		}
	}
	return layer;
	
}
//*******************************************************************************
//INITIALIZE THE HIDDEN LAYER BIAS WEIGHTS
float**
init_bweight(float **layer, float l , int *n, int funct){
	
	int i,j;
	int sign;
	
	//allocate the space
	layer = (float **)malloc(sizeof(float*)*l);
	for(i = 0; i < l-1; i++) {
		layer[i] = (float*)malloc(sizeof(float)*n[i]);
	}
	
	
	if(funct == 0){ //if function is for weights
	//initialize the wieghts
	for(i = 0; i < l-1; i++) {
		for(j=0; j < n[i]; j++) {
			sign = rand()%2;
				
			if(sign % 2 == 0)
				layer[i][j] = ((float)(rand()%100+1)/(float)1000);
			else
				layer[i][j] = -1 * ((float)(rand()%100+1)/(float)1000);
		}
	}
	}
	
	if(funct == 1){
		for(i = 0; i < l-1; i++) {
			for(j=0; j < n[i]; j++) {
				layer[i][j] = 0;
			}
		}
	}
	
	
	//return the bias weights
	return layer;
}

//**************************************************************************
//INITIALIZE THE OUTPUT LAYER WEIGHTS (ALSO USED FOR BIAS)
float*
init_oweight( float *layer, int n, int funct) {

	int j;
	int sign;
	
	layer = (float *)malloc(sizeof(float)*n);
	
	
	if(funct == 0){
	for(j = 0; j < (int)n; j++) {
			sign = rand()%2;
				
			if(sign % 2 == 0)
				layer[j] = ((float)(rand()%100+1)/(float)1000);
			else
				layer[j] = -1 * ((float)(rand()%100+1)/(float)1000);
		}
	}
	if(funct == 1){
		for(j = 0; j < (int)n; j++) {
			layer[j] = 0;
		}
	}
	return layer;
}

//****************************************************************************
//LOGISTIC SIGMOID FUNCTION 
float 
sigmoid(float input, float alpha) {
	return ((float)1 / (float)(1 + exp( alpha * input * -1)) );
}

//****************************************************************************
//DERIVATIVE OF THE SIGMOID FUNCTION 
float 
dsigmoid(float input, float alpha) {
	return (float)(alpha * sigmoid(input, alpha) * (1- sigmoid(input, alpha)) );
}

//*******************************************************************************
//CLEAR ALL THE VALUES FROM THE NETWORK EXCEPT WEIGHTS
void
clearVals(network net, int * n) {
int i,j;
	
		for(i = 0; i < net.layers-1; i++) {
			for(j=0; j < n[i]; j++) {
				net.hv_hidden[i][j] = 0;
				net.sv_hidden[i][j] = 0;
				net.dv_hidden[i][j] = 0;
			}
		}
	
		for(j = 0; j < net.outputs; j++) {
			net.hv_output[j] = 0;
			net.sv_output[j] = 0;
			net.dv_output[j] = 0;
		}
}

//********************************************************************************
//TRAIN THE NEURAL NETWORK TO SOLVE THE PROBLEM

network
trainNet(network net, char *filename, int *n) {

	int i, j, k;
	
	float in[net.inputs];
	float out[net.outputs]; 

	FILE *training;
	training = fopen(filename, "r+");

	while(fscanf(training,"%f %f %f %f", &in[0], &in[1], &in[2], &out[0]) == 4) {
		clearVals(net, n);
		
		for(i = 0; i < net.inputs; i++){
			net.sv_hidden[0][i] = in[i]; //pattern input
		}
	
	
		//FEEDFORWARD PROCESS TO GET THE OUTPUT
		//**************************************************************************************
		for(i=1; i < net.layers-1; i++) { //for each hidden layer
			for(j=0; j < n[i]; j++){ //for each node in the layer
				for(k=0; k < n[i-1]; k++){
				//get all of the h values of the hidden layer
				net.hv_hidden[i][j] += (net.sv_hidden[i-1][k] * net.l_hidden[i][j][k]);
				}
		
				net.hv_hidden[i][j] += (net.h_bias[i][j]); //add in the bias
				net.sv_hidden[i][j] = sigmoid(net.hv_hidden[i][j], 1); //pass through sigmoid
			}
		}
		
		//output node output
		float output;
		for(i=0; i < n[net.layers-2]; i++) {
			output += (net.l_output[i] * net.sv_hidden[net.layers-2][i]); 
		}
		
		output += net.o_bias[0];
		output = sigmoid(output, 1); //output sigma value
		//printf("%f %f %f\n", in[0], in[1], output);
		//*********************************************************************************************
	
		//BACKWARD PASS TO GET THE WEIGHT ADJUSTMENT DELTA VALUES
		//*********************************************************************************************
		
		net.dv_output[0] = (output * (1.0-output) * (out[0] - output) );
		
		for(i = net.layers-2; i > 0; i--) {
			for(j = 0; j < n[i]; j++) {
				
				if(i == net.layers-2) {
					net.dv_hidden[i][j] = (net.sv_hidden[i][j] * (1-net.sv_hidden[i][j]) * net.dv_output[0] * net.l_output[j]); //last hidden layer
				}
				else{
					for(k = 0; k < n[i+1]; k++){
						net.dv_hidden[i][j]+= (net.dv_hidden[i+1][k]*net.l_hidden[i+1][k][j]); //other hidden layers
					}
					net.dv_hidden[i][j] = net.sv_hidden[i][j]*(1-net.sv_hidden[i][j])*net.dv_hidden[i][j];
				}
			}
		}
		//**********************************************************************************************				
		
		//WEIGHT ADJUSTMENT TO TRAIN THE NETWORK
		//***********************************************************************************************
		
		//update the hidden layer weights and bias
		for(i=1; i < net.layers-1; i++) { //for each hidden layer
			for(j=0; j < n[i]; j++){ //for each node in the layer
				for(k=0; k < n[i-1]; k++){
					net.l_hidden[i][j][k] += (net.rate * net.dv_hidden[i][j] * net.sv_hidden[i-1][k]);
				}
				net.h_bias[i][j] += (net.rate * net.dv_hidden[i][j]); 
			}
		}
		
		//update the output layer weights and bias
		
		for(i = 0; i < n[net.layers-2]; i++) { 
			net.l_output[i] += (net.rate * net.dv_output[0] * net.sv_hidden[net.layers-2][i]);
		}
		net.o_bias[0] += (net.rate * net.dv_output[0]);
		//**************************************************************************************************		
			
}
fclose(training);
	
return net;

}

void 
testNet(network net, char *filename, int *n, int epoch) {

	int i, j, k;
	
	float sum = 0;
	int patterns = 0;
	float in[net.inputs];
	float out[net.outputs]; 

	FILE *testing;
	testing = fopen(filename, "r+");

	while(fscanf(testing,"%f %f %f %f", &in[0], &in[1], &in[2], &out[0]) == 4) {
		patterns++;
		clearVals(net, n);
		
		for(i = 0; i < net.inputs; i++){
			net.sv_hidden[0][i] = in[i]; //pattern input
		}
		
		
	//FEEDFORWARD PROCESS TO GET THE OUTPUT
		//**************************************************************************************
		for(i=1; i < net.layers-1; i++) { //for each hidden layer
			for(j=0; j < n[i]; j++){ //for each node in the layer
				for(k=0; k < n[i-1]; k++){
				//get all of the h values of the hidden layer
				net.hv_hidden[i][j] += (net.sv_hidden[i-1][k] * net.l_hidden[i][j][k]);
				}
		
				net.hv_hidden[i][j] += (net.h_bias[i][j]); //add in the bias
				net.sv_hidden[i][j] = sigmoid(net.hv_hidden[i][j], 1); //pass through sigmoid
			}
		}
		
		//output node output
		float output;
		for(i=0; i < n[net.layers-2]; i++) {
			output += (net.l_output[i] * net.sv_hidden[net.layers-2][i]); 
		}
		
		output += net.o_bias[0];
		output = sigmoid(output, 1); //output sigma value
		//*********************************************************************************************
	
		sum +=(pow((out[0]-output),2));
	}
	
	//printf("sum = %f\n", sum);
	//printf("patterns = %d\n", patterns);
	float rmse;
	rmse = sqrt(((float)1/(float)(2*patterns))*(float)sum);
	printf("%d\t%f\n",epoch, rmse);
	
	fclose(testing);
}
	
void 
evaluateNet (network net, char *filename, int *n) {

	int i, j, k;
	
	float sum = 0;
	int patterns = 0;
	float in[net.inputs];
	float out[net.outputs]; 

	FILE *validate;
	validate = fopen(filename, "r+");

	while(fscanf(validate,"%f %f %f %f", &in[0], &in[1], &in[2], &out[0]) == 4) {
		patterns++;
		clearVals(net, n);
		
		for(i = 0; i < net.inputs; i++){
			net.sv_hidden[0][i] = in[i]; //pattern input
		}
		
		
	//FEEDFORWARD PROCESS TO GET THE OUTPUT
		//**************************************************************************************
		for(i=1; i < net.layers-1; i++) { //for each hidden layer
			for(j=0; j < n[i]; j++){ //for each node in the layer
				for(k=0; k < n[i-1]; k++){
				//get all of the h values of the hidden layer
				net.hv_hidden[i][j] += (net.sv_hidden[i-1][k] * net.l_hidden[i][j][k]);
				}
		
				net.hv_hidden[i][j] += (net.h_bias[i][j]); //add in the bias
				net.sv_hidden[i][j] = sigmoid(net.hv_hidden[i][j], 1); //pass through sigmoid
			}
		}
		
		//output node output
		float output;
		for(i=0; i < n[net.layers-2]; i++) {
			output += (net.l_output[i] * net.sv_hidden[net.layers-2][i]); 
		}
		
		output += net.o_bias[0];
		output = sigmoid(output, 1); //output sigma value
		//*********************************************************************************************
	
		sum +=(pow((out[0]-output),2));
	}
	
	float rmse;
	rmse = sqrt(((float)1/(float)(2*patterns))*(float)sum);
	printf("%f\n", rmse);
	
	fclose(validate);
}
	
	
	
	
	
	
	
	
