//Your code goes here..!
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>
#define VECTOR_SIZE 5

//make sure to include error catching for malloc

struct node{
	const char* data;
	struct node* next;
};

struct node *headNode = NULL;

int nodeCount=0;

struct node* addNode(const char* data){
	printf("newData %s", data);
	struct node * newNode = (struct node*)malloc(sizeof (struct node));
	newNode->data= data;
	newNode->next =headNode;
	headNode = newNode;
	nodeCount++;
	return newNode;
}

void printList(){
	struct node *currentNode = headNode;
	
	while(currentNode!=NULL){
		printf("list data: %s",currentNode->data);
		currentNode = currentNode->next;
		
	}
	
}

int vectorSize= VECTOR_SIZE;
char **stringVector;
int currentIndex =0;

int resizedVector(){
	char** temp = (char**)malloc(sizeof(char*)*2*vectorSize);
	memcpy(temp, stringVector, vectorSize);
	temp[0] =NULL;
	vectorSize=2*vectorSize;
	return 0;
}

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

	
	stringVector = (char**)malloc(sizeof(char*)*vectorSize);
	if(argc>3){
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}
	else if(argc<2){
		printf("Please input your words:\n");

		char * buffer;
		size_t length=0;
		int size =0;
		while(size!=-1){
			size =getline(&buffer,&length,stdin);
			if(size ==-1)break;
			if(currentIndex ==vectorSize){
				resizedVector();
			}
			char* tmpBuffer= (char*)malloc(sizeof(char)*size);
			memcpy(tmpBuffer,buffer,size);
			stringVector[currentIndex]=tmpBuffer;
			printf("%s",stringVector[currentIndex]);
			currentIndex++;

			printf("%s",buffer); 
		}
		//currentIndex--;
		printf("\n%d\n",currentIndex);
		printf("\n---------------------");
		
		for(int i =0;i<currentIndex;++i){
			char* temp= stringVector[i];
			printf("%d %s",i,temp);
		}
		//printList();
		//printf("\n---------------------");
		
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
		
	printf("end of file\n");
	return 0;
}