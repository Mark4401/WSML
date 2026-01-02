#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<WSSU.h>

//using namespace std;


int main(int argv, char* argc[])
//int WinMain()
{
	Default_Systen_info();

	Get_Window_List();

	printf("DLL/LIB - Call From C! :P");

	return 0;
}
