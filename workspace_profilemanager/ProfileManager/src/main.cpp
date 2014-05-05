/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#include <iostream>
#include "ProfileManagerMain.h"

int main(){

	//Runs forever...
	ProfileManagerMain* prof_mgmt = new ProfileManagerMain();

	delete prof_mgmt;
	return 0;
}
