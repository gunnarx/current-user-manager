/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (C) 2014, GENIVI Alliance, Inc.
* All rights reserved
* Author: Przemyslaw Bularz
****************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>

#include "tests/TestBase.h"
#include "tests/TestSetUser.h"
#include "tests/TestRegister.h"
#include "tests/TestUnregister.h"
#include "tests/TestUnsetUser.h"

#include "FromProfileManager/ProfileManagerCfg.hpp"


#include "Client.h"
#include "Controller.h"

using namespace std;

/*
 * Returns next test instance
 */
TestBase* getNext(int i){
	switch (i) {
	case 0: return new TestSetUser(i,1,2);
	case 1: return new TestRegister(i,0,1);
	case 2: return new TestSetUser(i,1,0);
	case 3: return new TestRegister(i,1,1);
	case 4: return new TestSetUser(i,1,3);
	case 5: return new TestSetUser(i,1,2);
	case 6: return new TestSetUser(i,1,1);
	case 7: return new TestRegister(i,4,1);
	case 8: return new TestRegister(i,6,1);
	case 9: return new TestRegister(i,8,1);
	case 10: return new TestSetUser(i,1,2);

	case 11: return new TestUnregister(i,8);
	case 12: return new TestUnsetUser(i,1);

	case 13: return new TestUnregister(i,6);
	case 14: return new TestUnregister(i,4);
	case 15: return new TestSetUser(i,1,1);

	case 16: return new TestUnregister(i,1);
	case 17: return new TestSetUser(i,1,2);
	case 18: return new TestUnregister(i,0);

	};
	return 0;
}

/*
 * Creates a single client Config
 */
