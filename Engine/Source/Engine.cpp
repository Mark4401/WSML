#include "Engine.h"
#include "Test-internal.h"
#include <iostream>

const char* Platform_name = Engine_name;

int Addition(int One, int two)
{
	return One + two;
}

int Subtraction(int One, int two)
{
	return One - two;
}

void Hook()
{
	Hook_internal();
}

