//Hey your code goes here..!
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

int currentIndex =0;
int newLineCount =0;


int charCount =1;
char lastChar;

void compress(FILE* infile,int fileCount){
	char inchar[1];
	
	if(fileCount==0){
		inchar[0] = fgetc(infile);
		lastChar =inchar[0];
	}
	

	while(inchar[0] !=EOF){	
	
		inchar[0] = fgetc(infile);
		if(inchar[0]==EOF) break;
		if(lastChar==inchar[0]){
			++charCount;
		}
		else{
			fwrite(&charCount,sizeof(int),1,stdout);
			fputc(lastChar,stdout);
			charCount =1;
			lastChar=inchar[0];
		}

	}

}


//try writing all at once put into buffer

int main(int argc, char * argv[]){
	
	FILE **inputf = (FILE **)malloc(sizeof(FILE*)*(argc-1));
	if(argc<2){
		printf("wzip: file1 [file2 ...]\n");
		exit(1);
	}

	for(int i = 0;i<argc-1;++i){
		inputf[i]= fopen(argv[i+1],"r");//try to open input file	
		if(inputf[i]==NULL){
			printf("wzip: cannot open file\n" );
			exit(1);
		}	
		

		compress(inputf[i],i);
		fclose(inputf[i]);
		
	if(i==argc-2){
			fwrite(&charCount,sizeof(int),1,stdout);
			fputc(lastChar,stdout);
	}
		
	}

	return 0;
}
