#!/bin/bash
mkdir -p cmakeTmpPM		&&
mkdir -p cmakeTmpPMTest		&&
cd cmakeTmpPM		 	&&
cmake ../ProfileManager		&&
make 				&&
mkdir -p ../exec		&&
mv ProfileManager ../exec/ 	&&
cd ../cmakeTmpPMTest	 	&&
cmake ../ProfileManagerTest	&&
make				&&
mv ProfileManagerTest ../exec/	&&
cp ../ProfileManager/profile_manager_cfg ../exec &&
echo "Executables moved to /exec/"


