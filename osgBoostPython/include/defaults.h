#ifndef __OSGBOOSTPYTHON_DEFAULTS_H__
#define __OSGBOOSTPYTHON_DEFAULTS_H__

#include <boost/python.hpp>

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

    typedef return_value_policy<return_by_value>           default_value_policy;
    typedef return_value_policy<copy_non_const_reference>  default_reference_policy;
    typedef return_value_policy<copy_const_reference>      default_const_reference_policy;

    // This may not be the best option. But manage_new_object doesn't work 
    // (it uses auto_ptr so it needs a public destructor). Other options may 
    // be with_custodian_and_ward but I'll have to do more reading to know 
    // what it does exactly.
    typedef return_value_policy<reference_existing_object> default_pointer_policy;
}

#endif  // __OSGBOOSTPYTHON_DEFAULTS_H__
