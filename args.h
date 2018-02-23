typedef struct args{
//values
int lv;
int *nv; 
float lrv; //eta in the formula
char *fv[3]; //3 file names
int ev;
//bool flags
int l;
int n;
int lr;
int f[3];
int e;
}args;

//***********************************************************************************
// Gives the proper usage of the program, default error message
void 
usage() {

	printf("\nusage:\n#####################\n\n");
	printf("-l : number of layers including input/output\n");
	printf("-n : number of neurons in each layer including input/output\n");
	printf("\t*note: arguments to '-n' must add  up to '-l' parameter\n");	
	printf("-lr : learning rate\n");
	printf("-f : files [training] [testing] [validation]\n");
	printf("-e : number of epochs\n");
	printf("NOTE: Files are strings, learning rate is floating point\n");
	printf("all others are integers\n");
	exit(-1);
}

//***********************************************************************************
//Designed to check if a command argument is a command or a numeric parameter
int
isCommand( char *command) {
	const char *comp = strdup(command);
	
	if(strcmp(comp, "-l") == 0)
		return 1;
	else if(strcmp(comp, "-n") == 0)
		return 1;
	else if(strcmp(comp, "-lr") == 0)
		return 1;
	else if(strcmp(comp, "-f") == 0)
		return 1;
	else if(strcmp(comp, "-e") == 0)
		return 1;
	else
		return 0;
}

//*********************************************************************************
//Ensures that all required arguments are accounted for
int
verify_coms(args coms) {
	int flag = 0;
	if(coms.l != 1){
		printf("missing layers\n");
		flag++;
	}
	if(coms.n != 1){
		printf("missing neurons\n");
		flag++;
	}
	if(coms.lr != 1){
		printf("missing learning rate\n");
		flag++;
	}
	if(coms.f[0] != 1){
		printf("missing training file\n");
		flag++;
	}
	if(coms.f[1] != 1){
		printf("missing testing file\n");
		flag++;
	}
	if(coms.f[2] != 1){
		printf("missing validation file\n");
		flag++;
	}
	if(coms.e != 1){
		printf("missing number of epochs\n");
		flag++;
	}
	
	if(flag > 0)
		printf("missing %d arguments", flag);
	
	return flag;
}

//*********************************************************************************
//Clears the values for the arguments
args
init_args() {

	args temp;
	temp.l = 0;
	temp.lr = 0;
	temp.n = 0;
	temp.e = 0;
	temp.f[0] = 0;
	temp.f[1] = 0;
	temp.f[2] = 0;

	return temp;
}
