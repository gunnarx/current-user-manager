/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
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
	while (mClientId >= c.size()){
		c.push_back(new Client("generic",c.size()));
	}


	{
		//std::cout<<"mClientId: " << mClientId <<"\n";
		//std::cout<<"c.size(): " << c.size() <<"\n";

		time_t begin;
		time(&begin);

		c[mClientId]->sendRegisterMe(c[mClientId]->mUID,mSeatId);

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
	//else std::cout<<"#client does not exist\n";
}
