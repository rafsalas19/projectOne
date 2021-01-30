#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>





void inflate(FILE * infile){
	char outChar[1];
	outChar[0]='0';
	int iteration =1;
	
	while (!feof(infile)) // to read file 
    { 
		fread(&iteration, sizeof(int), 1, infile);
        fread(outChar, sizeof(char), 1, infile);
		if(feof(infile)){
			break;
		}
		//printf("%d",iteration);
		// printf("%c",outChar[0]);
		// printf("\n");

		for(int i =0;i<iteration;++i){
			printf("%c",outChar[0]);
		}
		
    } 
	
}

int main(int argc, char * argv[]){
	
	FILE **inputf = (FILE **)malloc(sizeof(FILE*)*(argc-1));

	if(argc<2){
		printf("wunzip: file1 [file2 ...]\n");
		exit(1);
	}

	for(int i = 0;i<argc-1;++i){
		inputf[i]= fopen(argv[i+1],"r");//try to open input file	
		if(inputf[i]==NULL){
			printf("wunzip: cannot open file\n" );
			exit(1);
		}	
		

		inflate(inputf[i]);
		fclose(inputf[i]);
		
	}
	

	return 0;
}