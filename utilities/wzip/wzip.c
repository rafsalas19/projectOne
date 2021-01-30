//Hey your code goes here..!
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>
#define VECTOR_SIZE 10
#include <sys/stat.h>

int charCount =1;
char lastChar;

void compress(FILE* infile,int fileCount){
	char inchar[1];
	//size_t length=0;
	//int charCount =1;
	inchar[0] = fgetc(infile);
	if(fileCount==0)lastChar =inchar[0];
	

	while(inchar[0] !=EOF){	
	
		inchar[0] = fgetc(infile);
		if(inchar[0]==EOF) break;
		if(lastChar==inchar[0]){
			//printf("%d\n",charCount);
			++charCount;
		}
		else{
			//print charcout and char

			if(charCount !=1){
				//fwrite(&charCount,sizeof(int),1,stdout);
				printf("%d",charCount);
			}
			printf("%c",lastChar);
			//printf("\n");
			charCount =1;
			lastChar=inchar[0];
		}

	}

}




int main(int argc, char * argv[]){
	
	FILE **inputf = (FILE **)malloc(sizeof(FILE*)*(argc-1));
	
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
			printf("%c",lastChar);
		
	}
		
	}
	// int test[5]={0,1,2,3,4};
	// fwrite(test,sizeof(int),5,stdout);
	
	
	
	return 0;
}