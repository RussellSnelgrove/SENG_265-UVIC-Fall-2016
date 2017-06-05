#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatter.h"


int main(int argc, char *argv[]) {
	char *line[512];
	char **lines;
	char **edited;
	FILE *filer;
	int counter=1;
	int tester=1;
	if(argc==1){ 
		fgets(*line_in, 200, stdin);
		edited = format_lines(line_in, 1);
	}else{
	/*	for(int k=0;k<10;k++){
		printf("testing number 1 \n");
		}
	*/	
		checker(argc,argv);
		filer = fopen(argv[1],"r");
		if(filer == NULL){
			fprintf(stderr,"Cannot open file\n");
			exit(1);
		}
	/*	for(int k=0;k<10;k++){
		printf("testing number 2 \n");
		}
	*/	edited = format_file(filer);
		if(edited == NULL){
			fprintf(stderr,"there is nothing in the file");
			exit(1);
		}
	}
	for(lines = edited; *lines != NULL; lines++){
		fprintf(stdout,"%s",*lines);
	}
	fclose(filer);
	exit(0);
}

void checker(int argnum, char** input){
	if(argnum !=2){
		fprintf(stderr,"Invalid parameters\n");
		exit(1);
	}
}
