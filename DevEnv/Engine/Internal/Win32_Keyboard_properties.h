#ifndef WIN32_KEYBOARD_PROPERTIES
#define WIN32_KEYBOARD_PROPERTIES

#include"Runtime_variables.h"
#include"Win32_properties.h"


void Keyboard_Data(HWND Window_Data, UINT Message_Data, WPARAM WParam, LPARAM LParam);

int16_u Return_Virtual_Code();
int16_u Return_Key_Flags();
int16_u Return_Scan_Code();

#endif // !WIN32_KEYBOARD_PROPERTIES
