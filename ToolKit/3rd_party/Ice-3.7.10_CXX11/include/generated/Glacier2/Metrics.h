//
// Copyright (c) ZeroC, Inc. All rights reserved.
//
//
// Ice version 3.7.10
//
// <auto-generated>
//
// Generated from file `Metrics.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __Glacier2_Metrics_h__
#define __Glacier2_Metrics_h__

#include <IceUtil/PushDisableWarnings.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/ValueF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <Ice/Comparable.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/GCObject.h>
#include <Ice/Value.h>
#include <Ice/Incoming.h>
#include <Ice/FactoryTableInit.h>
#include <IceUtil/ScopedArray.h>
#include <Ice/Optional.h>
#include <Ice/ExceptionHelpers.h>
#include <Ice/Metrics.h>
#include <IceUtil/UndefSysMacros.h>
#include <Glacier2/Config.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 307
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 >= 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 10
#       error Ice patch level mismatch!
#   endif
#endif

#ifndef GLACIER2_API
#   if defined(ICE_STATIC_LIBS)
#       define GLACIER2_API /**/
#   elif defined(GLACIER2_API_EXPORTS)
#       define GLACIER2_API ICE_DECLSPEC_EXPORT
#   else
#       define GLACIER2_API ICE_DECLSPEC_IMPORT
#   endif
#endif

#ifdef ICE_CPP11_MAPPING // C++11 mapping

namespace IceMX
{

class SessionMetrics;

}

namespace IceMX
{

/**
 * Provides information on Glacier2 sessions.
 * \headerfile Glacier2/Glacier2.h
 */
class ICE_CLASS(GLACIER2_API) SessionMetrics : public ::Ice::ValueHelper<SessionMetrics, Metrics>
{
public:

    ICE_MEMBER(GLACIER2_API) virtual ~SessionMetrics();

    SessionMetrics() = default;

    SessionMetrics(const SessionMetrics&) = default;
    SessionMetrics(SessionMetrics&&) = default;
    SessionMetrics& operator=(const SessionMetrics&) = default;
    SessionMetrics& operator=(SessionMetrics&&) = default;

    /**
     * One-shot constructor to initialize all data members.
     * @param id The metrics identifier.
     * @param total The total number of objects observed by this metrics.
     * @param current The number of objects currently observed by this metrics.
     * @param totalLifetime The sum of the lifetime of each observed objects.
     * @param failures The number of failures observed.
     * @param forwardedClient Number of client requests forwared.
     * @param forwardedServer Number of server requests forwared.
     * @param routingTableSize The size of the routing table.
     * @param queuedClient Number of client requests queued.
     * @param queuedServer Number of server requests queued.
     * @param overriddenClient Number of client requests overridden.
     * @param overriddenServer Number of server requests overridden.
     */
    SessionMetrics(const ::std::string& id, long long int total, int current, long long int totalLifetime, int failures, int forwardedClient, int forwardedServer, int routingTableSize, int queuedClient, int queuedServer, int overriddenClient, int overriddenServer) :
        Ice::ValueHelper<SessionMetrics, Metrics>(id, total, current, totalLifetime, failures),
        forwardedClient(forwardedClient),
        forwardedServer(forwardedServer),
        routingTableSize(routingTableSize),
        queuedClient(queuedClient),
        queuedServer(queuedServer),
        overriddenClient(overriddenClient),
        overriddenServer(overriddenServer)
    {
    }

    /**
     * Obtains a tuple containing all of the value's data members.
     * @return The data members in a tuple.
     */
    std::tuple<const ::std::string&, const long long int&, const int&, const long long int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&> ice_tuple() const
    {
        return std::tie(id, total, current, totalLifetime, failures, forwardedClient, forwardedServer, routingTableSize, queuedClient, queuedServer, overriddenClient, overriddenServer);
    }

    /**
     * Obtains the Slice type ID of this value.
     * @return The fully-scoped type ID.
     */
    ICE_MEMBER(GLACIER2_API) static const ::std::string& ice_staticId();

    /**
     * Number of client requests forwared.
     */
    int forwardedClient = 0;
    /**
     * Number of server requests forwared.
     */
    int forwardedServer = 0;
    /**
     * The size of the routing table.
     */
    int routingTableSize = 0;
    /**
     * Number of client requests queued.
     */
    int queuedClient = 0;
    /**
     * Number of server requests queued.
     */
    int queuedServer = 0;
    /**
     * Number of client requests overridden.
     */
    int overriddenClient = 0;
    /**
     * Number of server requests overridden.
     */
    int overriddenServer = 0;
};

/// \cond INTERNAL
static SessionMetrics _iceS_SessionMetrics_init;
/// \endcond

}

