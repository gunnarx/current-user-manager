/*
* This file was generated by the CommonAPI Generators. 
* Used org.genivi.commonapi.core 2.1.4.201311151436.
* Used org.franca.core 0.8.11.201401091023.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef ORG_GENIVI_PROFILE_MGMT_Profile_Manager_DBUS_STUB_ADAPTER_H_
#define ORG_GENIVI_PROFILE_MGMT_Profile_Manager_DBUS_STUB_ADAPTER_H_

#include <org/genivi/profile_mgmt/ProfileManagerStub.h>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/DBus/DBusStubAdapterHelper.h>
#include <CommonAPI/DBus/DBusStubAdapter.h>
#include <CommonAPI/DBus/DBusFactory.h>
#include <CommonAPI/DBus/DBusServicePublisher.h>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace org {
namespace genivi {
namespace profile_mgmt {

typedef CommonAPI::DBus::DBusStubAdapterHelper<ProfileManagerStub> ProfileManagerDBusStubAdapterHelper;

class ProfileManagerDBusStubAdapter: public ProfileManagerStubAdapter, public ProfileManagerDBusStubAdapterHelper {
 public:
    ProfileManagerDBusStubAdapter(
            const std::shared_ptr<CommonAPI::DBus::DBusFactory>& factory,
            const std::string& commonApiAddress,
            const std::string& dbusInterfaceName,
            const std::string& dbusBusName,
            const std::string& dbusObjectPath,
            const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection>& dbusConnection,
            const std::shared_ptr<CommonAPI::StubBase>& stub);

    ~ProfileManagerDBusStubAdapter();


    

    const StubDispatcherTable& getStubDispatcherTable();
    
    void deactivateManagedInstances();

 protected:
    virtual const char* getMethodsDBusIntrospectionXmlData() const;
    
  private:
};

} // namespace profile_mgmt
} // namespace genivi
} // namespace org

#endif // ORG_GENIVI_PROFILE_MGMT_Profile_Manager_DBUS_STUB_ADAPTER_H_
