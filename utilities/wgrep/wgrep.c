//Hey your code goes here..!
//Hey your code goes here..!
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h> 
int search(char* term, char* line){
	
	int sizec = strlen(term);
	int sizel = strlen(line);

	bool wholeMatch = false;
	int termIter=0;
	for(int i =0;i<sizel;++i){
		
		if(term[termIter]==line[i]){
			if(termIter==sizec-1){
				wholeMatch =true;
				break;
			}
			else {
				termIter++;
			}
		}
		else{
			termIter =0;
		}	
	}
	if(wholeMatch ==true){
		return 0;
	}
	else return 1;
}


void SearchPrint(char*term, FILE * infile){
	
	char * buffer;
	size_t length=0;
	if(infile==NULL){
		while(getline(&buffer,&length,stdin)!=-1){	
			
			if(search(term,buffer)==0){
				printf("%s",buffer);
			}
		}
	}
	else{
		while(getline(&buffer,&length,infile)!=-1){	
			
			if(search(term,buffer)==0){
				printf("%s",buffer);
			}
		}
	}
}




int main(int argc,char* argv[]){
	if(argc>2){

		FILE **inputf = (FILE **)malloc(sizeof(FILE*)*(argc-1));

		for(int i = 1;i<argc-1;++i){
			
			inputf[i]= fopen(argv[i+1],"r");//try to open input file	
			if(inputf[i]==NULL){
				printf("wgrep: cannot open file\n" );
				exit(1);
			}
			SearchPrint(argv[1],inputf[i]);

			
			fclose(inputf[i]);
		}
	}
	else if(argc<2){
		printf("wgrep: searchterm [file ...]\n");	
			exit(1);
	}else{
		SearchPrint(argv[1],NULL);
	}
	return 0;
}