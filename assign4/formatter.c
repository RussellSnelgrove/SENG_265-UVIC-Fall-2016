#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatter.h"



int is_file = 0;
int FT_past =0;
int status_of_FT = 0;


void tester(int y){
	printf("This is working at number %d \n",y);
	
}


char **format_lines(char **lines, int num_lines) {

	static int LW			= 0;
	static int LS			=0;
	static int LM			= 0;
	static int FT			= 0;
/*	tester(12);*/
	char **final = (char**)calloc(1,sizeof(char*));
	if(final == NULL){
		errors();
	}
	int curr_line = 0;
	int word_size=0;
	int sizer = 0
	int line_len=0;
	int i;
	for(i = 0; i<num_lines; i++){
		char *alpha;
		if(!strncmp(lines[i],"\n",1) && FT==1){
			curr_line++;
			final = (char**)realloc(final,(curr_line+1) * sizeof(char*));
			if(final == NULL){errors();}
			final[curr_line] = (char*)calloc(2,sizeof(char));
			if(final[curr_line] == NULL){errors();}
			strcpy(final[curr_line],"\n");
			line_len = LW;
			continue;
		}
		
		/*
		if having enough time after finishing the assignment go back to tryin 
		to do this with linked list and structs
		
		
		for (i=0; i < *num_lines; i++) {
        if (!strncmp(lines[i], "\n", 1) && FT) {
      if (current_position != 0) {
        strncat (result.data[result.size], "\n", 1);
      }
      result.size++;
      result.data = (char**) realloc(result.data, (result.size+1) * sizeof(char*));
      if (result.data == NULL) {
        fprintf(stderr, "Could not allocate any memory!");
        exit(1);
      }
		
		*/
		if(command_checker(lines[i], &LW, &LS, &LM, &FT)){
			if(status_of_FT==1){
				final = (char**)realloc(final,(curr_line+1) * sizeof(char*));
				if(final == NULL){errors();}
				final[curr_line] = (char*)calloc(strlen(lines[i])+1,sizeof(char));
				if(final[curr_line] == NULL){errors();}
				if(FT==0){
					strcat(final[curr_line],"\n");
					strcat(final[curr_line],"\n");
					/*tester(13)*/
					curr_line++;
					final = (char**)realloc(final,(curr_line+1) * sizeof(char*));
					if(final == NULL){errors();}
			
					final[curr_line] = (char*)calloc(strlen(lines[i])+1,sizeof(char));
					if(final[curr_line] == NULL){errors();}
				}
				status_of_FT=0;
			}
			continue;
		}else if(FT){
			status_of_FT = 0;
			char *lines_tok = (char*)calloc(strlen(lines[i])+1, sizeof(char));
			if(lines_tok == NULL){errors();}
			if(is_file){
				strncpy(lines_tok,lines[i], strlen(lines[i])-1);
			}else{
				strncpy(lines_tok,lines[i], strlen(lines[i]));
				lines_tok[strlen(lines[i])] = '\0';
		}
			strcat(lines_tok,"\0");
			alpha =strtok(lines_tok, "\t \n");
			while(alpha !=0){
				word_size = strlen(alpha);
				if(LW < word_size + LM){
					fprintf(stderr,"The size of the word is over LW");
					exit(1);
				}
				
			/*
}
			strcat(lines_tok,"\0");
			alpha =strtok(lines_tok, "alpha \n");
			while(alpha !=0){
				word_size = strlen(alpha);
				if(LW < word_size + LM){
					exit(1)
				}

*/			
				if(line_len + word_size + LS + 1 > LW){
					if(is_file){
						int x;
						for(x=0; x<LS+1;x++){
						strncat(final[curr_line],"\n",2);
						}
					}
					curr_line++;
					final = (char**)realloc(final,(curr_line+1)*sizeof(char*));
					if(final == NULL){errors();}
					line_len = 0;
				}else if(line_len !=0){
					strncat(final[curr_line]," ",1);
					line_len++;
				}
				if(line_len==0){
					final[curr_line] =(char*)calloc(LW+2, sizeof(char));
					if(final[curr_line] == NULL){errors();}
					int z;
					for(z=0;z<LM;z++){
						strcat(final[curr_line], " ");
						line_len++;
					}
				}
				strncat(final[curr_line], alpha,word_size);
				line_len = line_len + word_size;
				alpha = strtok(NULL, " ");
			}
		}else{
			status_of_FT=0;
			if(line_len + LS < LW){
				int y;
				for(y=0;y<LS+1;y++){
				strncat(final[curr_line],"\n",2);
				}
				curr_line++;
			}
			
			final = (char**)realloc(final,(curr_line+1) * sizeof(char*));
			if(final == NULL){errors();}
			
			final[curr_line] = (char*)calloc(LW+2,sizeof(char));
			if(final[curr_line] == NULL){errors();}
			
			strncpy(final[curr_line], lines[i],strlen(lines[i])+1);
			curr_line++;
			line_len = LW+1;
			continue;
		}
	}
	if(FT){
		curr_line++;
		if(is_file){
			final = (char**)realloc(final,(curr_line+1) * sizeof(char*));
			if(final == NULL){errors();}
			final[curr_line] = (char*)calloc(2,sizeof(char));
			/*
			for(int g=0;g<k;g++){
				
			}
			*/
			if(final[curr_line] == NULL){errors();}
			strncpy(final[curr_line],"\n",1);
			curr_line++;
			final[curr_line] = NULL;
		}
	}
	final[curr_line] = NULL;
	return final;
}


