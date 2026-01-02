#include "Windows_Prop_And_Exm.h"
#include<iostream>

using namespace std;

struct Window_handle_count
{
	int Count;
};

Window_handle_count Data;

BOOL CALLBACK
Enum_Windows_Proc(HWND Window_handle, LPARAM LParam)
{
	cout << "(Window_handle) : " << Window_handle << "\n";

	Data.Count++;

	return TRUE;
};

void Top_Level_Windows()
{
	EnumWindows(Enum_Windows_Proc, 0);

	cout << "\n(Top level Window Handle Count): " << Data.Count << "\n\n";
};


void Physical_Display_Properties()
{	
	/*
		Returns either  1 or 0 i.e. (TRUE or DALSE)
		
		- true if:
			- the program has Access to full Monitor/Display Physical Properties:
				- Hardware level resolution no-matter the current scale in windows settings.
		- false if:
			- the Program has Access ONLY to the virtual Monitor/Display Properties 
				- And will remain unaware of Hardware Resolution. Always Thinking the Scale is set to 100% 
	*/
	BOOL DPI_Actice_Awareness_Context_State = SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	
	if (DPI_Actice_Awareness_Context_State == true) (cout << "\n(DPI_Actice_Awareness_Context_State):  ACTIVE" << "\n\n");
	if (DPI_Actice_Awareness_Context_State == false) (cout << "\n(DPI_Actice_Awareness_Context_State):  OFF"<< "\n\n");
	//HWND DEF_handle =  GetWindow(GetDesktopWindow(), GW_HWNDFIRST);

	// DEF stands for Default; DEF is just my own short hand definition.
	HWND DEF_handle = GetDesktopWindow();

	// WIll stop GetWindowRect from complaining of retying 
	if (!DEF_handle ) { cerr << GetLastError() << "\n"; return; };

	cout << "(MEMORY ADDRS) of DEF: " << DEF_handle << "\n\n";

	RECT DEF_Handle_Dimensions;

	//GetClientRect(DEF_handle, &DEF_Handle_Dimensions);
	if (!GetWindowRect(DEF_handle, &DEF_Handle_Dimensions)) { cerr << GetLastError() << "\n"; return; };

	cout << "Primary Physical Display Properties:\n\n";
	cout << "DEF (LEFT): " << DEF_Handle_Dimensions.left << "\t" << "DEF (RIGHT): " << DEF_Handle_Dimensions.right << "\n"
		<< "DEF (TOP): " << DEF_Handle_Dimensions.top << "\t" << "DEF (BOTTOM): " << DEF_Handle_Dimensions.bottom << "\n\n";

	POINT DEF_Position = {0 , 0};

	HWND Position_handle = WindowFromPoint(DEF_Position);

	cout << "POS (ADDRS): " << Position_handle << "\n\n"
		<< "POS (X): " << DEF_Position.x << "\t" << "POS (Y): " << DEF_Position.y << "\n\n";
}
