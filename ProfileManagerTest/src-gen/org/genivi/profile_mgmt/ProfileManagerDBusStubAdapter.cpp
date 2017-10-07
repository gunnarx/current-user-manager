/*
* This file was generated by the CommonAPI Generators. 
* Used org.genivi.commonapi.core 2.1.4.201311151436.
* Used org.franca.core 0.8.11.201401091023.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include "ProfileManagerDBusStubAdapter.h"
#include <org/genivi/profile_mgmt/ProfileManager.h>

namespace org {
namespace genivi {
namespace profile_mgmt {

std::shared_ptr<CommonAPI::DBus::DBusStubAdapter> createProfileManagerDBusStubAdapter(
                   const std::shared_ptr<CommonAPI::DBus::DBusFactory>& factory,
                   const std::string& commonApiAddress,
                   const std::string& interfaceName,
                   const std::string& busName,
                   const std::string& objectPath,
                   const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection,
                   const std::shared_ptr<CommonAPI::StubBase>& stubBase) {
    return std::make_shared<ProfileManagerDBusStubAdapter>(factory, commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection, stubBase);
}

__attribute__((constructor)) void registerProfileManagerDBusStubAdapter(void) {
    CommonAPI::DBus::DBusFactory::registerAdapterFactoryMethod(ProfileManager::getInterfaceId(),
                                                               &createProfileManagerDBusStubAdapter);
}

ProfileManagerDBusStubAdapter::ProfileManagerDBusStubAdapter(
        const std::shared_ptr<CommonAPI::DBus::DBusFactory>& factory,
        const std::string& commonApiAddress,
        const std::string& dbusInterfaceName,
        const std::string& dbusBusName,
        const std::string& dbusObjectPath,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
        const std::shared_ptr<CommonAPI::StubBase>& stub):
        ProfileManagerDBusStubAdapterHelper(factory, commonApiAddress, dbusInterfaceName, dbusBusName, dbusObjectPath, 
            dbusConnection, std::dynamic_pointer_cast<ProfileManagerStub>(stub),
            false) {
    subscribersForDetectedUserSelective_ = std::make_shared<CommonAPI::ClientIdList>();
    subscribersForSynchronizedUserSelective_ = std::make_shared<CommonAPI::ClientIdList>();
    subscribersForStopSelective_ = std::make_shared<CommonAPI::ClientIdList>();
}

ProfileManagerDBusStubAdapter::~ProfileManagerDBusStubAdapter() {
    deactivateManagedInstances();
    deinit();
    stub_.reset();
}

void ProfileManagerDBusStubAdapter::deactivateManagedInstances() {
}

const char* ProfileManagerDBusStubAdapter::getMethodsDBusIntrospectionXmlData() const {
    static const char* introspectionData =
        "<signal name=\"detectedUser\">\n"
            "<arg name=\"seatID\" type=\"i\" />\n"
            "<arg name=\"userID\" type=\"i\" />\n"
            "<arg name=\"sessionID\" type=\"t\" />\n"
        "</signal>\n"
        "<signal name=\"synchronizedUser\">\n"
            "<arg name=\"seatID\" type=\"i\" />\n"
            "<arg name=\"userID\" type=\"i\" />\n"
            "<arg name=\"sessionID\" type=\"t\" />\n"
        "</signal>\n"
        "<signal name=\"stop\">\n"
            "<arg name=\"seatID\" type=\"i\" />\n"
            "<arg name=\"sessionID\" type=\"t\" />\n"
        "</signal>\n"
        "<method name=\"registerMe\">\n"
            "<arg name=\"appID\" type=\"s\" direction=\"in\" />\n"
            "<arg name=\"seatID\" type=\"i\" direction=\"in\" />\n"
        "</method>\n"
        "<method name=\"unregisterMe\">\n"
            "<arg name=\"consumerAddress\" type=\"s\" direction=\"in\" />\n"
            "<arg name=\"appID\" type=\"s\" direction=\"in\" />\n"
            "<arg name=\"seatID\" type=\"i\" direction=\"in\" />\n"
        "</method>\n"
        "<method name=\"confirm\">\n"
            "<arg name=\"sessionID\" type=\"t\" direction=\"in\" />\n"
        "</method>\n"
        "<method name=\"stopped\">\n"
            "<arg name=\"sessionID\" type=\"t\" direction=\"in\" />\n"
        "</method>\n"
        
    ;
    return introspectionData;
}



static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    ProfileManagerStub,
    std::tuple<std::string, int32_t>,
    std::tuple<>
    > registerMeStubDispatcher(&ProfileManagerStub::registerMe, "");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    ProfileManagerStub,
    std::tuple<std::string, std::string, int32_t>,
    std::tuple<>
    > unregisterMeStubDispatcher(&ProfileManagerStub::unregisterMe, "");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    ProfileManagerStub,
    std::tuple<uint64_t>,
    std::tuple<>
    > confirmStubDispatcher(&ProfileManagerStub::confirm, "");
static CommonAPI::DBus::DBusMethodWithReplyStubDispatcher<
    ProfileManagerStub,
    std::tuple<uint64_t>,
    std::tuple<>
    > stoppedStubDispatcher(&ProfileManagerStub::stopped, "");


static CommonAPI::DBus::DBusMethodWithReplyAdapterDispatcher<
    ProfileManagerStub,
    ProfileManagerStubAdapter,
    std::tuple<>,
    std::tuple<bool>
    > subscribeDetectedUserSelectiveStubDispatcher(&ProfileManagerStubAdapter::subscribeFordetectedUserSelective, "b");

static CommonAPI::DBus::DBusMethodWithReplyAdapterDispatcher<
    ProfileManagerStub,
    ProfileManagerStubAdapter,
    std::tuple<>,
    std::tuple<>
    > unsubscribeDetectedUserSelectiveStubDispatcher(&ProfileManagerStubAdapter::unsubscribeFromdetectedUserSelective, "");


void ProfileManagerDBusStubAdapter::fireDetectedUserSelective(const std::shared_ptr<CommonAPI::ClientId> clientId, const int32_t& seatID, const int32_t& userID, const uint64_t& sessionID) {
    std::shared_ptr<CommonAPI::DBus::DBusClientId> dbusClientId = std::dynamic_pointer_cast<CommonAPI::DBus::DBusClientId, CommonAPI::ClientId>(clientId);

    if(dbusClientId)
    {
        CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<int32_t, int32_t, uint64_t>>
            ::sendSignal(
                dbusClientId->getDBusId(),
                *this,
                "detectedUser",
                "iit",
                seatID, userID, sessionID
        );
    }
}

void ProfileManagerDBusStubAdapter::sendDetectedUserSelective(const int32_t& seatID, const int32_t& userID, const uint64_t& sessionID, const std::shared_ptr<CommonAPI::ClientIdList> receivers) {
    std::shared_ptr<CommonAPI::ClientIdList> actualReceiverList;
    actualReceiverList = receivers;

    if(receivers == NULL)
        actualReceiverList = subscribersForDetectedUserSelective_;

    for (auto clientIdIterator = actualReceiverList->cbegin();
               clientIdIterator != actualReceiverList->cend();
               clientIdIterator++) {
        if(receivers == NULL || subscribersForDetectedUserSelective_->find(*clientIdIterator) != subscribersForDetectedUserSelective_->end()) {
            fireDetectedUserSelective(*clientIdIterator, seatID, userID, sessionID);
        }
    }
}

void ProfileManagerDBusStubAdapter::subscribeFordetectedUserSelective(const std::shared_ptr<CommonAPI::ClientId> clientId, bool& success) {
    bool ok = stub_->onDetectedUserSelectiveSubscriptionRequested(clientId);
    if (ok) {
        subscribersForDetectedUserSelective_->insert(clientId);
        stub_->onDetectedUserSelectiveSubscriptionChanged(clientId, CommonAPI::SelectiveBroadcastSubscriptionEvent::SUBSCRIBED);
        success = true;
    } else {
        success = false;
    }
}


void ProfileManagerDBusStubAdapter::unsubscribeFromdetectedUserSelective(const std::shared_ptr<CommonAPI::ClientId> clientId) {
    subscribersForDetectedUserSelective_->erase(clientId);
    stub_->onDetectedUserSelectiveSubscriptionChanged(clientId, CommonAPI::SelectiveBroadcastSubscriptionEvent::UNSUBSCRIBED);
}

std::shared_ptr<CommonAPI::ClientIdList> const ProfileManagerDBusStubAdapter::getSubscribersForDetectedUserSelective() {
    return subscribersForDetectedUserSelective_;
}

static CommonAPI::DBus::DBusMethodWithReplyAdapterDispatcher<
    ProfileManagerStub,
    ProfileManagerStubAdapter,
    std::tuple<>,
    std::tuple<bool>
    > subscribeSynchronizedUserSelectiveStubDispatcher(&ProfileManagerStubAdapter::subscribeForsynchronizedUserSelective, "b");

static CommonAPI::DBus::DBusMethodWithReplyAdapterDispatcher<
    ProfileManagerStub,
    ProfileManagerStubAdapter,
    std::tuple<>,
    std::tuple<>
    > unsubscribeSynchronizedUserSelectiveStubDispatcher(&ProfileManagerStubAdapter::unsubscribeFromsynchronizedUserSelective, "");


void ProfileManagerDBusStubAdapter::fireSynchronizedUserSelective(const std::shared_ptr<CommonAPI::ClientId> clientId, const int32_t& seatID, const int32_t& userID, const uint64_t& sessionID) {
    std::shared_ptr<CommonAPI::DBus::DBusClientId> dbusClientId = std::dynamic_pointer_cast<CommonAPI::DBus::DBusClientId, CommonAPI::ClientId>(clientId);

    if(dbusClientId)
    {
        CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<int32_t, int32_t, uint64_t>>
            ::sendSignal(
                dbusClientId->getDBusId(),
                *this,
                "synchronizedUser",
                "iit",
                seatID, userID, sessionID
        );
    }
}

void ProfileManagerDBusStubAdapter::sendSynchronizedUserSelective(const int32_t& seatID, const int32_t& userID, const uint64_t& sessionID, const std::shared_ptr<CommonAPI::ClientIdList> receivers) {
    std::shared_ptr<CommonAPI::ClientIdList> actualReceiverList;
    actualReceiverList = receivers;

    if(receivers == NULL)
        actualReceiverList = subscribersForSynchronizedUserSelective_;

    for (auto clientIdIterator = actualReceiverList->cbegin();
               clientIdIterator != actualReceiverList->cend();
               clientIdIterator++) {
        if(receivers == NULL || subscribersForSynchronizedUserSelective_->find(*clientIdIterator) != subscribersForSynchronizedUserSelective_->end()) {
            fireSynchronizedUserSelective(*clientIdIterator, seatID, userID, sessionID);
        }
    }
}

void ProfileManagerDBusStubAdapter::subscribeForsynchronizedUserSelective(const std::shared_ptr<CommonAPI::ClientId> clientId, bool& success) {
    bool ok = stub_->onSynchronizedUserSelectiveSubscriptionRequested(clientId);
    if (ok) {
        subscribersForSynchronizedUserSelective_->insert(clientId);
        stub_->onSynchronizedUserSelectiveSubscriptionChanged(clientId, CommonAPI::SelectiveBroadcastSubscriptionEvent::SUBSCRIBED);
        success = true;
    } else {
        success = false;
    }
}


void ProfileManagerDBusStubAdapter::unsubscribeFromsynchronizedUserSelective(const std::shared_ptr<CommonAPI::ClientId> clientId) {
    subscribersForSynchronizedUserSelective_->erase(clientId);
    stub_->onSynchronizedUserSelectiveSubscriptionChanged(clientId, CommonAPI::SelectiveBroadcastSubscriptionEvent::UNSUBSCRIBED);
}

std::shared_ptr<CommonAPI::ClientIdList> const ProfileManagerDBusStubAdapter::getSubscribersForSynchronizedUserSelective() {
    return subscribersForSynchronizedUserSelective_;
}

static CommonAPI::DBus::DBusMethodWithReplyAdapterDispatcher<
    ProfileManagerStub,
    ProfileManagerStubAdapter,
    std::tuple<>,
    std::tuple<bool>
    > subscribeStopSelectiveStubDispatcher(&ProfileManagerStubAdapter::subscribeForstopSelective, "b");

static CommonAPI::DBus::DBusMethodWithReplyAdapterDispatcher<
    ProfileManagerStub,
    ProfileManagerStubAdapter,
    std::tuple<>,
    std::tuple<>
    > unsubscribeStopSelectiveStubDispatcher(&ProfileManagerStubAdapter::unsubscribeFromstopSelective, "");


void ProfileManagerDBusStubAdapter::fireStopSelective(const std::shared_ptr<CommonAPI::ClientId> clientId, const int32_t& seatID, const uint64_t& sessionID) {
    std::shared_ptr<CommonAPI::DBus::DBusClientId> dbusClientId = std::dynamic_pointer_cast<CommonAPI::DBus::DBusClientId, CommonAPI::ClientId>(clientId);

    if(dbusClientId)
    {
        CommonAPI::DBus::DBusStubSignalHelper<CommonAPI::DBus::DBusSerializableArguments<int32_t, uint64_t>>
            ::sendSignal(
                dbusClientId->getDBusId(),
                *this,
                "stop",
                "it",
                seatID, sessionID
        );
    }
}

void ProfileManagerDBusStubAdapter::sendStopSelective(const int32_t& seatID, const uint64_t& sessionID, const std::shared_ptr<CommonAPI::ClientIdList> receivers) {
    std::shared_ptr<CommonAPI::ClientIdList> actualReceiverList;
    actualReceiverList = receivers;

    if(receivers == NULL)
        actualReceiverList = subscribersForStopSelective_;

    for (auto clientIdIterator = actualReceiverList->cbegin();
               clientIdIterator != actualReceiverList->cend();
               clientIdIterator++) {
        if(receivers == NULL || subscribersForStopSelective_->find(*clientIdIterator) != subscribersForStopSelective_->end()) {
            fireStopSelective(*clientIdIterator, seatID, sessionID);
        }
    }
}

void ProfileManagerDBusStubAdapter::subscribeForstopSelective(const std::shared_ptr<CommonAPI::ClientId> clientId, bool& success) {
    bool ok = stub_->onStopSelectiveSubscriptionRequested(clientId);
    if (ok) {
        subscribersForStopSelective_->insert(clientId);
        stub_->onStopSelectiveSubscriptionChanged(clientId, CommonAPI::SelectiveBroadcastSubscriptionEvent::SUBSCRIBED);
        success = true;
    } else {
        success = false;
    }
}


void ProfileManagerDBusStubAdapter::unsubscribeFromstopSelective(const std::shared_ptr<CommonAPI::ClientId> clientId) {
    subscribersForStopSelective_->erase(clientId);
    stub_->onStopSelectiveSubscriptionChanged(clientId, CommonAPI::SelectiveBroadcastSubscriptionEvent::UNSUBSCRIBED);
}

std::shared_ptr<CommonAPI::ClientIdList> const ProfileManagerDBusStubAdapter::getSubscribersForStopSelective() {
    return subscribersForStopSelective_;
}


const ProfileManagerDBusStubAdapter::StubDispatcherTable& ProfileManagerDBusStubAdapter::getStubDispatcherTable() {
    static const ProfileManagerDBusStubAdapter::StubDispatcherTable stubDispatcherTable = {
            { { "registerMe", "si" }, &org::genivi::profile_mgmt::registerMeStubDispatcher },
            { { "unregisterMe", "ssi" }, &org::genivi::profile_mgmt::unregisterMeStubDispatcher },
            { { "confirm", "t" }, &org::genivi::profile_mgmt::confirmStubDispatcher },
            { { "stopped", "t" }, &org::genivi::profile_mgmt::stoppedStubDispatcher }
            ,
            { { "subscribeFordetectedUserSelective", "" }, &org::genivi::profile_mgmt::subscribeDetectedUserSelectiveStubDispatcher },
            { { "unsubscribeFromdetectedUserSelective", "" }, &org::genivi::profile_mgmt::unsubscribeDetectedUserSelectiveStubDispatcher },
            { { "subscribeForsynchronizedUserSelective", "" }, &org::genivi::profile_mgmt::subscribeSynchronizedUserSelectiveStubDispatcher },
            { { "unsubscribeFromsynchronizedUserSelective", "" }, &org::genivi::profile_mgmt::unsubscribeSynchronizedUserSelectiveStubDispatcher },
            { { "subscribeForstopSelective", "" }, &org::genivi::profile_mgmt::subscribeStopSelectiveStubDispatcher },
            { { "unsubscribeFromstopSelective", "" }, &org::genivi::profile_mgmt::unsubscribeStopSelectiveStubDispatcher }
            };
    return stubDispatcherTable;
}


} // namespace profile_mgmt
} // namespace genivi
} // namespace org