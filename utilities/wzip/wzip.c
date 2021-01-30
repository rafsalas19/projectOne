//Hey your code goes here..!
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#define VECTOR_SIZE 10

int vectorSize= VECTOR_SIZE;
char **stringVector;
int currentIndex =0;
int newLineCount =0;

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
int charCount =1;
char lastChar;

void compress(FILE* infile,int fileCount){
	char inchar[1];
	//size_t length=0;
	//int charCount =1;
	
	if(fileCount==0){
		inchar[0] = fgetc(infile);
		lastChar =inchar[0];
		//if (inchar[0]=='\n')newLineCount++;
	}
	

	while(inchar[0] !=EOF){	
	
		inchar[0] = fgetc(infile);
		//if (inchar[0]=='\n') newLineCount++;
		//if(inchar[0] == '\n'){continue;}
		if(inchar[0]==EOF) break;
		if(lastChar==inchar[0]){
			//printf("%d\n",charCount);
			++charCount;
		}
		else{
			//print charcout and char

			if(charCount !=1){
				fwrite(&charCount,sizeof(int),1,stdout);
				//printf("%d",charCount);
			}
			//printf("%c",lastChar);
			if (lastChar=='\n') newLineCount++;
			fputc(lastChar,stdout);
			//printf("\n");
			charCount =1;
			lastChar=inchar[0];
		}

	}

}


//try writing all at once put into buffer

int main(int argc, char * argv[]){
	//printf("hi");
	FILE **inputf = (FILE **)malloc(sizeof(FILE*)*(argc-1));
	if(argc<2){
		printf("wzip: file1 [file2 ...]\n");
		exit(1);
	}
	//char a ='LF';
	
	//printf("%cg%cg%c",a,a,a);
	for(int i = 0;i<argc-1;++i){
		inputf[i]= fopen(argv[i+1],"r");//try to open input file	
		if(inputf[i]==NULL){
			printf("wcat: cannot open file\n" );
			exit(1);
		}	
		
		//place code here
		compress(inputf[i],i);
		fclose(inputf[i]);
		
	if(i==argc-2){
		if(charCount !=1){
				fwrite(&charCount,sizeof(int),1,stdout);
				//printf("%d",charCount);
			}
			if (lastChar=='\n') newLineCount++;
			//printf("%c",lastChar);
			fputc(lastChar,stdout);
	}
		
	}
	// int test[5]={0,1,2,3,4};
	// fwrite(test,sizeof(int),5,stdout);
	
	
	//printf("\n%d new lines\n",newLineCount);
	return 0;
}