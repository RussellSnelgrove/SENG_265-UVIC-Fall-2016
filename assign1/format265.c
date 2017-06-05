

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_IN_LINES 500
#define MAX_IN_CHARS 150

char display[MAX_IN_LINES * MAX_IN_CHARS];
char str[MAX_IN_CHARS];
int line_size = 0;

int FT = 0; 
int LM = 0;
int LW = 0; 
int LS = 0;




/*This is my function for checking commands*/
int check_com(char* line) {
	char tmp[MAX_IN_CHARS];
	strncpy (tmp, line, MAX_IN_CHARS);
	strtok (tmp, " \n");
	if(!strncmp(tmp, ".FT", MAX_IN_CHARS) ) {
		char* t = strtok (NULL, " \n");
		if ( !strncmp(t, "on", 3) ) {
			FT= 1;
		}else{
			FT= 0;
		}
		return 1;
	}
	if(!strncmp(tmp,".LS",MAX_IN_CHARS) ){
		int t = atoi(strtok(NULL," \n") );
		LS = t;
		return 1;
	}
	if(!strncmp(tmp, ".LM", MAX_IN_CHARS) ) {
		int t = atoi( strtok (NULL, " \n") );
		LM = t;
 		return 1;
	}
	if(!strncmp(tmp, ".LW", MAX_IN_CHARS) ) {
		int t = atoi( strtok (NULL, " \n") );
		LW = t;
		FT = 1;
		return 1;
	}
	return 0;
}



/*This function is for editing each line for the commands we are given*/
void edit(char* line) {
	char* t= strtok (line, " \n"); 
	while (t) {
		if (line_size + strlen (t) >= LW) {
			strncat (str, "\n", 1);
			line_size = 0;
				if (LM) {
					if(LS){
						strncat(str,"\n",1);
						line_size++;
					}
					while (line_size < LM) {
						strncat (str, " ", 1);
						line_size++;
					}
				}
		/*		if(LS){
					strncat(str,"\n",1);
					line_size++;
				}
*/
			
		}else if (line_size >= LM+1) {
			line_size++;
			strncat (str, " ", 1);
		}
	line_size = line_size + strlen (t);
	strncat (str, t, MAX_IN_CHARS);
	t= strtok (NULL, " \n");
	}

	return;
}


int main (int argc, char* argv[]) {
	FILE* input;
	char line[MAX_IN_CHARS]; 
  
	input = fopen (argv[1], "r");
	if (input == NULL) {
		return -1;
	}
  
	while ( fgets (line, MAX_IN_CHARS, input) ) {
		if ( check_com(line) ) {
				continue;
			}
		    
		if (LM) {
			while (line_size < LM) {
				strncat (str, " ", 1);
				line_size++; 
			}
		}
/*		if(FT && LS && strncmp(line,"\n",1)){
			strncat(display,"\n\n",MAX_IN_CHARS); 
		}	
*/		if (FT && !strncmp (line, "\n", 1) ) {
			strncat (display, "\n\n", MAX_IN_CHARS);
			line_size = 0;
		}
		
		if (FT) {
			edit(line);
			strncat (display, str, MAX_IN_CHARS);
			strncpy (str, "", MAX_IN_CHARS);
		
		}else{
			strncat(display,line,MAX_IN_CHARS);
		}	
	}
 
	if (FT) {
		strncat (display, "\n", MAX_IN_CHARS);
	}
  
	printf("%s", display);
	return 0;
}
