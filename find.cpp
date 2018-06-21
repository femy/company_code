#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

using namespace std;
struct stat s_buf;			//global use
void find(const char *path){
	if(path == NULL)
		return;
	stat(path, &s_buf);
	if(S_ISDIR(s_buf.st_mode)){
		//is dir
		DIR *dp = opendir(path);
		struct dirent *filename;
		char newfilename[200];
		if(dp == NULL)
			return;
		while(filename = (struct dirent*)readdir(dp)){
			bzero(newfilename, sizeof(newfilename));
			if(strcmp(filename->d_name, ".") == 0 ||
			   strcmp(filename->d_name, "..") == 0)
				continue;
			strcat(newfilename, path);
			strcat(newfilename, "/");
			strcat(newfilename, filename->d_name);
			find(newfilename);
		}
	}
	else{
		//is file
		cout<<path<<endl;
	}
}
int main(int argc, char **argv){
	if(argc == 2)
	{
		find(argv[1]);
	}
	else
	{
		cout<<"must 2 parameter"<<endl;
	}
	return 0;
}
