#!/bin/bash
cd cmake_ProfileManager 	&&
cmake . 			&&
make 				&&
mv ProfileManager ../exec/ 	&&
cd ../cmake_ProfileManagerTest 	&&
cmake . 			&&
make				&&
mv ProfileManagerTest ../exec/	&&
echo "Success"


