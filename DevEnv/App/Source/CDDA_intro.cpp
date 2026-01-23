#include<iostream>
#include"cuda_functions.h"

using namespace std;

int main(int argc, char** argv)
{
	int vectorLength = 1024;
	if (argc >= 2)
	{
		vectorLength = atoi(argv[1]);
	}

	Intro(vectorLength);

	return 0;
}