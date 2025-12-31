#include"Win32_Keyboard_properties.h"

#define BIT_LENGTH_8    0xFF
#define BIT_LENGTH_16   0xFFFF

int16_u Virtual_Key_Code    = 0;
int16_u Key_Flags           = 0;
int16_u Scan_Code           = 0;
int16_u Repeat_Count        = 0;
bool Key_extended_Data     = false;
bool Key_Pressed            = false;
bool Key_Released           = false;

using namespace std;

void Keyboard_Data(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	
    Virtual_Key_Code    = static_cast<int16_u>(WParam);
    Key_Flags           = static_cast<int16_u>((LParam >> 16) & BIT_LENGTH_16);
    Scan_Code           = static_cast<int8_u>((Key_Flags) & BIT_LENGTH_8);

    Key_extended_Data = (Key_Flags & KF_EXTENDED) == KF_EXTENDED;

    if (Key_extended_Data) { Scan_Code = MAKEWORD(Scan_Code, 0xE0); };
        
    Repeat_Count = static_cast<int16_u>(LParam & BIT_LENGTH_16);
        
    Key_Pressed     = (Key_Flags & KF_REPEAT) == KF_REPEAT;
    Key_Released    = (Key_Flags & KF_UP) == KF_UP;

    switch (Virtual_Key_Code)
    {
    case VK_SHIFT:   
    case VK_CONTROL: 
    case VK_MENU:    
        Virtual_Key_Code = LOWORD(MapVirtualKeyW(Scan_Code, MAPVK_VSC_TO_VK_EX));
        break;
    }
}

int16_u Return_Virtual_Code() { return Virtual_Key_Code; }
int16_u Return_Key_Flags() { return Key_Flags; }
int16_u Return_Scan_Code() { return Scan_Code; }


WORD vkCode = 0; 
WORD keyFlags = 0;
WORD scanCode = 0;

void WIN32_Keyboard_Data(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
    vkCode = LOWORD(WParam);                                

    keyFlags = HIWORD(LParam);

    scanCode = LOBYTE(keyFlags);                        
    BOOL isExtendedKey = (keyFlags & KF_EXTENDED) == KF_EXTENDED; 

    if (isExtendedKey)
        scanCode = MAKEWORD(scanCode, 0xE0);

    BOOL wasKeyDown = (keyFlags & KF_REPEAT) == KF_REPEAT;        
    WORD repeatCount = LOWORD(LParam);                            

    BOOL isKeyReleased = (keyFlags & KF_UP) == KF_UP;            


    switch (vkCode)
    {
    case VK_SHIFT:   
    case VK_CONTROL: 
    case VK_MENU:    
        vkCode = LOWORD(MapVirtualKeyW(scanCode, MAPVK_VSC_TO_VK_EX));
        break;
    }
}


WORD Return_Vk() { return vkCode;  };
WORD Return_KeyFlags() { return keyFlags; };
WORD Return_ScanCode() { return scanCode; };

#define INITIALX_96DPI 50 
#define INITIALY_96DPI 50 
#define INITIALWIDTH_96DPI 100 
#define INITIALHEIGHT_96DPI 50 

// DPI scale the position and size of the button control 
void UpdateButtonLayoutForDpi(HWND hWnd)
{
    int iDpi = GetDpiForWindow(hWnd);
    int dpiScaledX = MulDiv(INITIALX_96DPI, iDpi, USER_DEFAULT_SCREEN_DPI);
    int dpiScaledY = MulDiv(INITIALY_96DPI, iDpi, USER_DEFAULT_SCREEN_DPI);
    int dpiScaledWidth = MulDiv(INITIALWIDTH_96DPI, iDpi, USER_DEFAULT_SCREEN_DPI);
    int dpiScaledHeight = MulDiv(INITIALHEIGHT_96DPI, iDpi, USER_DEFAULT_SCREEN_DPI);
    SetWindowPos(hWnd, hWnd, dpiScaledX, dpiScaledY, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);
}
