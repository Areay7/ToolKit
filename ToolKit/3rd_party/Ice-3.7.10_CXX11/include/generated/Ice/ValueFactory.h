//
// Copyright (c) ZeroC, Inc. All rights reserved.
//
//
// Ice version 3.7.10
//
// <auto-generated>
//
// Generated from file `ValueFactory.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __Ice_ValueFactory_h__
#define __Ice_ValueFactory_h__

#include <IceUtil/PushDisableWarnings.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/ValueF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <Ice/Comparable.h>
#include <IceUtil/ScopedArray.h>
#include <Ice/Optional.h>
#include <IceUtil/UndefSysMacros.h>

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

#ifndef ICE_API
#   if defined(ICE_STATIC_LIBS)
#       define ICE_API /**/
#   elif defined(ICE_API_EXPORTS)
#       define ICE_API ICE_DECLSPEC_EXPORT
#   else
#       define ICE_API ICE_DECLSPEC_IMPORT
#   endif
#endif

#ifdef ICE_CPP11_MAPPING // C++11 mapping

namespace Ice
{

class ValueFactoryManager;

}

namespace Ice
{

/**
 * Create a new value for a given value type. The type is the
 * absolute Slice type id, i.e., the id relative to the
 * unnamed top-level Slice module. For example, the absolute
 * Slice type id for an interface <code>Bar</code> in the module
 * <code>Foo</code> is <code>"::Foo::Bar"</code>.
 *
 * Note that the leading "<code>::</code>" is required.
 * @param type The value type.
 * @return The value created for the given type, or nil if the
 * factory is unable to create the value.
 */
using ValueFactory = ::std::function<::std::shared_ptr<Value>(const ::std::string& type)>;

/**
 * A value factory manager maintains a collection of value factories.
 * An application can supply a custom implementation during communicator
 * initialization, otherwise Ice provides a default implementation.
 * @see ValueFactory
 * \headerfile Ice/Ice.h
 */
class ICE_CLASS(ICE_API) ValueFactoryManager
{
public:

    ICE_MEMBER(ICE_API) virtual ~ValueFactoryManager();

    /**
     * Add a value factory. Attempting to add a factory with an id for
     * which a factory is already registered throws AlreadyRegisteredException.
     *
     * When unmarshaling an Ice value, the Ice run time reads the
     * most-derived type id off the wire and attempts to create an
     * instance of the type using a factory. If no instance is created,
     * either because no factory was found, or because all factories
     * returned nil, the behavior of the Ice run time depends on the
     * format with which the value was marshaled:
     *
     * If the value uses the "sliced" format, Ice ascends the class
     * hierarchy until it finds a type that is recognized by a factory,
     * or it reaches the least-derived type. If no factory is found that
     * can create an instance, the run time throws NoValueFactoryException.
     *
     * If the value uses the "compact" format, Ice immediately raises
     * NoValueFactoryException.
     *
     * The following order is used to locate a factory for a type:
     *
     * <ol>
     *
     * <li>The Ice run-time looks for a factory registered
     * specifically for the type.</li>
     *
     * <li>If no instance has been created, the Ice run-time looks
     * for the default factory, which is registered with an empty type id.
     * </li>
     *
     * <li>If no instance has been created by any of the preceding
     * steps, the Ice run-time looks for a factory that may have been
     * statically generated by the language mapping for non-abstract classes.
     * </li>
     *
     * </ol>
     * @param factory The factory to add.
     * @param id The type id for which the factory can create instances, or
     * an empty string for the default factory.
     */
    virtual void add(ValueFactory factory, const ::std::string& id) = 0;

    /**
     * Find an value factory registered with this communicator.
     * @param id The type id for which the factory can create instances,
     * or an empty string for the default factory.
     * @return The value factory, or null if no value factory was
     * found for the given id.
     */
    virtual ::Ice::ValueFactory find(const ::std::string& id) const noexcept = 0;
};

}

/// \cond STREAM
namespace Ice
{

}
/// \endcond

/// \cond INTERNAL
namespace Ice
{

using ValueFactoryManagerPtr = ::std::shared_ptr<ValueFactoryManager>;

}
/// \endcond

#else // C++98 mapping

namespace Ice
{

class ValueFactory;
/// \cond INTERNAL
ICE_API LocalObject* upCast(ValueFactory*);
/// \endcond
typedef ::IceInternal::Handle< ValueFactory> ValueFactoryPtr;

class ValueFactoryManager;
/// \cond INTERNAL
ICE_API LocalObject* upCast(ValueFactoryManager*);
/// \endcond
typedef ::IceInternal::Handle< ValueFactoryManager> ValueFactoryManagerPtr;

}

