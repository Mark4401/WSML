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


#ifdef __cplusplus
extern "C" {
#endif
    
    ENGINE_API extern const char* Platform_name;

    ENGINE_API int Addition(int One, int two);
    ENGINE_API int Subtraction(int One, int two);

    ENGINE_API void Hook();

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ENGINE_H
