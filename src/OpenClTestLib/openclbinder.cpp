#include "openclbinder.h"

#include <dlfcn.h>



OpenClBinder::OpenClBinder(const std::string& libraryPath):
    libraryHandle(openLibrary(libraryPath), &dlclose)
    #define OCLB_BIND_POINTER(function) \
            , function(bindFunction<decltype(function)>(#function))
    OCLB_PROCESS_OPEN_CL_FUNCTIONS(OCLB_BIND_POINTER)
    #undef OCLB_BIND_POINTER
{}



void* OpenClBinder::openLibrary(const std::string& path)
{
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (handle == nullptr) {
        throw OpenClException(dlerror());
    }
    return handle;
}



template<class T>
T OpenClBinder::bindFunction(const std::string& name)
{
    void* pointer = dlsym(libraryHandle.get(), name.c_str());
    if (pointer == nullptr) {
        throw OpenClException(dlerror());
    }
    return reinterpret_cast<T>(pointer);
}
