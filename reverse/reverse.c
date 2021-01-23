//Your code goes here..!
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>

int main(int argc, char* argv[]){


	// char** inLines;
	// char** outLines;
	if(argc>3){
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}
	else if(argc<1){
		printf("Please input your words:\n");
		//input code
		//input = ;
		//
		printf("\n");
	}
	else
	{
		char* inputName=argv[1];
		char* outputName;
		if(argc >2){
			outputName=argv[2];		
			if(strcmp(inputName, outputName )==0){
				fprintf(stderr, "Input and output file must differ\n");
				exit(1);
			}			
			//printf("%s\n%s\n",input, output);
		}
		else
		{
			outputName = NULL;
		}
		printf("%s\n%s\n",inputName, outputName);
		
		FILE *inputf= fopen(inputName,"r");
		if(inputf==NULL){
			fprintf(stderr,"reverse: cannot open file %s\n",inputName);
			exit(1);
		}
		
		fclose(inputf);
		
		
	}
		

	return 0;
}