#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>

#define MAX_NAME 1000
#define MAX_COUNT 100

struct dirent* readdir(DIR* dirp);


int Find(unsigned deep, char* directory, char* file, char** out, int* count) {

	if (deep <= 0)
	        return 0;
        
    	DIR* d = opendir(directory);
    	struct dirent* dir;
    
    	while ((dir = readdir(d)) != NULL) {
    
        	if (dir->d_type == 4 && strcmp(dir->d_name, "./")) {
         
            	char abs_name[MAX_NAME] = {};
            	strcat(abs_name, directory);
            	strcat(abs_name, "/");
            	strcat(abs_name, dir->d_name);
            
            	Find(deep - 1, abs_name, file, out, count);
        	}
        	else if (dir->d_type == 8) {
        
            		if (!strcmp(dir->d_name, file)) {
            
                		strcat(out[*count], directory);
                		strcat(out[*count], "/");
                		strcat(out[*count], dir->d_name);
                		(*count)++;
            		}
		}
	}
    	closedir(d);
    
    	return *count;
}

int main(int argc, char** argv) {

	if (argc != 4) {
		printf("there is not 3 args\n");  
		return 0;
	}

	int count = 0, res_count = 0;
	
   	char** out = (char**)calloc(MAX_COUNT, sizeof(char*));
   	char** replays = (char**)calloc(MAX_COUNT, sizeof(char*));
   	char** ans = (char**)calloc(MAX_COUNT, sizeof(char*));
   	
   	for (int i = 0; i < MAX_COUNT; i++) {
        	out[i] = (char*)calloc(MAX_NAME, sizeof(char));
		replays[i] = (char*)calloc(MAX_NAME, sizeof(char));
		ans[i] = (char*)calloc(MAX_NAME, sizeof(char));
	}

    
   	if (Find(atoi(argv[3]), argv[1], argv[2], out, &count)) {
     		for (int i = 0; i < count; i++) {
     		
  	 		realpath(out[i], replays[i]);
          		int flag = 0;
          		
          		for (int k = 0; k < res_count; k++) {
				if (strcmp(replays[i], ans[k]) == 0) {
   	        			flag = 1;
               	 		break;
                		}
            		}
            		if (!flag) {
               		strcat(ans[res_count], replays[i]);
                		res_count++;
            		}
        	}
        	
        	for (int i = 0; i < res_count; i++)
            		printf("%d : [%s]\n", i + 1, ans[i]);
    	}
    	else 
        	printf("File not found\n");
    	
    
   	for (int i = 0; i < MAX_COUNT; i++) {
		free(out[i]);
		free(ans[i]);
		free(replays[i]);
        }
        
   	free(out);
   	free(ans);
   	free(replays);
   	
  	return 0;
}
