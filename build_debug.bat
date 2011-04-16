call "%VS100COMNTOOLS%vsvars32.bat"
cd build
cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
nmake