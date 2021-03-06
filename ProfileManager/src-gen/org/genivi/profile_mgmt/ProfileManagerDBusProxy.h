/*
* This file was generated by the CommonAPI Generators. 
* Used org.genivi.commonapi.core 2.1.4.201311151436.
* Used org.franca.core 0.8.11.201401091023.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef ORG_GENIVI_PROFILE_MGMT_Profile_Manager_DBUS_PROXY_H_
#define ORG_GENIVI_PROFILE_MGMT_Profile_Manager_DBUS_PROXY_H_

#include <org/genivi/profile_mgmt/ProfileManagerProxyBase.h>

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
namespace profile_mgmt {

class ProfileManagerDBusProxy: virtual public ProfileManagerProxyBase, virtual public CommonAPI::DBus::DBusProxy {
 public:
    ProfileManagerDBusProxy(
                    const std::shared_ptr<CommonAPI::DBus::DBusFactory>& factory,
                    const std::string& commonApiAddress,
                    const std::string& interfaceName,
                    const std::string& busName,
                    const std::string& objectPath,
                    const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusProxyconnection);

    virtual ~ProfileManagerDBusProxy() { }


    virtual DetectedUserSelectiveEvent& getDetectedUserSelectiveEvent();
    virtual SynchronizedUserSelectiveEvent& getSynchronizedUserSelectiveEvent();
    virtual StopSelectiveEvent& getStopSelectiveEvent();

    virtual void registerMe(const std::string& appID, const int32_t& seatID, CommonAPI::CallStatus& callStatus);
    virtual std::future<CommonAPI::CallStatus> registerMeAsync(const std::string& appID, const int32_t& seatID, RegisterMeAsyncCallback callback);
    virtual void unregisterMe(const std::string& consumerAddress, const std::string& appID, const int32_t& seatID, CommonAPI::CallStatus& callStatus);
    virtual std::future<CommonAPI::CallStatus> unregisterMeAsync(const std::string& consumerAddress, const std::string& appID, const int32_t& seatID, UnregisterMeAsyncCallback callback);
    virtual void confirm(const uint64_t& sessionID, CommonAPI::CallStatus& callStatus);
    virtual std::future<CommonAPI::CallStatus> confirmAsync(const uint64_t& sessionID, ConfirmAsyncCallback callback);
    virtual void stopped(const uint64_t& sessionID, CommonAPI::CallStatus& callStatus);
    virtual std::future<CommonAPI::CallStatus> stoppedAsync(const uint64_t& sessionID, StoppedAsyncCallback callback);
    

    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

 private:

    CommonAPI::DBus::DBusSelectiveEvent<DetectedUserSelectiveEvent> detectedUserSelective_;
    CommonAPI::DBus::DBusSelectiveEvent<SynchronizedUserSelectiveEvent> synchronizedUserSelective_;
    CommonAPI::DBus::DBusSelectiveEvent<StopSelectiveEvent> stopSelective_;
    
};



} // namespace profile_mgmt
} // namespace genivi
} // namespace org

#endif // ORG_GENIVI_PROFILE_MGMT_Profile_Manager_DBUS_PROXY_H_
