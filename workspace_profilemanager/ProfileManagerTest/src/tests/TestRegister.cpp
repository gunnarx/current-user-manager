/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (c) 2012 Harman International Industries, Inc.
 * All rights reserved
 ****************************************************************/
#include "TestRegister.h"


TestRegister::TestRegister(int testNo, int clientId, int seatId): TestBase(testNo), mSeatId(seatId), mClientId(clientId){
}


TestRegister::~TestRegister() {
}


void TestRegister::prepare(std::vector<Client*> & clientVect, Controller * ctrl){
	this->Ctrl = ctrl;
	this->c = clientVect;
}


void TestRegister::execute(){
	if(mClientId < c.size()){

		time_t begin;
		time(&begin);

		c[mClientId]->sendRegisterMe(c[mClientId]->mAddressClientStub,c[mClientId]->mUID,mSeatId);

		try{
			while(c[mClientId]->mState != Client::EClientStatus::eDetected){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_TESTWAITSFORRESPONSE_){
					throw 'd';
				}
			}

			c[mClientId]->sendConfirm(c[mClientId]->mSessionId);

			while(c[mClientId]->mState != Client::EClientStatus::eSynced){
				if(difftime(time(0), begin) > _TIMEOUT_SECONDS_TESTWAITSFORRESPONSE_){
					throw 's';
				}
			}

			//std::cout<<"TestRegister successfully completed!\n";
		}
		catch(char e){
			if(e=='d') std::cout << "#timeout during TestRegister while waiting for eDetected!\n";
			else if(e=='s') std::cout << "#timeout during TestRegister while waiting for eSynced!\n";
			else std::cout<< "#Unexpected error during TestRegister!\n";

			throw 'e';
		}
	}
	else std::cout<<"#client does not exist\n";
}