namespace Ice
{

/**
 * A factory for values. Value factories are used in several
 * places, such as when Ice receives a class instance and
 * when Freeze restores a persistent value. Value factories
 * must be implemented by the application writer and registered
 * with the communicator.
 * \headerfile Ice/Ice.h
 */
class ICE_API ValueFactory : public virtual LocalObject
{
public:

    typedef ValueFactoryPtr PointerType;

    virtual ~ValueFactory();

#ifdef ICE_CPP11_COMPILER
    ValueFactory() = default;
    ValueFactory(const ValueFactory&) = default;
    ValueFactory& operator=(const ValueFactory&) = default;
#endif

    /**
     * Create a new value for a given value type. The type is the
     * absolute Slice type id, i.e., the id relative to the
     * unnamed top-level Slice module. For example, the absolute
     * Slice type id for an interface <code>Bar</code> in the module
     * <code>Foo</code> is <code>"::Foo::Bar"</code>.
     *
     * Note that the leading "<code>::</code>" is required.
     * @param type The value type.
     * @return The value created for the given type, or nil if the
     * factory is unable to create the value.
     */
    virtual ValuePtr create(const ::std::string& type) = 0;
};

/// \cond INTERNAL
inline bool operator==(const ValueFactory& lhs, const ValueFactory& rhs)
{
    return static_cast<const LocalObject&>(lhs) == static_cast<const LocalObject&>(rhs);
}

inline bool operator<(const ValueFactory& lhs, const ValueFactory& rhs)
{
    return static_cast<const LocalObject&>(lhs) < static_cast<const LocalObject&>(rhs);
}
/// \endcond

/**
 * A value factory manager maintains a collection of value factories.
 * An application can supply a custom implementation during communicator
 * initialization, otherwise Ice provides a default implementation.
 * @see ValueFactory
 * \headerfile Ice/Ice.h
 */
class ICE_API ValueFactoryManager : public virtual LocalObject
{
public:

    typedef ValueFactoryManagerPtr PointerType;

    virtual ~ValueFactoryManager();

#ifdef ICE_CPP11_COMPILER
    ValueFactoryManager() = default;
    ValueFactoryManager(const ValueFactoryManager&) = default;
    ValueFactoryManager& operator=(const ValueFactoryManager&) = default;
#endif

    /**
     * Add a value factory. Attempting to add a factory with an id for
     * which a factory is already registered throws AlreadyRegisteredException.
     *
     * When unmarshaling an Ice value, the Ice run time reads the
     * most-derived type id off the wire and attempts to create an
     * instance of the type using a factory. If no instance is created,
     * either because no factory was found, or because all factories
     * returned nil, the behavior of the Ice run time depends on the
     * format with which the value was marshaled:
     *
     * If the value uses the "sliced" format, Ice ascends the class
     * hierarchy until it finds a type that is recognized by a factory,
     * or it reaches the least-derived type. If no factory is found that
     * can create an instance, the run time throws NoValueFactoryException.
     *
     * If the value uses the "compact" format, Ice immediately raises
     * NoValueFactoryException.
     *
     * The following order is used to locate a factory for a type:
     *
     * <ol>
     *
     * <li>The Ice run-time looks for a factory registered
     * specifically for the type.</li>
     *
     * <li>If no instance has been created, the Ice run-time looks
     * for the default factory, which is registered with an empty type id.
     * </li>
     *
     * <li>If no instance has been created by any of the preceding
     * steps, the Ice run-time looks for a factory that may have been
     * statically generated by the language mapping for non-abstract classes.
     * </li>
     *
     * </ol>
     * @param factory The factory to add.
     * @param id The type id for which the factory can create instances, or
     * an empty string for the default factory.
     */
    virtual void add(const ValueFactoryPtr& factory, const ::std::string& id) = 0;

    /**
     * Find an value factory registered with this communicator.
     * @param id The type id for which the factory can create instances,
     * or an empty string for the default factory.
     * @return The value factory, or null if no value factory was
     * found for the given id.
     */
    virtual ValueFactoryPtr find(const ::std::string& id) const ICE_NOEXCEPT = 0;
};

/// \cond INTERNAL
inline bool operator==(const ValueFactoryManager& lhs, const ValueFactoryManager& rhs)
{
    return static_cast<const LocalObject&>(lhs) == static_cast<const LocalObject&>(rhs);
}

inline bool operator<(const ValueFactoryManager& lhs, const ValueFactoryManager& rhs)
{
    return static_cast<const LocalObject&>(lhs) < static_cast<const LocalObject&>(rhs);
}
/// \endcond

}

/// \cond STREAM
namespace Ice
{

}
/// \endcond

#endif

#include <IceUtil/PopDisableWarnings.h>
#endif
