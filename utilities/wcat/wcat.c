//Hey your code goes here..!
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

void printFile(FILE * infile){
	
	char * buffer;
	size_t length=0;

	while(getline(&buffer,&length,infile)!=-1){	
		printf("%s",buffer);
	}
	
}


int main(int argc,char* argv[]){
	
	
	FILE **inputf = (FILE **)malloc(sizeof(FILE*)*(argc-1));

	for(int i = 0;i<argc-1;++i){
		inputf[i]= fopen(argv[i+1],"r");//try to open input file	
		//printf("file: %s\n",argv[i+1]);
		if(inputf[i]==NULL){
			printf("wcat: cannot open file\n" );
			exit(1);
		}	
		printFile(inputf[i]);
		fclose(inputf[i]);
	}
	
	
	return 0;
}