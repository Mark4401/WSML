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
}

struct Window_Data
{
};

Window_Data* DEFALUT_WINDOW;

WNDCLASSEXW DEFALUT_WINDOW_CALSS = { };

LRESULT CALLBACK
Default_Window_Proc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{

	switch (Message)
	{
		//case WM_NCCREATE:
		//{
		//	CREATESTRUCTW* WIndow_Create_Struct_Binding = reinterpret_cast<CREATESTRUCTW*>(LParam);

		//	WIN32_CLIENT* Client_Data_Binding = reinterpret_cast<WIN32_CLIENT*>(WIndow_Create_Struct_Binding->lpCreateParams);

		//	SetWindowLongPtrW(Window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(Client_Data_Binding));

		//	Client_Data_Binding->Client_Window_Handle = Window;
		//	
		//	return TRUE;
		//}
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	{
		/*
		Keyboard_Data(Window, Message, WParam, LParam);

		WIN32_Keyboard_Data(Window, Message, WParam, LParam);

		cout << "| My Method \t" << Return_Virtual_Code() << "\t | Win32  " << Return_Vk() << "\t | VK CODE  \n";
		cout << "| My Method \t" << Return_Key_Flags() << "\t | Win32  " << Return_KeyFlags() << "\t | KEY FLAG    \n";
		cout << "| My Method \t" << Return_Scan_Code() << "\t | Win32  " << Return_ScanCode() << "\t | SCAN CODE   \n\n";
		*/
		break;
	}
	case WM_DESTROY:
	{
		cout << "\nWindow closed\n";

		PostQuitMessage(0);

		return 0;
	}
	case WM_PAINT:
	{
		// Window painting at resize 
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(Window, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(Window, &ps);
	}
	return 0;
	}
	return DefWindowProc(Window, Message, WParam, LParam);
};

void Set_Window_info()
{
	//DEFALUT_WINDOW_CALSS = { };

	DEFALUT_WINDOW_CALSS.cbSize				= sizeof(WNDCLASSEXW);
	DEFALUT_WINDOW_CALSS.style				= 0;
	DEFALUT_WINDOW_CALSS.lpfnWndProc		= Default_Window_Proc;
	DEFALUT_WINDOW_CALSS.hInstance			= GetModuleHandle(nullptr);
	DEFALUT_WINDOW_CALSS.lpszClassName		= L"DEF_WINDOW_CALSS";
	
	if (!RegisterClassExW(&DEFALUT_WINDOW_CALSS)) { cout << GetLastError() << "\n"; };

	HWND DEF_Screen = CreateWindowExW
	(
		0,
		DEFALUT_WINDOW_CALSS.lpszClassName,
		L"DEF_Window_Screen",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		500,
		120,
		800,
		800,
		NULL,
		NULL,
		DEFALUT_WINDOW_CALSS.hInstance,
		NULL
	);

	//ShowWindow(DEF_Screen, SW_SHOW);

}
bool Queue()
{
	bool Active_state = true;
	MSG Message_Loop = { };

	while (PeekMessageW(&Message_Loop, 0, 0, 0, PM_REMOVE))
	{
		if (Message_Loop.message == WM_QUIT)
		{
			return Active_state = false;
		}

		TranslateMessage(&Message_Loop);
		DispatchMessageW(&Message_Loop);
	}

	return Active_state = true;
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
	BOOL DPI_Active_Awareness_Context_State = SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	
	if (DPI_Active_Awareness_Context_State == true) (cout << "\n(DPI_Active_Awareness_Context_State):  ACTIVE" << "\n\n");
	if (DPI_Active_Awareness_Context_State == false) (cout << "\n(DPI_Active_Awareness_Context_State):  OFF"<< "\n\n");
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
