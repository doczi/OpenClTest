Compilation:
cmake path/to/OpenClTest
make

Execution on linux (tested on Ubuntu 14.04 64 bit):
./src/OpenClTestApp/OpenClTestApp /path/to/libOpenCL.so [json/xml]
e.g.
src/OpenClTestApp/OpenClTestApp /opt/AMDAPP/lib/x86_64/libOpenCL.so json

I did some testing on Windows7 / MinGW too. It compiles and runs if it finds
the .dlls. 

