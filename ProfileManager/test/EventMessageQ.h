/*****************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
* Copyright (c) 2012 Harman International Industries, Inc.
* All rights reserved
****************************************************************/
#ifndef EVENTMESSAGEQ_H_
#define EVENTMESSAGEQ_H_

#include <pthread.h>
#include <list>
#include <string>
#include "../include/CommonApi.h"
#include <stdlib.h>

int selector2Int(ClientSelector s);

const char* selector2Char(ClientSelector s);

/**
 * Types, states, structs needed to build up the test enviornment
 */
namespace PrflMgrTestTypes {
   enum EClientMsgType {
      eClientInvalid, eClientDetected, eClientSynchronized, eClientStop
   };

   struct ClientMsg {
      EClientMsgType    mReceiveSelector;
      ClientSelector    mClientSelector;
      std::string       mMessage;
      int               mSeatId;
      int               mUserId;
      uint64_t          mSessionId;
   };

   enum ESrvMsgType {
      eSrvInvalid, eSrvRegister, eSrvUnregister, eSrvConfirm, eSrvStopped, eSrvSetUser
   };

   struct SrvMsg {
      int            mTestNo;
      ESrvMsgType    mReceiveSelector;
      ClientSelector mClientSelector;
      std::string    mAppId;
      int            mSeatId;
      uint64_t       mSessionId;
      int            mUserId;
   };

   enum ETestEventType {
      eTSetUser, eTRegister, eTDetected, eTConfirm, eTSynced, eTStop, eTStopped
   };

   struct TestEvent {
      ETestEventType mT;
      unsigned int   mPayload;
      bool           mOccured;
   };
}


/**
 * This class provides a blocking queue to establish an event driven
 */
template<class TheEventMessage>
class EventMessageQ {
private:
   pthread_mutex_t               mReceiveCondMutex;
   pthread_cond_t                mReceiveCond;
   std::list<TheEventMessage>    mSrvQ;

public:
   EventMessageQ();
   virtual ~EventMessageQ(){};

   void              push(TheEventMessage m);
   void              notify();
   TheEventMessage   poll();
   bool              empty();

};

template<class TheEventMessage> EventMessageQ<TheEventMessage>::EventMessageQ()
: mReceiveCondMutex(PTHREAD_MUTEX_INITIALIZER)
, mReceiveCond(PTHREAD_COND_INITIALIZER)
, mSrvQ(){
}

template<class TheEventMessage> void EventMessageQ<TheEventMessage>::push(TheEventMessage m){
   pthread_mutex_lock(&mReceiveCondMutex);
      mSrvQ.push_back(m);
   pthread_mutex_unlock(&mReceiveCondMutex);
}

template<class TheEventMessage> void EventMessageQ<TheEventMessage>::notify(){
   pthread_mutex_lock(&mReceiveCondMutex);
      pthread_cond_signal(&mReceiveCond);
   pthread_mutex_unlock(&mReceiveCondMutex);
}

template<class TheEventMessage> TheEventMessage EventMessageQ<TheEventMessage>::poll(){
   TheEventMessage m;
   pthread_mutex_lock(&mReceiveCondMutex);
      while (mSrvQ.empty()) {
         pthread_cond_wait(&mReceiveCond, &mReceiveCondMutex);
      }
      m = mSrvQ.front();
      mSrvQ.pop_front();
   pthread_mutex_unlock(&mReceiveCondMutex);
   return m;
}

template<class TheEventMessage> bool EventMessageQ<TheEventMessage>::empty(){
   bool empty;
   pthread_mutex_lock(&mReceiveCondMutex);
      empty = mSrvQ.empty();
   pthread_mutex_unlock(&mReceiveCondMutex);
   return empty;
}

#endif /* EVENTMESSAGEQ_H_ */
