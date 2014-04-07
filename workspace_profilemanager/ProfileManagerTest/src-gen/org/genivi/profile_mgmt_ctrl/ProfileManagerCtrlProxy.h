/*
* This file was generated by the CommonAPI Generators. 
* Used org.genivi.commonapi.core 2.1.4.201311151436.
* Used org.franca.core 0.8.11.201401091023.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef ORG_GENIVI_PROFILE_MGMT_CTRL_Profile_Manager_Ctrl_PROXY_H_
#define ORG_GENIVI_PROFILE_MGMT_CTRL_Profile_Manager_Ctrl_PROXY_H_

#include "ProfileManagerCtrlProxyBase.h"

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif


#undef COMMONAPI_INTERNAL_COMPILATION

namespace org {
namespace genivi {
namespace profile_mgmt_ctrl {

template <typename ... _AttributeExtensions>
class ProfileManagerCtrlProxy: virtual public ProfileManagerCtrl, virtual public ProfileManagerCtrlProxyBase, public _AttributeExtensions... {
 public:
    ProfileManagerCtrlProxy(std::shared_ptr<CommonAPI::Proxy> delegate);
    ~ProfileManagerCtrlProxy();



    /**
     * Calls registerMe with synchronous semantics.
     * 
    * All const parameters are input parameters to this method.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     */
    virtual void registerMe(const std::string& consumerAddress, const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister, CommonAPI::CallStatus& callStatus);
    /**
     * Calls registerMe with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> registerMeAsync(const std::string& consumerAddress, const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister, RegisterMeAsyncCallback callback);
    /**
     * Calls setUser with synchronous semantics.
     * 
    * All const parameters are input parameters to this method.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     */
    virtual void setUser(const uint32_t& userId, const uint32_t& seatId, CommonAPI::CallStatus& callStatus);
    /**
     * Calls setUser with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> setUserAsync(const uint32_t& userId, const uint32_t& seatId, SetUserAsyncCallback callback);
    /**
     * Calls unsetUser with synchronous semantics.
     * 
    * All const parameters are input parameters to this method.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     */
    virtual void unsetUser(const uint32_t& seatId, CommonAPI::CallStatus& callStatus);
    /**
     * Calls unsetUser with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> unsetUserAsync(const uint32_t& seatId, UnsetUserAsyncCallback callback);
    /**
     * Calls timeOutAction with synchronous semantics.
     * 
    * All const parameters are input parameters to this method.
     * The CallStatus will be filled when the method returns and indicate either
     * "SUCCESS" or which type of error has occurred. In case of an error, ONLY the CallStatus
     * will be set.
     */
    virtual void timeOutAction(const uint64_t& timeOutSessionId, const ProfileManagerCtrl::ETimeOutAction& timeOutActionItem, CommonAPI::CallStatus& callStatus);
    /**
     * Calls timeOutAction with asynchronous semantics.
     * 
     * The provided callback will be called when the reply to this call arrives or
     * an error occurs during the call. The CallStatus will indicate either "SUCCESS"
     * or which type of error has occurred. In case of any error, ONLY the CallStatus
     * will have a defined value.
     * The std::future returned by this method will be fulfilled at arrival of the reply.
     * It will provide the same value for CallStatus as will be handed to the callback.
     */
    virtual std::future<CommonAPI::CallStatus> timeOutActionAsync(const uint64_t& timeOutSessionId, const ProfileManagerCtrl::ETimeOutAction& timeOutActionItem, TimeOutActionAsyncCallback callback);
    

    /**
     * Returns the CommonAPI address of the remote partner this proxy communicates with.
     */
    virtual std::string getAddress() const;

    /**
     * Returns the domain of the remote partner this proxy communicates with.
     */
    virtual const std::string& getDomain() const;

    /** 
     * Returns the service ID of the remote partner this proxy communicates with.
     */
    virtual const std::string& getServiceId() const;

    /**
     * Returns the instance ID of the remote partner this proxy communicates with.
     */
    virtual const std::string& getInstanceId() const;

    /**
     * Returns true if the remote partner for this proxy is currently known to be available.
     */
    virtual bool isAvailable() const;

    /**
     * Returns true if the remote partner for this proxy is available.
     */
    virtual bool isAvailableBlocking() const;

    /**
     * Returns the wrapper class that is used to (de-)register for notifications about
     * the availability of the remote partner of this proxy.
     */
    virtual CommonAPI::ProxyStatusEvent& getProxyStatusEvent();

    /**
     * Returns the wrapper class that is used to access version information of the remote
     * partner of this proxy.
     */
    virtual CommonAPI::InterfaceVersionAttribute& getInterfaceVersionAttribute();

 private:
    std::shared_ptr<ProfileManagerCtrlProxyBase> delegate_;
};


//
// ProfileManagerCtrlProxy Implementation
//
template <typename ... _AttributeExtensions>
ProfileManagerCtrlProxy<_AttributeExtensions...>::ProfileManagerCtrlProxy(std::shared_ptr<CommonAPI::Proxy> delegate):
        delegate_(std::dynamic_pointer_cast<ProfileManagerCtrlProxyBase>(delegate)),
        _AttributeExtensions(*(std::dynamic_pointer_cast<ProfileManagerCtrlProxyBase>(delegate)))... {
}

