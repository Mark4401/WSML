#include"Win32_Phys_Monitor_Properties.h"

using namespace std;

void Physical_Monitor_Position(HWND Monitor_handle)
{
	RECT			Window_Dimensions = { };
	MONITORINFO		Monitor_info = { };

	HMONITOR Monitor = MonitorFromPoint
	(
		POINT{ 0, 0 },
		MONITOR_DEFAULTTONEAREST
	);

	Monitor_info.cbSize = sizeof(Monitor_info);

	GetMonitorInfoW(Monitor, &Monitor_info);

	GetWindowRect(Monitor_handle, &Window_Dimensions);

	cout << "Window Dimensions Top: " << Window_Dimensions.top << "\n";
	cout << "Window Dimensions Bottom: " << Window_Dimensions.bottom << "\n";
	cout << "Window Dimensions Left: " << Window_Dimensions.left << "\n";
	cout << "Window Dimensions Right: " << Window_Dimensions.right << "\n";

	int Window_Width_Dim = Window_Dimensions.right - Window_Dimensions.left;
	int Window_Height_Dim = Window_Dimensions.bottom - Window_Dimensions.top;


	int Perfered_Monitor_X_Pos = Monitor_info.rcWork.right - Window_Width_Dim;
	int Perfered_Monitor_Y_Pos = Monitor_info.rcWork.top;

	BOOL Active_Pos = SetWindowPos(
		Monitor_handle, nullptr,
		Perfered_Monitor_X_Pos, Perfered_Monitor_Y_Pos, 0, 0,
		SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE
	);

	if (!Active_Pos)
	{
		cout << GetLastError();
	}
}

#define INITIALX_96DPI 50 
#define INITIALY_96DPI 50 
#define INITIALWIDTH_96DPI 100 
#define INITIALHEIGHT_96DPI 50 

Physical_Screen_Info Physical_Monitor_Dimensions(HWND Monitor_handle)
{
	Physical_Screen_Info info = {};
	HMONITOR Physical_Monitor_Info = MonitorFromPoint
	(
		POINT{ 0, 0 },
		MONITOR_DEFAULTTONEAREST
	);

	MONITORINFO Mon_info = { };

	Mon_info.cbSize = sizeof(Mon_info);
	
	GetMonitorInfoW(Physical_Monitor_Info, &Mon_info);

	// Maximum 
	int Physical_Screen_X_Minimum = Mon_info.rcWork.left;
	int Physical_Screen_X_Maximum = Mon_info.rcWork.right;

	int Physical_Screen_Y_Minimum = Mon_info.rcWork.top;
	int Physical_Screen_Y_Maximum = Mon_info.rcWork.bottom;


	info.X_Min = Physical_Screen_X_Minimum, info.X_Max = Physical_Screen_X_Maximum,
	info.Y_Min = Physical_Screen_Y_Minimum, info.Y_Max = Physical_Screen_Y_Maximum;
	
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	
	int32_u DPI_ref_amount = GetDpiForWindow(Monitor_handle);

	int dpi_Scaled_X_return_data = MulDiv(INITIALX_96DPI, DPI_ref_amount, USER_DEFAULT_SCREEN_DPI);
	int dpi_Scaled_Y_return_data = MulDiv(INITIALY_96DPI, DPI_ref_amount, USER_DEFAULT_SCREEN_DPI);
	int dpi_Scaled_Width_return_data = MulDiv(INITIALWIDTH_96DPI, DPI_ref_amount, USER_DEFAULT_SCREEN_DPI);
	int dpi_Scaled_Height_return_data = MulDiv(INITIALHEIGHT_96DPI, DPI_ref_amount, USER_DEFAULT_SCREEN_DPI);

	info.dpi_Scaled_Height = dpi_Scaled_Height_return_data, info.dpi_Scaled_Width = dpi_Scaled_Width_return_data,
	info.dpi_Scaled_X = dpi_Scaled_X_return_data, info.dpi_Scaled_Y = dpi_Scaled_Y_return_data;

	return info;
}
