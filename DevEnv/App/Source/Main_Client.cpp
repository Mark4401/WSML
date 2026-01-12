#include<WSML/WSML.h>
#include <iostream>

using namespace std;

int main(int argv, char* argc[])
{
    cout << "\ncalled from an C++ file! :p\n\n";

    Init_Program(DPI_AWARENESS_FALSE);

    //Init_Window(L"Test_Window! ;P | WSML i.e (WIndowing & State Management Library)",
    //    800,800, true, POS_TOP_RIGHT);
    
    int Width = 2560, Height = 400;

    Init_Window(L"Test_Window! Top Left", Width, Height, false, POS_TOP_LEFT);
    //Init_Window(L"Test_Window! top Center", Width, Height, true , POS_TOP_CENTER);
    //Init_Window(L"Test_Window! top Right", Width, Height, false, POS_TOP_RIGHT);
    //Init_Window(L"Test_Window! Center Left", Width, Height, true, CENTER_LEFT);
    //Init_Window(L"Test_Window! Center Left", Width, Height, false, CENTER);
    //Init_Window(L"Test_Window! Center Left", Width, Height, true, CENTER_RIGHT);
    //Init_Window(L"Test_Window! Center Left", Width, Height, false, POS_BOTTOM_LEFT);
    //Init_Window(L"Test_Window! Center Left", Width, Height, true, POS_BOTTOM_CENTER);
    //Init_Window(L"Test_Window! Center Left", Width, Height, false , POS_BOTTOM_RIGHT);

    Process_Lists();

    while (System_Queue())
    {
        //return true;
    };

    //Retrieve_All_Active_Window_instances();

    return 0;
}