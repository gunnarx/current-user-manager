/*****************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * Copyright (c) 2012 Harman International Industries, Inc.
 * All rights reserved
 ****************************************************************/
#include "TestSetUser.h"


TestSetUser::TestSetUser(int testNo, int seatId, int userId): TestBase(testNo), mSeatId(seatId), mUserId(userId){
}


TestSetUser::~TestSetUser() {
}


void TestSetUser::prepare(std::vector<Client*>& clientVect, Controller * ctrl){
	this->Ctrl = ctrl;
	this->c=clientVect;
}


void TestSetUser::execute(){

	//check who occupies seat
	std::vector<int> clientsToWhomSendStop;
	for(unsigned int i=0; i<c.size();i++){
		if(c[i]->mSeatId==mSeatId && c[i]->mState!=Client::EClientStatus::eNotRegistered && c[i]->mState!=Client::EClientStatus::eStopped){
			clientsToWhomSendStop.push_back(i);
		}
	}

	std::vector<int> clientsToChangeUser;
	for(unsigned int i=0; i<c.size();i++){
		if(c[i]->mSeatId==mSeatId && c[i]->mState!=Client::EClientStatus::eNotRegistered){
			clientsToChangeUser.push_back(i);
		}
	}

	time_t begin;
	time(&begin);

	Ctrl->sendSetUser(mSeatId, mUserId);

	try{
		if(clientsToWhomSendStop.size()!=0){


			//wait for all stop signals;
			for(unsigned int i=0; i<clientsToWhomSendStop.size();i++){
				while(c[clientsToWhomSendStop[i]]->mState != Client::EClientStatus::eStopped) {
					if(difftime(time(0), begin) > _TIMEOUT_SECONDS_TESTWAITSFORRESPONSE_){
						throw 'p';
					}
				}


				c[clientsToWhomSendStop[i]]->sendStopped(c[clientsToChangeUser[i]]->mSessionId);
			}
		}

			//wait for all detected signals;
			for(unsigned int i=0; i<clientsToChangeUser.size();i++){
				while(c[clientsToChangeUser[i]]->mState != Client::EClientStatus::eDetected) {
					if(difftime(time(0), begin) > _TIMEOUT_SECONDS_TESTWAITSFORRESPONSE_){
						throw 'd';
					}
				}


				c[clientsToChangeUser[i]]->sendConfirm(c[clientsToChangeUser[i]]->mSessionId);
			}


			//wait for all synced signals;
			for(unsigned int i=0; i<clientsToChangeUser.size();i++){


				while(c[clientsToChangeUser[i]]->mState != Client::EClientStatus::eSynced) {
					if(difftime(time(0), begin) > _TIMEOUT_SECONDS_TESTWAITSFORRESPONSE_){
						throw 's';
					}
				}
			}
		//std::cout<<"TestSetUser successfully completed!\n";
	}
	catch(char e){
		if(e=='p') std::cout << "#timeout during TestSetUser while waiting for eStopped!\n";
		else if(e=='d') std::cout << "#timeout during TestSetUser while waiting for eDetected!\n";
		else if(e=='s') std::cout << "#timeout during TestSetUser while waiting for eSynced!\n";
		else std::cout<< "#Unexpected error during TestSetUser!\n";

		throw 'e';
	}
}
