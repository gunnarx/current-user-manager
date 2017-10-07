/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
****************************************************************/

#include "TestUnregister.h"


TestUnregister::TestUnregister(int testNo, int clientId): TestBase(testNo), mClientId(clientId){
}


TestUnregister::~TestUnregister() {
}


void TestUnregister::prepare(std::vector<Client*> & clientVect, Controller * ctrl){
	this->Ctrl = ctrl;
	this->c = clientVect;
}


void TestUnregister::execute(){
	if(mClientId < c.size()){

		time_t begin;
		time(&begin);

		c[mClientId]->sendUnregisterMe(c[mClientId]->mAddressClientStub,c[mClientId]->mUID,c[mClientId]->mSeatId);

	}
	else std::cout<<"#client does not exist\n";
}
