//Your code goes here..!
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>



void printScreen(FILE *inputf, FILE *outputf){
		char *line=NULL;
		size_t length=0;
		int lineCount =0;
		int currentLineSize=0;
		//int lastSize=0;
		
		
		//fseek(FILE *stream, long int offset, int whence)
		
		while(currentLineSize!=-1 ){
			//lastSize = currentLineSize;
			currentLineSize =getline(&line,&length,inputf);
			if(currentLineSize!=-1) ++lineCount;
			if(currentLineSize!=-1)printf("line: %s",line);
		}
		printf("\n_______________________\n");
		fseek(inputf, 0, SEEK_SET);
		int * lineLengths = (int*)malloc(sizeof(int)*lineCount);
		for(int i =0;i<lineCount;++i){
			lineLengths[i] =getline(&line,&length,inputf);			
		}

		int LengthFromBottom= 0;
		if(outputf==NULL){
			for(int i =lineCount-1;i>=0;--i){
				
				LengthFromBottom= LengthFromBottom + lineLengths[i];
				//printf("i:%d , lineLen: %d, lineTot: %d\n",i,lineLengths[i],LengthFromBottom);
				fseek(inputf, -LengthFromBottom, SEEK_END);
				getline(&line,&length,inputf);
				if (i == lineCount-1 && line[lineLengths[lineCount-1]-1]=='\n'){printf("\n");}
				printf("%s",line);
				if (i == lineCount-1 && line[lineLengths[lineCount-1]-1]!='\n'){printf("\n");}
			}
		}
	
	return;
}


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
		printScreen(inputf, NULL);


		
		fclose(inputf);
		
		
	}
		

	return 0;
}