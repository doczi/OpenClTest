#include "openclbinder.h"



#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>

class OpenClBinder::Loader
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

class OpenClBinder::Loader
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
        void* pointer = dlsym(libraryHandle.get(), name.c_str());
        if (pointer == nullptr) {
            throw OpenClException(dlerror());
        }
        return reinterpret_cast<T>(pointer);
    }
private:
    void* libraryHandle;
};

#endif // _WIN32



OpenClBinder::OpenClBinder(const std::string& libraryPath):
    loader(new Loader(libraryPath))
    #define OCLB_BIND_POINTER(function) \
            , function(loader->bindFunction<decltype(function)>(#function))
    OCLB_PROCESS_OPEN_CL_FUNCTIONS(OCLB_BIND_POINTER)
    #undef OCLB_BIND_POINTER
{}



OpenClBinder::~OpenClBinder() = default;
