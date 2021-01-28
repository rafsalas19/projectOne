//Your code goes here..!
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>
#define VECTOR_SIZE 10
#include <sys/stat.h>

int vectorSize= VECTOR_SIZE;
char **stringVector;
int currentIndex =0;

int resizedVector(){
	char** temp = (char**)malloc(sizeof(char*)*2*vectorSize);
	if (temp ==NULL){
		fprintf(stderr, "Failed to resize stringVector array.\n");
		exit(1);
	}
	memcpy(temp, stringVector, vectorSize*sizeof(char**));
	vectorSize=2*vectorSize;
	stringVector =temp;
	temp=NULL;
	return 0;
}

void reverseInput(FILE *inputf, FILE *outputf){
		

		char * buffer;
		size_t length=0;
		int size =0;
		int lastLength=0;
		while(size!=-1){
			lastLength =size;
			if(inputf != NULL){
				size =getline(&buffer,&length,inputf);			
			}
			else
			{
				size =getline(&buffer,&length,stdin);
			}

			if(size ==-1)break;
			if(currentIndex ==vectorSize-1){
				resizedVector();
			}
			char* tmpBuffer= (char*)malloc(sizeof(char)*size);
			if (tmpBuffer ==NULL){
				fprintf(stderr, "Failed to allocate line memory.\n");
				exit(1);
			}
			memcpy(tmpBuffer,buffer,size);
			stringVector[currentIndex]=tmpBuffer;

			currentIndex++;
		}
		
		for(int i =currentIndex-1;i>=0;--i){
			char* temp= stringVector[i];
			if(outputf == NULL){			
				//if (i == currentIndex-1 && stringVector[i][lastLength-1]=='\n'){printf("\n");}
				printf("%s",temp);
				if (i == currentIndex-1 && stringVector[i][lastLength-1]!='\n'){printf("\n");}
			}
			else{
				//if (i == currentIndex-1 && stringVector[i][lastLength-1]=='\n'){fputs("\n",outputf);}
				fputs(temp,outputf);
				if (i == currentIndex-1 && stringVector[i][lastLength-1]!='\n'){fputs("\n",outputf);}
			}
		}
	
}





int main(int argc, char* argv[]){

	
	stringVector = (char**)malloc(sizeof(char*)*vectorSize);
	if (stringVector ==NULL){
		fprintf(stderr, "Failed to allocate stringVector.\n");
		exit(1);
	}
	if(argc>3){
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}
	else if(argc<2){
		
		reverseInput(NULL, NULL);

	}
	else
	{
		FILE *outputf=NULL;
		FILE *inputf=NULL;
		char* inputName=argv[1];
		char* outputName;
		if(argc >2){//user provided two files
			outputName=argv[2];		
			if(strcmp(inputName, outputName )==0){
				fprintf(stderr, "reverse: input and output file must differ\n");
				exit(1);
			}	

			inputf= fopen(inputName,"r");//try to open input file	
			if(inputf==NULL){
				fprintf(stderr,"reverse: cannot open file '%s'\n",inputName);
				exit(1);
			}
			outputf = fopen(outputName,"a");
			if(outputf==NULL){
				fprintf(stderr,"reverse: cannot open file '%s'\n",outputName);
				exit(1);
			}
			
			struct stat ofstat;
			struct stat ifstat;
			int ofd=fileno(outputf);
			int ifd=fileno(inputf);
			if(fstat (ofd, &ofstat) ==-1){ fprintf(stderr, "failed to get file inode");exit(1);}
			if(fstat (ifd, &ifstat) ==-1){ fprintf(stderr, "failed to get file inode");exit(1);}
			if(ofstat.st_ino == ifstat.st_ino){
				fprintf(stderr, "reverse: input and output file must differ\n");
				exit(1);
			}
			
			fclose(outputf);
			//try to open out file
			outputf = fopen(outputName,"w");
			if(outputf==NULL){
				fprintf(stderr,"reverse: cannot open file '%s'\n",outputName);
				exit(1);
			}
		}
		else//user only provided one file
		{
			inputf= fopen(inputName,"r");//try to open input file	
			if(inputf==NULL){
				//printf("hello\n");
				fprintf(stderr,"reverse: cannot open file '%s'\n",inputName);
				exit(1);
			}
			outputName = NULL;
		}
		


		//
		reverseInput(inputf, outputf);
		
		
		if(outputf !=NULL){fclose(outputf);}
		fclose(inputf);
		
		
	}
		
	
	return 0;
}