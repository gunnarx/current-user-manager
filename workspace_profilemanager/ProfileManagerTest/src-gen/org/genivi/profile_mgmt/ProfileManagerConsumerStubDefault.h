/*
* This file was generated by the CommonAPI Generators. 
* Used org.genivi.commonapi.core 2.1.4.201311151436.
* Used org.franca.core 0.8.11.201401091023.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef ORG_GENIVI_PROFILE_MGMT_Profile_Manager_Consumer_STUB_DEFAULT_H_
#define ORG_GENIVI_PROFILE_MGMT_Profile_Manager_Consumer_STUB_DEFAULT_H_

#include <org/genivi/profile_mgmt/ProfileManagerConsumerStub.h>
#include <sstream>

namespace org {
namespace genivi {
namespace profile_mgmt {

/**
 * Provides a default implementation for ProfileManagerConsumerStubRemoteEvent and
 * ProfileManagerConsumerStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 *
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class ProfileManagerConsumerStubDefault : public ProfileManagerConsumerStub {
 public:
    ProfileManagerConsumerStubDefault();

    ProfileManagerConsumerStubRemoteEvent* initStubAdapter(const std::shared_ptr<ProfileManagerConsumerStubAdapter>& stubAdapter);


    virtual void detectedUser(const std::shared_ptr<CommonAPI::ClientId> clientId, int32_t seatID, int32_t userID, uint64_t sessionID);
    virtual void detectedUser(int32_t seatID, int32_t userID, uint64_t sessionID);

    virtual void synchronizedUser(const std::shared_ptr<CommonAPI::ClientId> clientId, int32_t seatID, int32_t userID, uint64_t sessionID);
    virtual void synchronizedUser(int32_t seatID, int32_t userID, uint64_t sessionID);

    virtual void stop(const std::shared_ptr<CommonAPI::ClientId> clientId, int32_t seatID, uint64_t sessionID);
    virtual void stop(int32_t seatID, uint64_t sessionID);


    

 protected:
    std::shared_ptr<ProfileManagerConsumerStubAdapter> stubAdapter_;
 private:
    class RemoteEventHandler: public ProfileManagerConsumerStubRemoteEvent {
     public:
        RemoteEventHandler(ProfileManagerConsumerStubDefault* defaultStub);


     private:
        ProfileManagerConsumerStubDefault* defaultStub_;
    };

    RemoteEventHandler remoteEventHandler_;

};

} // namespace profile_mgmt
} // namespace genivi
} // namespace org

#endif // ORG_GENIVI_PROFILE_MGMT_Profile_Manager_Consumer_STUB_DEFAULT_H_
