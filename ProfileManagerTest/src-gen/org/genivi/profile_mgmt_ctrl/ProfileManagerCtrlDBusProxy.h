/*
* This file was generated by the CommonAPI Generators. 
* Used org.genivi.commonapi.core 2.1.4.201311151436.
* Used org.franca.core 0.8.11.201401091023.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef ORG_GENIVI_PROFILE_MGMT_CTRL_Profile_Manager_Ctrl_DBUS_PROXY_H_
#define ORG_GENIVI_PROFILE_MGMT_CTRL_Profile_Manager_Ctrl_DBUS_PROXY_H_

#include <org/genivi/profile_mgmt_ctrl/ProfileManagerCtrlProxyBase.h>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/DBus/DBusFactory.h>
#include <CommonAPI/DBus/DBusProxy.h>
#include <CommonAPI/DBus/DBusEvent.h>
#include <CommonAPI/types.h>
#include <CommonAPI/DBus/DBusSelectiveEvent.h>

#undef COMMONAPI_INTERNAL_COMPILATION

#include <string>

namespace org {
namespace genivi {
namespace profile_mgmt_ctrl {

class ProfileManagerCtrlDBusProxy: virtual public ProfileManagerCtrlProxyBase, virtual public CommonAPI::DBus::DBusProxy {
 public:
    ProfileManagerCtrlDBusProxy(
                    const std::shared_ptr<CommonAPI::DBus::DBusFactory>& factory,
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection);

    virtual ~ProfileManagerCtrlDBusProxy() { }


    virtual OnTimeOutSelectiveEvent& getOnTimeOutSelectiveEvent();
    virtual OnStateChangeStartSelectiveEvent& getOnStateChangeStartSelectiveEvent();
    virtual OnStateChangeStopSelectiveEvent& getOnStateChangeStopSelectiveEvent();
    virtual OnClientRegisterSelectiveEvent& getOnClientRegisterSelectiveEvent();
    virtual OnClientUnregisterSelectiveEvent& getOnClientUnregisterSelectiveEvent();

    virtual void registerMe(const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister, CommonAPI::CallStatus& callStatus);
    virtual std::future<CommonAPI::CallStatus> registerMeAsync(const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister, RegisterMeAsyncCallback callback);
    virtual void setUser(const uint32_t& userId, const uint32_t& seatId, CommonAPI::CallStatus& callStatus);
    virtual std::future<CommonAPI::CallStatus> setUserAsync(const uint32_t& userId, const uint32_t& seatId, SetUserAsyncCallback callback);
    virtual void unsetUser(const uint32_t& seatId, CommonAPI::CallStatus& callStatus);
    virtual std::future<CommonAPI::CallStatus> unsetUserAsync(const uint32_t& seatId, UnsetUserAsyncCallback callback);
    virtual void timeOutAction(const uint64_t& timeOutSessionId, const ProfileManagerCtrl::ETimeOutAction& timeOutActionItem, CommonAPI::CallStatus& callStatus);
    virtual std::future<CommonAPI::CallStatus> timeOutActionAsync(const uint64_t& timeOutSessionId, const ProfileManagerCtrl::ETimeOutAction& timeOutActionItem, TimeOutActionAsyncCallback callback);
    

    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

 private:

    CommonAPI::DBus::DBusSelectiveEvent<OnTimeOutSelectiveEvent> onTimeOutSelective_;
    CommonAPI::DBus::DBusSelectiveEvent<OnStateChangeStartSelectiveEvent> onStateChangeStartSelective_;
    CommonAPI::DBus::DBusSelectiveEvent<OnStateChangeStopSelectiveEvent> onStateChangeStopSelective_;
    CommonAPI::DBus::DBusSelectiveEvent<OnClientRegisterSelectiveEvent> onClientRegisterSelective_;
    CommonAPI::DBus::DBusSelectiveEvent<OnClientUnregisterSelectiveEvent> onClientUnregisterSelective_;
    
};



} // namespace profile_mgmt_ctrl
} // namespace genivi
} // namespace org

#endif // ORG_GENIVI_PROFILE_MGMT_CTRL_Profile_Manager_Ctrl_DBUS_PROXY_H_
