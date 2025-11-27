#include "Engine.h"
#include <iostream>
//#include "main.cu" // Host wrapper for CUDA kernel

// ------------------------------
// Example global variable
// ------------------------------


// ------------------------------
// DLL wrapper: exposes CUDA functionality
// ------------------------------
void Engine_FindPerfectNumbers(int a, int b, int c, int d)
{
    // Validate inputs
    if (a <= 0 || b <= 0 || c <= 0 || d <= 0)
    {
        std::cerr << "[Engine] Invalid input: numbers must be positive.\n";
        return;
    }

    if (a > 100000 || b > 100000 || c > 100000 || d > 100000)
    {
        std::cerr << "[Engine] Invalid input: max value is 100000.\n";
        return;
    }

    // Call the host wrapper which launches the CUDA kernel
    //FindPerfectNumbers(a, b, c, d);
}
