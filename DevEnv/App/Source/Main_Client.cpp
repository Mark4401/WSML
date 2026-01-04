#include <WSSU.h>
#include <iostream>

using namespace std;

int main(int argv, char* argc[])
{
    Default_Systen_info();

    Get_Window_List();

    cout << "called from an C++ file! :p\n\n";

    Init_Window(L"One");

    while (Events())
    {
        //return true;
    };

    return 0;
}


