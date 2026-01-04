#include "WSSU.h"
#include"Runtime_variables.h"
#include"Win32_properties.h"
#include"Windows_Prop_And_Exm.h"

using namespace std;

void Default_Systen_info()
{
    Physical_Display_Properties();
}

void Get_Window_List()
{
    Top_Level_Windows();
}

void Init_Window(const wchar_t* title)
{
    Set_Window_info(title);
}

bool Events()
{
    return Queue();
}