char **format_file(FILE *infile) {
	char *line = NULL;
	int numlines = 0;

	size_t initlen = 0;
	ssize_t read;

	char **output = calloc(1,sizeof(char*));
	if(output == NULL){errors();}
	char **final = NULL;
	while((read = getline(&line, &initlen, infile)) != -1){
		output = (char**)realloc(output,(numlines+1) * sizeof(char*));
		if(output == NULL){errors();}
		output[numlines] = calloc(read+1,sizeof(char));
		if(output[numlines] == NULL){errors();}
		strcpy(output[numlines], line);
		numlines++;
	}
	is_file = 1;
	final = format_lines(output,numlines);
	return final;
}
/*
void values_p(){
	printf("%s, %d, %d, %d \n",FT ,LS, LW, LM);
}
*/
int command_checker(char *line_in, int *LW, int *LS, int *LM, int *FT){
	char *line = (char*)calloc(strlen(line_in)+1,sizeof(char));
	if(line == NULL){errors();}
	strncpy(line,line_in,strlen(line_in)+1);
	char *tok = strtok(line,"\t ");
	char FT_out[4];
	if(!strcmp(tok,".LW")){
		tok = strtok(NULL, " ");
		*LW = atoi(tok);
		*FT = 1;
		return 1;
	}
	if(!strcmp(tok,".LS")){
		tok = strtok(NULL, " ");
		*LS = atoi(tok);
		return 1;
	}
	else if(!strcmp(tok,".FT")){
		tok = strtok(NULL, " ");
		sscanf(tok, "%s", FT_out);
		if(strcmp(FT_out,"on")==0){
			*FT = 1;
			status_of_FT++;
		}
		if(strcmp(FT_out,"off")==0){
			*FT = 0;
			status_of_FT++;
		}
		/*if have time, add some statment here that 
		catchs anything else that is passed through and 
		throw an error*/
		return 1;
	}
	else if(!strcmp(tok,".LM") && *FT==1){
		tok = strtok(NULL, " ");
		if(!strncmp(tok,"+",1)) {
			*LM = *LM + atoi(++tok);
		}else if(!strncmp(tok,"-",1)) {
			*LM = *LM - atoi(++tok);
		}else{
			*LM = atoi(tok);
		}
		if (*LM >= *LW - 20) {
			*LM = *LW - 20;
		}
		return 1;
	}

	return 0;
}


void errors(){
	fprintf(stderr,"cannot allocate memory \n");
	exit(1);
}

