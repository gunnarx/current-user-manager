/*
* This file was generated by the CommonAPI Generators. 
* Used org.genivi.commonapi.core 2.1.2.201309301424.
* Used org.franca.core 0.8.10.201309262002.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#include "ProfileManagerCtrlDBusProxy.h"

namespace org {
namespace genivi {
namespace profile_mgmt_ctrl {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createProfileManagerCtrlDBusProxy(
                    const std::shared_ptr<CommonAPI::DBus::DBusFactory>& factory,
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyConnection) {
    return std::make_shared<ProfileManagerCtrlDBusProxy>(factory, commonApiAddress, interfaceName, busName, objectPath, dbusProxyConnection);
}

__attribute__((constructor)) void registerProfileManagerCtrlDBusProxy(void) {
    CommonAPI::DBus::DBusFactory::registerProxyFactoryMethod(ProfileManagerCtrl::getInterfaceId(),
       &createProfileManagerCtrlDBusProxy);
}

ProfileManagerCtrlDBusProxy::ProfileManagerCtrlDBusProxy(
                    const std::shared_ptr<CommonAPI::DBus::DBusFactory>& factory,
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection):
        CommonAPI::DBus::DBusProxy(factory, commonApiAddress, interfaceName, busName, objectPath, dbusProxyconnection)
    {
    }



void ProfileManagerCtrlDBusProxy::registerMe(const std::string& consumerAddress, const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister, CommonAPI::CallStatus& callStatus) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<std::string, bool, bool, bool, bool, bool>,
                                     CommonAPI::DBus::DBusSerializableArguments<> >::callMethodWithReply(
        *this,
        "registerMe",
        "sbbbbb",
        consumerAddress, registerOnTimeOut, registerOnStateChangeStart, registerOnStateChangeStop, registerOnClientRegister, registerOnClientUnregister, 
        callStatus
        );
}
std::future<CommonAPI::CallStatus> ProfileManagerCtrlDBusProxy::registerMeAsync(const std::string& consumerAddress, const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister, RegisterMeAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<std::string, bool, bool, bool, bool, bool>,
                                     CommonAPI::DBus::DBusSerializableArguments<> >::callMethodAsync(
        *this,
        "registerMe",
        "sbbbbb",
        consumerAddress, registerOnTimeOut, registerOnStateChangeStart, registerOnStateChangeStop, registerOnClientRegister, registerOnClientUnregister, 
        std::move(callback));
}
void ProfileManagerCtrlDBusProxy::setUser(const uint32_t& userId, const uint32_t& seatId, CommonAPI::CallStatus& callStatus) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<uint32_t, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<> >::callMethodWithReply(
        *this,
        "setUser",
        "uu",
        userId, seatId, 
        callStatus
        );
}
std::future<CommonAPI::CallStatus> ProfileManagerCtrlDBusProxy::setUserAsync(const uint32_t& userId, const uint32_t& seatId, SetUserAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<uint32_t, uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<> >::callMethodAsync(
        *this,
        "setUser",
        "uu",
        userId, seatId, 
        std::move(callback));
}
void ProfileManagerCtrlDBusProxy::unsetUser(const uint32_t& seatId, CommonAPI::CallStatus& callStatus) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<> >::callMethodWithReply(
        *this,
        "unsetUser",
        "u",
        seatId, 
        callStatus
        );
}
std::future<CommonAPI::CallStatus> ProfileManagerCtrlDBusProxy::unsetUserAsync(const uint32_t& seatId, UnsetUserAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<uint32_t>,
                                     CommonAPI::DBus::DBusSerializableArguments<> >::callMethodAsync(
        *this,
        "unsetUser",
        "u",
        seatId, 
        std::move(callback));
}
void ProfileManagerCtrlDBusProxy::timeOutAction(const uint64_t& timeOutSessionId, const ProfileManagerCtrl::ETimeOutAction& timeOutActionItem, CommonAPI::CallStatus& callStatus) {
    CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<uint64_t, ProfileManagerCtrl::ETimeOutAction>,
                                     CommonAPI::DBus::DBusSerializableArguments<> >::callMethodWithReply(
        *this,
        "timeOutAction",
        "ti",
        timeOutSessionId, timeOutActionItem, 
        callStatus
        );
}
std::future<CommonAPI::CallStatus> ProfileManagerCtrlDBusProxy::timeOutActionAsync(const uint64_t& timeOutSessionId, const ProfileManagerCtrl::ETimeOutAction& timeOutActionItem, TimeOutActionAsyncCallback callback) {
    return CommonAPI::DBus::DBusProxyHelper<CommonAPI::DBus::DBusSerializableArguments<uint64_t, ProfileManagerCtrl::ETimeOutAction>,
                                     CommonAPI::DBus::DBusSerializableArguments<> >::callMethodAsync(
        *this,
        "timeOutAction",
        "ti",
        timeOutSessionId, timeOutActionItem, 
        std::move(callback));
}



void ProfileManagerCtrlDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
    ownVersionMajor = 1;
    ownVersionMinor = 0;
}

} // namespace profile_mgmt_ctrl
} // namespace genivi
} // namespace org