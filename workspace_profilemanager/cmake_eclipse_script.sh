#!/bin/bash
cd cmake_ProfileManager 		&&
cmake -G"Eclipse CDT4 - Unix Makefiles" &&	
cd ../cmake_ProfileManagerTest 		&&
cmake -G"Eclipse CDT4 - Unix Makefiles" &&
echo "Success"

#lots of info how to run it:
#http://wiki.ros.org/IDEs
