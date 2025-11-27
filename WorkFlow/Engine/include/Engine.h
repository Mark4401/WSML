#ifndef ENGINE_H
#define ENGINE_H

#ifdef _WIN32
#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
#else
#define ENGINE_API
#endif

#include <cstdint>

// ------------------------------
// Example engine global
// ------------------------------

// ------------------------------
// CUDA wrapper interface (C linkage)
// ------------------------------
#ifdef __cplusplus
extern "C" {
#endif

    // Wrapper function exposed to app
    ENGINE_API void Engine_FindPerfectNumbers(int a, int b, int c, int d);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ENGINE_H


/*
//int Engine_Number = 3;
*/