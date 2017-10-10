#include <unistd.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
using namespace std;

int main(int argc, char const * argv[])
{
	//Declare variables

	int a[1000000];
	int count;
	string textFile;
	int threadsToMake;
	
	//Take in the arguments passed in
	textFile = argv[1];
	string threadCountInput=argv[2];
	threadsToMake = stoi(threadCountInput);


	//Open my text file and add all elements into an array to be passed of to strings
	ifstream infile; //open the file
	infile.open(textFile);
	string line;
	count = 0;
//	while(!infile.eof()) //while there is something elft read the next line 
	while (getline( infile, line ))
	{		
		a[count] = atoi(line.c_str());
		count++; 
	}
	infile.close();
	//	now i want to seperate the threads into groups using ceiling 
	//int giveNumToThread = (count + threadsToMake - 1) / threadsToMake;
	while(count % threadsToMake != 0)
	{
		count++;
		a[count] = 0;
	}
	//now i will be able to pass the same parameter to each thread.. an index and a stop point which is index + index -1
	int numbersPerThread = count / threadsToMake ;
	while(count > 0)
	{
			//call my thread here 
		
	}
	
	
return 0 ;
}

