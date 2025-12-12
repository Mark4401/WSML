#include"Test-internal.h"

#include<iostream>

using namespace std;

C_String_ Engine_name = "\nHello Altera Ody!";

void Hook_internal()
{
	int Num = 51;

	cout << Num << "\n" << Engine_name;
}
