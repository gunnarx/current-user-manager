#!/bin/bash
cd cmake_ProfileManager 	&&
cmake . 			&&
make 				&&
mkdir -p ../exec		&&
mv ProfileManager ../exec/ 	&&
cd ../cmake_ProfileManagerTest 	&&
cmake . 			&&
make				&&
mv ProfileManagerTest ../exec/	&&
echo "Success"


