#include "openclbinder.h"



#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>

class OpenCl_1_0_Binder::Loader
{
public:
    Loader(const std::string& libraryPath) {
        HMODULE handle = LoadLibrary(libraryPath.c_str());
        if (handle == nullptr) {
            throw OpenClException("Failed to open library: " + libraryPath,
                    GetLastError());
        }
        libraryHandle = handle;
    }
    ~Loader() {
        FreeLibrary(libraryHandle);
    }
    template<class T> T bindFunction(const std::string& name) {
        FARPROC pointer = GetProcAddress(libraryHandle, name.c_str());
        if (pointer == nullptr) {
            throw OpenClException("Failed to bind function: " + name,
                    GetLastError());
        }
        return reinterpret_cast<T>(pointer);
    }
private:
    HMODULE libraryHandle;
};

#else // _WIN32

#include <dlfcn.h>

class OpenCl_1_0_Binder::Loader
{
public:
    Loader(const std::string& libraryPath) {
        void* handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
        if (handle == nullptr) {
            throw OpenClException(dlerror());
        }
        libraryHandle = handle;
    }
    ~Loader() {
        dlclose(libraryHandle);
    }
    template<class T> T bindFunction(const std::string& name) {
        void* pointer = dlsym(libraryHandle, name.c_str());
        if (pointer == nullptr) {
            throw OpenClException(dlerror());
        }
        // -pedantic complains about direct void* to function pointer cast.
        return reinterpret_cast<T>(reinterpret_cast<size_t>(pointer));
    }
private:
    void* libraryHandle;
};

#endif // _WIN32



#define OCLB_BIND_POINTER(function) \
        ,function(loader->bindFunction<decltype(function)>(#function))



/**
 * Loads an OpenCL library and binds pointers to the library functions.
 * @throws OpenClException if the library cannot be opened or is an older
 * version.
 * @param libraryPath path of the .dll or .so to load.
 */
OpenCl_1_0_Binder::OpenCl_1_0_Binder(const std::string& libraryPath):
    loader(new Loader(libraryPath))
    OCLB_PROCESS_CL_1_0_FUNCTIONS(OCLB_BIND_POINTER)
{}



OpenCl_1_0_Binder::~OpenCl_1_0_Binder() = default;



OpenCl_1_1_Binder::OpenCl_1_1_Binder(const std::string& libraryPath):
    OpenCl_1_0_Binder(libraryPath)
    OCLB_PROCESS_CL_1_1_FUNCTIONS(OCLB_BIND_POINTER)
{}



OpenCl_1_2_Binder::OpenCl_1_2_Binder(const std::string& libraryPath):
    OpenCl_1_1_Binder(libraryPath)
    OCLB_PROCESS_CL_1_2_FUNCTIONS(OCLB_BIND_POINTER)
{}



OpenCl_2_0_Binder::OpenCl_2_0_Binder(const std::string& libraryPath):
    OpenCl_1_2_Binder(libraryPath)
    OCLB_PROCESS_CL_2_0_FUNCTIONS(OCLB_BIND_POINTER)
{}
