/*
* This file was generated by the CommonAPI Generators. 
* Used org.genivi.commonapi.core 2.1.4.201311151436.
* Used org.franca.core 0.8.11.201401091023.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlStubDefault.h>

namespace org {
namespace genivi {
namespace profile_mgmt_ctrl {

ProfileManagerCtrlStubDefault::ProfileManagerCtrlStubDefault():
        remoteEventHandler_(this) {
}

ProfileManagerCtrlStubRemoteEvent* ProfileManagerCtrlStubDefault::initStubAdapter(const std::shared_ptr<ProfileManagerCtrlStubAdapter>& stubAdapter) {
    stubAdapter_ = stubAdapter;
    return &remoteEventHandler_;
}


void ProfileManagerCtrlStubDefault::registerMe(const std::shared_ptr<CommonAPI::ClientId> clientId, std::string consumerAddress, bool registerOnTimeOut, bool registerOnStateChangeStart, bool registerOnStateChangeStop, bool registerOnClientRegister, bool registerOnClientUnregister) {
    // Call old style methods in default 
    registerMe(consumerAddress, registerOnTimeOut, registerOnStateChangeStart, registerOnStateChangeStop, registerOnClientRegister, registerOnClientUnregister);
}
void ProfileManagerCtrlStubDefault::registerMe(std::string consumerAddress, bool registerOnTimeOut, bool registerOnStateChangeStart, bool registerOnStateChangeStop, bool registerOnClientRegister, bool registerOnClientUnregister) {
    // No operation in default
}

void ProfileManagerCtrlStubDefault::setUser(const std::shared_ptr<CommonAPI::ClientId> clientId, uint32_t userId, uint32_t seatId) {
    // Call old style methods in default 
    setUser(userId, seatId);
}
void ProfileManagerCtrlStubDefault::setUser(uint32_t userId, uint32_t seatId) {
    // No operation in default
}

void ProfileManagerCtrlStubDefault::unsetUser(const std::shared_ptr<CommonAPI::ClientId> clientId, uint32_t seatId) {
    // Call old style methods in default 
    unsetUser(seatId);
}
void ProfileManagerCtrlStubDefault::unsetUser(uint32_t seatId) {
    // No operation in default
}

void ProfileManagerCtrlStubDefault::timeOutAction(const std::shared_ptr<CommonAPI::ClientId> clientId, uint64_t timeOutSessionId, ProfileManagerCtrl::ETimeOutAction timeOutActionItem) {
    // Call old style methods in default 
    timeOutAction(timeOutSessionId, timeOutActionItem);
}
void ProfileManagerCtrlStubDefault::timeOutAction(uint64_t timeOutSessionId, ProfileManagerCtrl::ETimeOutAction timeOutActionItem) {
    // No operation in default
}




ProfileManagerCtrlStubDefault::RemoteEventHandler::RemoteEventHandler(ProfileManagerCtrlStubDefault* defaultStub):
        defaultStub_(defaultStub) {
}

} // namespace profile_mgmt_ctrl
} // namespace genivi
} // namespace org
