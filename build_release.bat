call "%VS100COMNTOOLS%vsvars32.bat"
rm -rf build
mkdir build
cd build
cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release ..
nmake
