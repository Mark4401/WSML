#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<WSSU.h>

//using namespace std;


int main(int argv, char* argc[])
//int WinMain()
{
	printf("DLL/LIB - Call From C! :P");

    Default_Systen_info();

    Init_Window(L"One", 2000, 1460, true, CENTER, DEAFULT);

    Process_Lists();

    while (Events())
    {
        //return true;
    };

	return 0;
}
