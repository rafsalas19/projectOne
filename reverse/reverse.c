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
		//printf("%s\n%s\n",inputName, outputName);
		
		FILE *inputf= fopen(inputName,"r");
		if(inputf==NULL){
			fprintf(stderr,"reverse: cannot open file %s\n",inputName);
			exit(1);
		}
		// char ** lineBuffer;
		// linerBuffer = (char**)malloc(sizeof(char*)*10);
		
		//read file
		char *line=NULL;
		size_t length=0;
		int lineCount =0;
		int currentLineSize=0;
		int lastSize=0;
		
		
		//fseek(FILE *stream, long int offset, int whence)

		
		while(currentLineSize!=-1){
			lastSize = currentLineSize;
			currentLineSize =getline(&line,&length,inputf);
			++lineCount;
			//printf("line: %s, line Count %d\n",line,lineCount);
			//printf("%p\n",(void *) inputf);
		}
		
		fseek(inputf, -lastSize, SEEK_END);
		getline(&line,&length,inputf);
		printf("line: %s, line count %d\n",line,lineCount);
		
		fclose(inputf);
		
		
	}
		

	return 0;
}