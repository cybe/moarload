call "%VS100COMNTOOLS%vsvars32.bat"
rd build /S /Q
mkdir build
cd build
cmake -G "NMake Makefiles JOM" -DCMAKE_BUILD_TYPE=Release ..
jom -j1
