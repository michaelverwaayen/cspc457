#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FNAME_SIZE 512
#define MAX_FILES 1024

int myComp(const void *x, const void *y)
{
	int xx = *(const int*)x;
	int yy = *(const int*)y;
	return(yy-xx);
	
}

int main( int argc, char ** argv) {
	// handle command line arguments
	if( argc != 3) {
		fprintf(stderr, "I don't take command line arguments.\n");
		exit(-1);
	}
	char *testvar = argv[1];
	char command[100];
	// open 'find...'
	//printf("%s",testvar);
	//snprintf(command,sizeof(command), "find . -name '*%s' ", testvar);
		snprintf(command,sizeof(command), "find . -name '*%s' > temp.txt ", testvar);
	FILE * fp = popen( command, "r");
	if( fp == NULL) {
		perror("popen failed:");
		exit(-1);
	}
	FILE *infile = fopen("temp.txt","r");
	// read in all filenames
	char buff[MAX_FNAME_SIZE];
	int nFiles = 0;
	char * files[MAX_FILES];
	while(fgets(buff,MAX_FNAME_SIZE,infile)) {
		int len = strlen(buff) - 1;
		files[nFiles] = strndup(buff,len);

		nFiles ++;
  }
	fclose(fp);
//	printf("Found %d files:\n", nFiles);
		
	// get file sizes for each file and sum them up
	long long totalSize = 0;
	struct stat st;
	int numbers[1000000];
	int num;
	int sum;
	sscanf (argv[2],"%d",&num);

	for(int i = 0 ; i < nFiles ; i ++ ) {
		//sort ur files here 
		if( 0 != stat(files[i],&st)) {

			perror("stat failed:");
			exit(-1);
		}
		numbers[i] = st.st_size;
	//	printf("\t%s : %ld\n", files[i], st.st_size);
	}
	
	//printf("Total size: %lld bytes.\n", totalSize);
	// clean up

	int n = sizeof(numbers)/ sizeof(int);
	//quick sort attempt 
	qsort(numbers, n, sizeof(int),myComp);
	//NOW IVE SORTED MY NUMS G BLESS SORT THE VALUES 
	if(num < nFiles)
	{
		nFiles = num;
	}
	
	for(int i=0;i<nFiles;i++)
	{
		printf("%d \t ",numbers[i]);
		printf("%s\n", files[i]);
		sum += numbers[i];
	}
	printf("Total: %d\t", sum);
	
	
	
	for(int i = 0; i < nFiles ; i ++ ) {
		free(files[i]);
	}
	// return success
	fclose(infile);
	return 0;
}

