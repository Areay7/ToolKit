//
// Copyright (c) ZeroC, Inc. All rights reserved.
//
//
// Ice version 3.7.10
//
// <auto-generated>
//
// Generated from file `BuiltinSequences.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __Ice_BuiltinSequences_h__
#define __Ice_BuiltinSequences_h__

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

/**
 * A sequence of bools.
 */
using BoolSeq = ::std::vector<bool>;

/**
 * A sequence of bytes.
 */
using ByteSeq = ::std::vector<Byte>;

/**
 * A sequence of shorts.
 */
using ShortSeq = ::std::vector<short>;

/**
 * A sequence of ints.
 */
using IntSeq = ::std::vector<int>;

/**
 * A sequence of longs.
 */
using LongSeq = ::std::vector<long long int>;

/**
 * A sequence of floats.
 */
using FloatSeq = ::std::vector<float>;

/**
 * A sequence of doubles.
 */
using DoubleSeq = ::std::vector<double>;

/**
 * A sequence of strings.
 */
using StringSeq = ::std::vector<::std::string>;

/**
 * A sequence of objects.
 */
using ObjectSeq = ::std::vector<::std::shared_ptr<Value>>;

/**
 * A sequence of object proxies.
 */
using ObjectProxySeq = ::std::vector<::std::shared_ptr<ObjectPrx>>;

}

#else // C++98 mapping

namespace Ice
{

/**
 * A sequence of bools.
 */
typedef ::std::vector<bool> BoolSeq;

/**
 * A sequence of bytes.
 */
typedef ::std::vector<Byte> ByteSeq;

/**
 * A sequence of shorts.
 */
typedef ::std::vector<Short> ShortSeq;

/**
 * A sequence of ints.
 */
typedef ::std::vector<Int> IntSeq;

/**
 * A sequence of longs.
 */
typedef ::std::vector<Long> LongSeq;

/**
 * A sequence of floats.
 */
typedef ::std::vector<Float> FloatSeq;

/**
 * A sequence of doubles.
 */
typedef ::std::vector<Double> DoubleSeq;

/**
 * A sequence of strings.
 */
typedef ::std::vector< ::std::string> StringSeq;

/**
 * A sequence of objects.
 */
typedef ::std::vector<ObjectPtr> ObjectSeq;

/**
 * A sequence of object proxies.
 */
typedef ::std::vector<ObjectPrx> ObjectProxySeq;

}

#endif

#include <IceUtil/PopDisableWarnings.h>
#endif
