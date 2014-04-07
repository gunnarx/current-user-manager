/*
* This file was generated by the CommonAPI Generators. 
* Used org.genivi.commonapi.core 2.1.4.201311151436.
* Used org.franca.core 0.8.11.201401091023.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include <org/genivi/profile_mgmt/ProfileManagerConsumerStubDefault.h>

namespace org {
namespace genivi {
namespace profile_mgmt {

ProfileManagerConsumerStubDefault::ProfileManagerConsumerStubDefault():
        remoteEventHandler_(this) {
}

ProfileManagerConsumerStubRemoteEvent* ProfileManagerConsumerStubDefault::initStubAdapter(const std::shared_ptr<ProfileManagerConsumerStubAdapter>& stubAdapter) {
    stubAdapter_ = stubAdapter;
    return &remoteEventHandler_;
}


void ProfileManagerConsumerStubDefault::detectedUser(const std::shared_ptr<CommonAPI::ClientId> clientId, int32_t seatID, int32_t userID, uint64_t sessionID) {
    // Call old style methods in default 
    detectedUser(seatID, userID, sessionID);
}
void ProfileManagerConsumerStubDefault::detectedUser(int32_t seatID, int32_t userID, uint64_t sessionID) {
    // No operation in default
}

void ProfileManagerConsumerStubDefault::synchronizedUser(const std::shared_ptr<CommonAPI::ClientId> clientId, int32_t seatID, int32_t userID, uint64_t sessionID) {
    // Call old style methods in default 
    synchronizedUser(seatID, userID, sessionID);
}
void ProfileManagerConsumerStubDefault::synchronizedUser(int32_t seatID, int32_t userID, uint64_t sessionID) {
    // No operation in default
}

void ProfileManagerConsumerStubDefault::stop(const std::shared_ptr<CommonAPI::ClientId> clientId, int32_t seatID, uint64_t sessionID) {
    // Call old style methods in default 
    stop(seatID, sessionID);
}
void ProfileManagerConsumerStubDefault::stop(int32_t seatID, uint64_t sessionID) {
    // No operation in default
}




ProfileManagerConsumerStubDefault::RemoteEventHandler::RemoteEventHandler(ProfileManagerConsumerStubDefault* defaultStub):
        defaultStub_(defaultStub) {
}

} // namespace profile_mgmt
} // namespace genivi
} // namespace org