void createClient(ProfileManagerCfg & cfg, std::vector<Client*> & clientVect, ClientSelector appName, u_int32_t seatId, int32_t depLevel, int32_t timeOutMs)
{
	static int client_num;

	//create new client
	ProfileManagerCfg::ClientCfg clientCfg;
	clientCfg.mAppName = appName ;
	clientCfg.mSeatId = seatId;
	clientCfg.mDepLevel =  depLevel;
	clientCfg.mTimeOutMs =  timeOutMs;

	//push to client config
	cfg.mClientCfgs.push_back(clientCfg);

	//push to client vect
	clientVect.push_back(new Client(appName, client_num));

	client_num++;
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

/*
 * Creates PM config, writes it to "profile_manager_cfg" file
 * TODO: To be replaced by external sricpt
 */
void createConfig(ProfileManagerCfg & cfg, std::vector<Client*> & clientVect){

	unsigned int version = 0x0001 << 16 | 0x0000;

	cfg.mDefaultDepLevel = -1;
	cfg.mDefaultTimeOutMs = 5000;
	cfg.mNumOfSeats = 5;

	//name, seatId, depLevel, timeOutMs
	createClient(cfg, clientVect, "Client_0", -1, -1, 	cfg.mDefaultTimeOutMs);
	createClient(cfg, clientVect, "Client_1", -1, -1,	cfg.mDefaultTimeOutMs);
	createClient(cfg, clientVect, "Client_2", -1, -1, 	cfg.mDefaultTimeOutMs);
	createClient(cfg, clientVect, "Client_3", -1, -1, 	cfg.mDefaultTimeOutMs);
	createClient(cfg, clientVect, "Client_4", -1, 10, 	cfg.mDefaultTimeOutMs);
	createClient(cfg, clientVect, "Client_5", -1, 10, 	cfg.mDefaultTimeOutMs);
	createClient(cfg, clientVect, "Client_6", -1, 100, 	cfg.mDefaultTimeOutMs);
	createClient(cfg, clientVect, "Client_7", -1, 100, 	cfg.mDefaultTimeOutMs);
	createClient(cfg, clientVect, "Client_8", -1, 1000, cfg.mDefaultTimeOutMs);
	createClient(cfg, clientVect, "Client_9", -1, 1000, cfg.mDefaultTimeOutMs);
	/* to create another client just add another one here*/

	//write to file
	fstream cfgFile("profile_manager_cfg", ios::out | ios::binary);
	cfgFile.write((char*)&version, sizeof(unsigned int));
	cfgFile.write((char*)&(cfg.mDefaultDepLevel), sizeof(int));
	cfgFile.write((char*)&(cfg.mDefaultTimeOutMs), sizeof(unsigned int));
	cfgFile.write((char*)&(cfg.mNumOfSeats), sizeof(unsigned int));

	unsigned int numOfCfgs = cfg.mClientCfgs.size();

	cfgFile.write((char*)&numOfCfgs, sizeof(unsigned int));

	for (vector<ProfileManagerCfg::ClientCfg>::const_iterator cfgIt = cfg.mClientCfgs.begin(); cfgIt != cfg.mClientCfgs.end(); cfgIt++) {
		unsigned int nameLen = (*cfgIt).mAppName.size();
		cfgFile.write((char*)&nameLen, sizeof(unsigned int));
		cfgFile.write((*cfgIt).mAppName.data(), (*cfgIt).mAppName.size());
		cfgFile.write((char*)&((*cfgIt).mSeatId), sizeof(unsigned int));
		cfgFile.write((char*)&((*cfgIt).mDepLevel), sizeof(unsigned int));
		cfgFile.write((char*)&((*cfgIt).mTimeOutMs), sizeof(unsigned int));
	}

	cfgFile.close();

}

/*
 * Executes test sequence, display results
 */
int main(void) {
	/* create config: */
	std::vector<Client*> clientVect;

	ProfileManagerCfg cfg;
	createConfig( cfg, clientVect);

	std::cout << "p:PrflMgrCtrll[ap]" << std::endl;
	std::cout << "s:PrflMgr[ap]" << std::endl;
	for (int i = 0; i < _NUM_OF_TEST_CLIENTS_; i++){
		std::cout << "c" << i << ":Client_" << i << "[ap]" << std::endl;
	}
	std::cout << endl;


	/* Create Controller */
	Controller * ptrController = new Controller();


	/* Start test sequence */
	int testCtr = 0;
	int testErrorRetryNum = 0;

	TestBase* CurrentTest = getNext(testCtr);
	bool success = true;

	while (CurrentTest != 0){
		std::cout << "[c Test " << testCtr << "]" << std::endl;
		CurrentTest->prepare(clientVect , ptrController);

		try{
			CurrentTest->execute();

			if (CurrentTest!=0){
				delete CurrentTest;
				CurrentTest=0;
			}
			testCtr++;
			CurrentTest = getNext(testCtr);

			//wait some time for response (needed only to keep test results in proper order)
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			std::cout << "[/c]" << std::endl;
		}
		catch(char e){
			/* in case of error: */
			if(e =='e' && testErrorRetryNum < _MAX_NUM_OF_TEST_ERROR_RETRY_) std::cout<<"#Test error, relunching test again\n";
			else if(e =='e') std::cout<<"#Test error, aborting test execution\n";
			else  std::cout<<"#Unknown test error, aborting test execution\n";

			if (CurrentTest!=0){

				delete CurrentTest;
				CurrentTest=0;
			}
			testErrorRetryNum++;
			std::cout << "[/c]" << std::endl;

			CurrentTest = getNext(testCtr);
			if(testErrorRetryNum < _MAX_NUM_OF_TEST_ERROR_RETRY_) continue;

			success = false;
			break;
		}
	}

	std::cout<<"\n#testErrorRetryNum: "<<testErrorRetryNum <<std::endl;

	//some time to wait for all massages (needed only as PM test ends faster than PM messages arrives to PM test)
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	if (success) {
		printf("#FINISHED SUCCESSFULL!\n");
	} else {
		printf("#FAILED!\n");
	}

	return 0;
}


