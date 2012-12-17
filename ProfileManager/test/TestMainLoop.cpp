/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#include <iostream>
#include <pthread.h>
#include <cstdio>

#include "EventReceiver.h"
#include "ServerLoop.h"
#include "TestSetUser.h"
#include "TestRegister.h"
#include "TestFactory.h"


using namespace std;

ServerLoop* mSLoop = 0;


TestBase* getNext(int i){
   switch (i) {
   case 0: return new TestSetUser(i,1,2);
   case 1: return new TestRegister(i,0,1);
   case 2: return new TestSetUser(i,1,0);
   case 3: return new TestRegister(i,1,1);
   case 4: return new TestSetUser(i,1,-1);
   case 5: return new TestSetUser(i,1,2);
   case 6: return new TestSetUser(i,1,1);
   case 7: return new TestRegister(i,4,1);
   case 8: return new TestRegister(i,6,1);
   case 9: return new TestRegister(i,8,1);
   case 10: return new TestSetUser(i,1,2);
   };
   return 0;
}


void* startSeverLoop(void *){
   mSLoop->run();
   return 0;
}


int main(void) {
   //lProfileManagerLogic logic = new ProfileManagerLogic()
   EventMessageQ<PrflMgrTestTypes::SrvMsg>* serverQ = new EventMessageQ<PrflMgrTestTypes::SrvMsg>();
   EventMessageQ<PrflMgrTestTypes::ClientMsg>* clientQ = new EventMessageQ<PrflMgrTestTypes::ClientMsg>();

   //TestModel* model = new TestModel();

   std::cout << "p:Plugin[ap]" << std::endl;
   std::cout << "s:PrflMgr[ap]" << std::endl;

   for (int i = 0; i < NUM_OF_TEST_CLIENTS; i++){
      std::cout << "c" << i << ":Client_" << i << "[ap]" << std::endl;
   }

   std::cout << endl;


   EventReceiver* evReceiver = new EventReceiver(*clientQ, *serverQ);

   TestFactory* factory = new TestFactory(evReceiver);

   mSLoop = new ServerLoop(*serverQ, factory);
   pthread_t sthread;
   pthread_create(&sthread, NULL, startSeverLoop, NULL);
   int testCtr = 0;
   TestBase* nextTest = getNext(testCtr);
   bool success = true;
   while (nextTest != 0){
      nextTest->prepare(evReceiver);
      std::cout << "[c Test " << testCtr << "]" << std::endl;
      if (evReceiver->execute(*nextTest)) {
         delete nextTest;
         testCtr++;
         nextTest = getNext(testCtr);
      } else {
         delete nextTest;
         success = false;
         nextTest = 0;
      }
      std::cout << "[/c]" << std::endl;

   }
   PrflMgrTestTypes::SrvMsg m;
   m.mReceiveSelector = PrflMgrTestTypes::eSrvInvalid;
   serverQ->push(m);
   serverQ->notify();
   pthread_join( sthread, NULL);
   if (success) {
      printf("FINISHED SUCCESSFULL!\n");
   } else {
      printf("FAILED!\n");
   }
}


