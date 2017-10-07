/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
****************************************************************/

#include "TestUnsetUser.h"


TestUnsetUser::TestUnsetUser(int testNo, int seatId): TestBase(testNo), mSeatId(seatId){
}


TestUnsetUser::~TestUnsetUser() {
}


void TestUnsetUser::prepare(std::vector<Client*>& clientVect, Controller * ctrl){
	this->Ctrl = ctrl;
	this->c=clientVect;
}


void TestUnsetUser::execute(){

	//check who occupies seat
	std::vector<int> clientsToUnset;
	for(unsigned int i=0; i<c.size();i++){
		if(c[i]->mSeatId==mSeatId && c[i]->mState!=Client::EClientStatus::eNotRegistered){
			clientsToUnset.push_back(i);
		}
	}

	time_t begin;
	time(&begin);

	Ctrl->sendUnsetUser(mSeatId);

	try{
		if(clientsToUnset.size()!=0){

			//wait for all stop signals;
			for(unsigned int i=0; i<clientsToUnset.size();i++){
				while(c[clientsToUnset[i]]->mState != Client::EClientStatus::eStopped) {
					if(difftime(time(0), begin) > _TIMEOUT_SECONDS_TESTWAITSFORRESPONSE_){
						throw 's';
					}
				}
				c[clientsToUnset[i]]->sendStopped(c[clientsToUnset[i]]->mSessionId);
			}
		}
	}
	catch(char e){
		if(e=='s') std::cout << "#timeout during TestUnsetUser while waiting for eStopped!\n";
		else std::cout<< "#Unexpected error during TestUnsetUser!\n";

		throw 'e';
	}
}
