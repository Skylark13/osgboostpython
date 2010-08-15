/*
* This source file is part of the osgBoostPython library
* 
* Copyright (C) 2009-2010 Jean-Sébastien Guay
* 
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU Lesser General Public License as published by the Free Software
* Foundation; either version 3 of the License, or (at your option) any later
* version.
* 
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
* http://www.gnu.org/copyleft/lesser.txt.
*/

#ifndef __OSGBOOSTPYTHON_DEFAULTS_H__
#define __OSGBOOSTPYTHON_DEFAULTS_H__

#include <boost/python.hpp>


#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #if defined( OSGBOOSTPYTHON_LIBRARY )
        #define OSGBOOSTPYTHON_EXPORT   __declspec(dllexport)
    #else
        #define OSGBOOSTPYTHON_EXPORT   __declspec(dllimport)
    #endif
#else
    #define OSGBOOSTPYTHON_EXPORT
#endif


namespace osgBoostPython
{
    // http://wiki.python.org/moin/boost.python/HowTo#head-20559aa92913c151739164fdaf5170530cfe50e9
    // http://wiki.python.org/moin/boost.python/CallPolicy
    // http://www.boost.org/doc/libs/1_35_0/libs/python/doc/v2/CallPolicies.html
    //
    // Possible return value policies:
    // with_custodian_and_ward<1,2>()
    // with_custodian_and_ward_postcall<1,0>()
    // return_internal_reference<>()                        -- ptr or reference   bad
    // return_value_policy<reference_existing_object>()     -- ptr or reference   bad
    // return_value_policy<copy_const_reference>()          -- reference         good
    // return_value_policy<copy_non_const_reference>()      -- reference         good
    // return_value_policy<manage_new_object>()             -- ptr               good
    // return_value_policy<return_by_value>()               -- value             good

    typedef boost::python::return_value_policy<boost::python::return_by_value>           default_value_policy;
    typedef boost::python::return_value_policy<boost::python::copy_non_const_reference>  default_reference_policy;
    typedef boost::python::return_value_policy<boost::python::copy_const_reference>      default_const_reference_policy;

    // This may not be the best option. But manage_new_object doesn't work 
    // (it uses auto_ptr so it needs a public destructor). Other options may 
    // be with_custodian_and_ward but I'll have to do more reading to know 
    // what it does exactly.
    typedef boost::python::return_value_policy<boost::python::reference_existing_object> default_pointer_policy;
}

#define FUNC_PTR0(retval, classname, funcname, ptr) retval (classname::*funcname)() = &ptr;
#define FUNC_PTR1(retval, classname, funcname, argtype1, ptr) retval (classname::*funcname)(argtype1) = &ptr;
#define FUNC_PTR2(retval, classname, funcname, argtype1, argtype2, ptr) retval (classname::*funcname)(argtype1, argtype2) = &ptr;
#define FUNC_PTR3(retval, classname, funcname, argtype1, argtype2, argtype3, ptr) retval (classname::*funcname)(argtype1, argtype2, argtype3) = &ptr;
#define FUNC_PTR4(retval, classname, funcname, argtype1, argtype2, argtype3, argtype4, ptr) retval (classname::*funcname)(argtype1, argtype2, argtype3, argtype4) = &ptr;

#define FUNC_PTR0_CONST(retval, classname, funcname, ptr) retval (classname::*funcname)() const = &ptr;
#define FUNC_PTR1_CONST(retval, classname, funcname, argtype1, ptr) retval (classname::*funcname)(argtype1) const = &ptr;
#define FUNC_PTR2_CONST(retval, classname, funcname, argtype1, argtype2, ptr) retval (classname::*funcname)(argtype1, argtype2) const = &ptr;
#define FUNC_PTR3_CONST(retval, classname, funcname, argtype1, argtype2, argtype3, ptr) retval (classname::*funcname)(argtype1, argtype2, argtype3) const = &ptr;
#define FUNC_PTR4_CONST(retval, classname, funcname, argtype1, argtype2, argtype3, argtype4, ptr) retval (classname::*funcname)(argtype1, argtype2, argtype3, argtype4) const = &ptr;

#endif  // __OSGBOOSTPYTHON_DEFAULTS_H__