template <typename ... _AttributeExtensions>
ProfileManagerCtrlProxy<_AttributeExtensions...>::~ProfileManagerCtrlProxy() {
}

template <typename ... _AttributeExtensions>
void ProfileManagerCtrlProxy<_AttributeExtensions...>::registerMe(const std::string& consumerAddress, const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister, CommonAPI::CallStatus& callStatus) {
    delegate_->registerMe(consumerAddress, registerOnTimeOut, registerOnStateChangeStart, registerOnStateChangeStop, registerOnClientRegister, registerOnClientUnregister, callStatus);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> ProfileManagerCtrlProxy<_AttributeExtensions...>::registerMeAsync(const std::string& consumerAddress, const bool& registerOnTimeOut, const bool& registerOnStateChangeStart, const bool& registerOnStateChangeStop, const bool& registerOnClientRegister, const bool& registerOnClientUnregister, RegisterMeAsyncCallback callback) {
    return delegate_->registerMeAsync(consumerAddress, registerOnTimeOut, registerOnStateChangeStart, registerOnStateChangeStop, registerOnClientRegister, registerOnClientUnregister, callback);
}
template <typename ... _AttributeExtensions>
void ProfileManagerCtrlProxy<_AttributeExtensions...>::setUser(const uint32_t& userId, const uint32_t& seatId, CommonAPI::CallStatus& callStatus) {
    delegate_->setUser(userId, seatId, callStatus);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> ProfileManagerCtrlProxy<_AttributeExtensions...>::setUserAsync(const uint32_t& userId, const uint32_t& seatId, SetUserAsyncCallback callback) {
    return delegate_->setUserAsync(userId, seatId, callback);
}
template <typename ... _AttributeExtensions>
void ProfileManagerCtrlProxy<_AttributeExtensions...>::unsetUser(const uint32_t& seatId, CommonAPI::CallStatus& callStatus) {
    delegate_->unsetUser(seatId, callStatus);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> ProfileManagerCtrlProxy<_AttributeExtensions...>::unsetUserAsync(const uint32_t& seatId, UnsetUserAsyncCallback callback) {
    return delegate_->unsetUserAsync(seatId, callback);
}
template <typename ... _AttributeExtensions>
void ProfileManagerCtrlProxy<_AttributeExtensions...>::timeOutAction(const uint64_t& timeOutSessionId, const ProfileManagerCtrl::ETimeOutAction& timeOutActionItem, CommonAPI::CallStatus& callStatus) {
    delegate_->timeOutAction(timeOutSessionId, timeOutActionItem, callStatus);
}

template <typename ... _AttributeExtensions>
std::future<CommonAPI::CallStatus> ProfileManagerCtrlProxy<_AttributeExtensions...>::timeOutActionAsync(const uint64_t& timeOutSessionId, const ProfileManagerCtrl::ETimeOutAction& timeOutActionItem, TimeOutActionAsyncCallback callback) {
    return delegate_->timeOutActionAsync(timeOutSessionId, timeOutActionItem, callback);
}

template <typename ... _AttributeExtensions>
std::string ProfileManagerCtrlProxy<_AttributeExtensions...>::getAddress() const {
    return delegate_->getAddress();
}

template <typename ... _AttributeExtensions>
const std::string& ProfileManagerCtrlProxy<_AttributeExtensions...>::getDomain() const {
    return delegate_->getDomain();
}

template <typename ... _AttributeExtensions>
const std::string& ProfileManagerCtrlProxy<_AttributeExtensions...>::getServiceId() const {
    return delegate_->getServiceId();
}

template <typename ... _AttributeExtensions>
const std::string& ProfileManagerCtrlProxy<_AttributeExtensions...>::getInstanceId() const {
    return delegate_->getInstanceId();
}

template <typename ... _AttributeExtensions>
bool ProfileManagerCtrlProxy<_AttributeExtensions...>::isAvailable() const {
    return delegate_->isAvailable();
}

template <typename ... _AttributeExtensions>
bool ProfileManagerCtrlProxy<_AttributeExtensions...>::isAvailableBlocking() const {
    return delegate_->isAvailableBlocking();
}

template <typename ... _AttributeExtensions>
CommonAPI::ProxyStatusEvent& ProfileManagerCtrlProxy<_AttributeExtensions...>::getProxyStatusEvent() {
    return delegate_->getProxyStatusEvent();
}

template <typename ... _AttributeExtensions>
CommonAPI::InterfaceVersionAttribute& ProfileManagerCtrlProxy<_AttributeExtensions...>::getInterfaceVersionAttribute() {
    return delegate_->getInterfaceVersionAttribute();
}

        

} // namespace profile_mgmt_ctrl
} // namespace genivi
} // namespace org


#endif // ORG_GENIVI_PROFILE_MGMT_CTRL_Profile_Manager_Ctrl_PROXY_H_
