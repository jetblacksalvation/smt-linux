!bin#bash
mkdir build
cd build
cmake -S .. -B . -DCMAKE_INSTALL_PREFIX=install -DBUILD_SHARED_LIBS=FALSE


make
echo "good to run now.." 

