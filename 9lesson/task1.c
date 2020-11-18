#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define MAX_STR 1000

int main(int argc, char* argv[]) {
	
	if (argc != 2) {
		printf("Ban\n");
	}
	
	//printf("%s  ", argv[1]);
	DIR* dir = opendir(argv[1]);
	
	struct dirent* dirent_;
	
	while ((dirent_ = readdir(dir))!= NULL) {
		
		char copystr[MAX_STR];
		strcpy(copystr,argv[1]);
	
		strcat(copystr, "/");
		
		printf("name: %s\n", strcat(copystr,dirent_-> d_name));
		struct stat buf;
		lstat(copystr, &buf);
		
		if (S_ISREG(buf.st_mode) )
			printf("file type is regular type\n");
		else if (S_ISDIR(buf.st_mode))
			printf("file type is directory\n");
		else
			printf("file type is unknown\n");
			
			
		printf("size: %llu \n", buf.st_size);
		
		printf("\n\n");
	}

	
	
	return 0;
}
