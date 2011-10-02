#!/usr/bin/env sh

# clean old files
rm pyload.cpp pyload.h pyload_constants.cpp pyload_constants.h pyload_types.cpp pyload_types.h

# generate thrift
thrift -v --strict --gen cpp -out . pyload.thrift

# delete non needed files
rm Pyload_server.skeleton.cpp

# we use lowercase filenames
mv Pyload.cpp pyload.cpp
mv Pyload.h pyload.h

# fix include
sed -e "s/#include \"Pyload.h\"/#include \"pyload.h\"/g" -i pyload.cpp