namespace IceMX
{

}

/// \cond STREAM
namespace Ice
{

template<typename S>
struct StreamWriter<::IceMX::SessionMetrics, S>
{
    static void write(S* ostr, const ::IceMX::SessionMetrics& v)
    {
        ostr->writeAll(v.forwardedClient, v.forwardedServer, v.routingTableSize, v.queuedClient, v.queuedServer, v.overriddenClient, v.overriddenServer);
    }
};

template<typename S>
struct StreamReader<::IceMX::SessionMetrics, S>
{
    static void read(S* istr, ::IceMX::SessionMetrics& v)
    {
        istr->readAll(v.forwardedClient, v.forwardedServer, v.routingTableSize, v.queuedClient, v.queuedServer, v.overriddenClient, v.overriddenServer);
    }
};

}
/// \endcond

/// \cond INTERNAL
namespace IceMX
{

using SessionMetricsPtr = ::std::shared_ptr<SessionMetrics>;

}
/// \endcond

#else // C++98 mapping

namespace IceProxy
{

namespace IceMX
{

class SessionMetrics;
/// \cond INTERNAL
GLACIER2_API void _readProxy(::Ice::InputStream*, ::IceInternal::ProxyHandle< SessionMetrics>&);
GLACIER2_API ::IceProxy::Ice::Object* upCast(SessionMetrics*);
/// \endcond

}

}

namespace IceMX
{

class SessionMetrics;
/// \cond INTERNAL
GLACIER2_API ::Ice::Object* upCast(SessionMetrics*);
/// \endcond
typedef ::IceInternal::Handle< SessionMetrics> SessionMetricsPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::IceMX::SessionMetrics> SessionMetricsPrx;
typedef SessionMetricsPrx SessionMetricsPrxPtr;
/// \cond INTERNAL
GLACIER2_API void _icePatchObjectPtr(SessionMetricsPtr&, const ::Ice::ObjectPtr&);
/// \endcond

}

namespace IceMX
{

}

namespace IceProxy
{

namespace IceMX
{

class ICE_CLASS(GLACIER2_API) SessionMetrics : public virtual ::Ice::Proxy<SessionMetrics, ::IceProxy::IceMX::Metrics>
{
public:

    /**
     * Obtains the Slice type ID corresponding to this class.
     * @return A fully-scoped type ID.
     */
    ICE_MEMBER(GLACIER2_API) static const ::std::string& ice_staticId();

protected:
    /// \cond INTERNAL

    ICE_MEMBER(GLACIER2_API) virtual ::IceProxy::Ice::Object* _newInstance() const;
    /// \endcond
};

}

}

namespace IceMX
{

/**
 * Provides information on Glacier2 sessions.
 * \headerfile Glacier2/Glacier2.h
 */
class GLACIER2_API SessionMetrics : public Metrics
{
public:

    typedef SessionMetricsPrx ProxyType;
    typedef SessionMetricsPtr PointerType;

    virtual ~SessionMetrics();

    /** Default constructor that assigns default values to members as specified in the Slice definition. */
    SessionMetrics() :
        forwardedClient(0),
        forwardedServer(0),
        routingTableSize(0),
        queuedClient(0),
        queuedServer(0),
        overriddenClient(0),
        overriddenServer(0)
    {
    }

