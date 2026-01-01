#include "Windows_Prop_And_Exm.h"
#include<iostream>

using namespace std;

void Physical_Display_Properties()
{	//HWND DEF_handle =  GetWindow(GetDesktopWindow(), GW_HWNDFIRST);

	HWND DEF_handle = GetDesktopWindow();

	// WIll stop GetWindowRect from complaining of retying 
	if (!DEF_handle ) { cerr << GetLastError() << "\n"; return; };

	cout << "(MEMORY ADDRS) of DEF: " << DEF_handle << "\n\n";

	RECT DEF_Handle_Dimensions;

	//GetClientRect(DEF_handle, &DEF_Handle_Dimensions);
	if (!GetWindowRect(DEF_handle, &DEF_Handle_Dimensions)) { cerr << GetLastError() << "\n"; return; };

	cout << "Primary Physical Display Properties:\n\n";
	cout << "DEF (LEFT): " << DEF_Handle_Dimensions.left << "\t" << "DEF (RIGHT): " << DEF_Handle_Dimensions.right << "\n"
		<< "DEF (TOP): " << DEF_Handle_Dimensions.top << "\t" << "DEF (BOTTOM): " << DEF_Handle_Dimensions.bottom << "\n";
}