    /**
     * One-shot constructor to initialize all data members.
     * @param id The metrics identifier.
     * @param total The total number of objects observed by this metrics.
     * @param current The number of objects currently observed by this metrics.
     * @param totalLifetime The sum of the lifetime of each observed objects.
     * @param failures The number of failures observed.
     * @param forwardedClient Number of client requests forwared.
     * @param forwardedServer Number of server requests forwared.
     * @param routingTableSize The size of the routing table.
     * @param queuedClient Number of client requests queued.
     * @param queuedServer Number of server requests queued.
     * @param overriddenClient Number of client requests overridden.
     * @param overriddenServer Number of server requests overridden.
     */
    SessionMetrics(const ::std::string& id, ::Ice::Long total, ::Ice::Int current, ::Ice::Long totalLifetime, ::Ice::Int failures, ::Ice::Int forwardedClient, ::Ice::Int forwardedServer, ::Ice::Int routingTableSize, ::Ice::Int queuedClient, ::Ice::Int queuedServer, ::Ice::Int overriddenClient, ::Ice::Int overriddenServer) :
        ::IceMX::Metrics(id, total, current, totalLifetime, failures),
        forwardedClient(forwardedClient),
        forwardedServer(forwardedServer),
        routingTableSize(routingTableSize),
        queuedClient(queuedClient),
        queuedServer(queuedServer),
        overriddenClient(overriddenClient),
        overriddenServer(overriddenServer)
    {
    }

#ifdef ICE_CPP11_COMPILER
    SessionMetrics(const SessionMetrics&) = default;
    SessionMetrics& operator=(const SessionMetrics&) = default;
#endif

    /**
     * Polymorphically clones this object.
     * @return A shallow copy of this object.
     */
    virtual ::Ice::ObjectPtr ice_clone() const;

    /**
     * Determines whether this object supports an interface with the given Slice type ID.
     * @param id The fully-scoped Slice type ID.
     * @param current The Current object for the invocation.
     * @return True if this object supports the interface, false, otherwise.
     */
    virtual bool ice_isA(const ::std::string& id, const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains a list of the Slice type IDs representing the interfaces supported by this object.
     * @param current The Current object for the invocation.
     * @return A list of fully-scoped type IDs.
     */
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains a Slice type ID representing the most-derived interface supported by this object.
     * @param current The Current object for the invocation.
     * @return A fully-scoped type ID.
     */
    virtual const ::std::string& ice_id(const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains the Slice type ID corresponding to this class.
     * @return A fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

    /**
     * Obtains a value factory that instantiates this class.
     * @return The value factory.
     */
    static ::Ice::ValueFactoryPtr ice_factory();

protected:

    /// \cond STREAM
    virtual void _iceWriteImpl(::Ice::OutputStream*) const;
    virtual void _iceReadImpl(::Ice::InputStream*);
    /// \endcond

public:

    /**
     * Number of client requests forwared.
     */
    ::Ice::Int forwardedClient;
    /**
     * Number of server requests forwared.
     */
    ::Ice::Int forwardedServer;
    /**
     * The size of the routing table.
     */
    ::Ice::Int routingTableSize;
    /**
     * Number of client requests queued.
     */
    ::Ice::Int queuedClient;
    /**
     * Number of server requests queued.
     */
    ::Ice::Int queuedServer;
    /**
     * Number of client requests overridden.
     */
    ::Ice::Int overriddenClient;
    /**
     * Number of server requests overridden.
     */
    ::Ice::Int overriddenServer;
};
/// \cond INTERNAL
static ::Ice::ValueFactoryPtr _iceS_SessionMetrics_init = ::IceMX::SessionMetrics::ice_factory();
/// \endcond

/// \cond INTERNAL
inline bool operator==(const SessionMetrics& lhs, const SessionMetrics& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) == static_cast<const ::Ice::Object&>(rhs);
}

inline bool operator<(const SessionMetrics& lhs, const SessionMetrics& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) < static_cast<const ::Ice::Object&>(rhs);
}
/// \endcond

}

/// \cond STREAM
namespace Ice
{

template<typename S>
struct StreamWriter< ::IceMX::SessionMetrics, S>
{
    static void write(S* ostr, const ::IceMX::SessionMetrics& v)
    {
        ostr->write(v.forwardedClient);
        ostr->write(v.forwardedServer);
        ostr->write(v.routingTableSize);
        ostr->write(v.queuedClient);
        ostr->write(v.queuedServer);
        ostr->write(v.overriddenClient);
        ostr->write(v.overriddenServer);
    }
};

template<typename S>
struct StreamReader< ::IceMX::SessionMetrics, S>
{
    static void read(S* istr, ::IceMX::SessionMetrics& v)
    {
        istr->read(v.forwardedClient);
        istr->read(v.forwardedServer);
        istr->read(v.routingTableSize);
        istr->read(v.queuedClient);
        istr->read(v.queuedServer);
        istr->read(v.overriddenClient);
        istr->read(v.overriddenServer);
    }
};

}
/// \endcond

namespace IceMX
{

}

#endif

#include <IceUtil/PopDisableWarnings.h>
#endif
