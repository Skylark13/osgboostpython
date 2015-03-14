# Introduction #

I'll try not to dwell on the trivial details, but instead mention some tricks and info that I've gathered from different documentation and web links. I'll try to mention the source where I first read each piece of advice, so if you want more reading click the links and read the rest of what they had to say.

# Wrapping enums #

Simple, but there's one little thing to watch for:

```
BOOST_PYTHON_MODULE(_osg)
{
  // ...
  {
    scope in_Object = class_<Object, /* ... */ >("Object", /* ... */)
      // ...
    ;

    enum_<Object::DataVariance>("DataVariance")
      .value("DYNAMIC",     Object::DYNAMIC)
      .value("STATIC",      Object::STATIC)
      .value("UNSPECIFIED", Object::UNSPECIFIED)
    ;
  }
  // ...
}
```

Note that the class where the enum needs to be is enclosed in a scope (curly brackets) and the result of the `class_` template is assigned to a `scope` object that lives for the duration of that scope. Then the `enum_` is created while that `scope` object lives.

This means that the enum will be accessed as osg.Object.DataVariance. If we didn't do that, the enum would be in module scope, so it would be osg.DataVariance. In addition to cluttering the osg module's namespace, it makes it hard to see which enums apply to which kinds of objects. So it's preferable to do it as above.

Eventually I might switch to read-only data members for the enum values instead of using `enum_`, because I don't like this:

```
n = osg.Node()  # Since Object is abstract
n.dataVariance(osg.Object.DataVariance.DYNAMIC)  # Note we need to add DataVariance
# I'd prefer:
# n.dataVariance(osg.Object.DYNAMIC)  # Like in C++, less cluttered
```

But for now, it's ok.

# Wrapping overridden methods #

When wrapping methods like this:

```
class A {};

class B
{
  public:
    A* getA();
    const A* getA() const;
};
```

The boost.python wrapper cannot be:

```
class_<B, ...>("B")
  .def("getA", &B::getA, some_return_value_policy())
;
```

because `&B::getA` is ambiguous. Which override should it choose?

The solution is to create an alias and use that:

```
A* (B::*B_getA1)() = &B::getA;

class_<B, ...>("B")
  .def("getA", B_getA1, some_return_value_policy())
;
```

Note that above I chose the version that returns a non-const pointer. These function pointers become tedious to write, so I'd like to find a better (more readable) way, possibly using a macro.

Reference: [Overloading](http://www.boost.org/doc/libs/1_36_0/libs/python/doc/tutorial/doc/html/python/functions.html#python.overloading)

# Wrapping methods with optional arguments #

Say you have:

```
class A
{
  public:
    void func(int a, bool b = true);
};
```

Simple:

```
// First parameter is a name, can be whatever you want.
// min arguments: 1, max arguments: 2
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(A_func_overloads, func, 1, 2)

// ...
class_<A, ...>("A")
  .def("func", &A::func, A_func_overloads())
;
```

You can combine that with an overloaded method by using `BOOST_PYTHON_FUNCTION_OVERLOADS` and an alias as described above.

Reference: [Default Arguments](http://www.boost.org/doc/libs/1_36_0/libs/python/doc/tutorial/doc/html/python/functions.html#python.default_arguments)

# Class overridable in python code #

This is a bit more complex. Two methods are discussed in the documentation:
  * [Using wrapper&lt;class&gt;](http://www.boost.org/doc/libs/1_40_0/libs/python/doc/tutorial/doc/html/python/exposing.html#python.class_virtual_functions)
  * [Using call\_method<...>(...)](http://wiki.python.org/moin/boost.python/OverridableVirtualFunctions)

In my case, I found `wrapper<class>` restrictive (the method and default version cannot be in the same class, so if you want to have a thin wrapper for the method you need to derive twice, among other things). So I went with call\_method. Here's an example:

```
struct NodeVisitor_wrapper : public NodeVisitor
{
    // 1
    // NodeVisitor constructors storing initial self parameter
    NodeVisitor_wrapper(PyObject *p, NodeVisitor::TraversalMode tm = NodeVisitor::TRAVERSE_NONE)
        : NodeVisitor(tm), self(p) {}

    NodeVisitor_wrapper(PyObject *p, NodeVisitor::VisitorType type, NodeVisitor::TraversalMode tm = NodeVisitor::TRAVERSE_NONE)
        : NodeVisitor(type, tm), self(p) {}

    // In case NodeVisitor is returned by-value from a wrapped function
    NodeVisitor_wrapper(PyObject *p, const NodeVisitor& x)
        : NodeVisitor(x), self(p) {}

    // TODO: We could probably simplify writing all the apply_* and 
    // default_apply_* with some preprocessor magic... Then again there are
    // a finite number of versions.

    // Override apply to call back into Python
    void apply(Node& node)
    {
        // 2
        try {
            call_method<void>(self, "apply_Node", boost::ref(node));  // 3
        }
        // Catch boost::python exception, means method was not overridden in subclass.
        catch (error_already_set) {
            NodeVisitor::apply(node);
        }
    }

    // Supplies the default implementation of apply
    void default_apply_Node(NodeVisitor& self_, Node& node)
    {
        self_.NodeVisitor::apply(node);
    }

    // Override apply to call back into Python
    void apply(Group& node)
    {
        try {
            call_method<void>(self, "apply_Group", boost::ref(node));
        }
        // Catch boost::python exception, means method was not overridden in subclass.
        catch (error_already_set) {
            NodeVisitor::apply(node);
        }
    }

    // Supplies the default implementation of apply
    void default_apply_Group(NodeVisitor& self_, Group& node)
    {
        self_.NodeVisitor::apply(node);
    }

 private:
    PyObject* self;
};

// 4
class_<NodeVisitor, NodeVisitor_wrapper, bases<Referenced>, 
       ref_ptr<NodeVisitor> >("NodeVisitor")
  .def(init<NodeVisitor::TraversalMode>())
  .def(init<NodeVisitor::VisitorType, NodeVisitor::TraversalMode>())
  // ...
  .def("apply_Node", &NodeVisitor_wrapper::default_apply_Node)
  .def("apply_Group", &NodeVisitor_wrapper::default_apply_Group)
  // ...
;
```

Notes:
  1. The wrapper class must define all the constructors you'd want to use from the base class, with an additional first parameter `PyObject *p`.
  1. The `try { /*...*/ } catch (error_already_set) { /*...*/ }` mechanism is used so that the methods can **optionally** be overridden. call\_method will throw an exception if the python-derived class does not override that method. You don't need that for pure virtual methods obviously, since it's mandatory that any concrete derived class override all pure virtual methods.
  1. Wrap reference arguments in `boost::ref()` and pointer arguments in `boost::python::ptr()`. This will prevent the wrapper from creating copies of the arguments, which would cause two problems:
    1. Since the copy constructor would be used to copy, the static type would be copied and this would cause slicing of the object's derived part.
    1. The copy would be used by value which would cause a compiler error for any class whose destructor is private/protected (which is often the case in OSG).
  1. Note that in the `class_` wrapper, the wrapper class `NodeVisitor_wrapper` is mentioned after the real type `NodeVisitor`, and then the function pointers used in the .def() methods are `NodeVisitor_wrapper::default_*`.

References: [Using wrapper&lt;class&gt;](http://www.boost.org/doc/libs/1_40_0/libs/python/doc/tutorial/doc/html/python/exposing.html#python.class_virtual_functions) -- [Using call\_method<...>(...)](http://wiki.python.org/moin/boost.python/OverridableVirtualFunctions)

# Wrapping an abstract class #

This is no secret, but just for reference. Need to specify both boost::noncopyable and no\_init:

```
class_<A, ..., boost::noncopyable>("A", no_init)
  // ...
;
```

Reference: [What is the relation between this '''no\_init''' and '''boost::noncopyable?'''](http://wiki.python.org/moin/boost.python/FAQ#Whatistherelationbetweenthis.27.27.27noinit.27.27.27and.27.27.27boost.3A.3Anoncopyable.3F.27.27.27)

# Make sure boost.python knows about ref\_ptr #

```
namespace boost { namespace python
{
  template <class T> struct pointee<ref_ptr<T> >
  {
     typedef T type;
  };
}}

// Then for all classes that derive from osg::Referenced, i.e. that can be 
// held by a ref_ptr:
class_<ClassName, bases<...>, ref_ptr<ClassName> >("ClassName")
  // ...
;
```

Note that I still have problems with conversion from ref\_ptr

&lt;T&gt;

 to T**and the opposite, so I'll update this when I've fixed it.**

References: [Pointee documentation](http://www.boost.org/doc/libs/1_36_0/libs/python/doc/v2/pointee.html#pointee-spec) -- [mailing list post](http://osdir.com/ml/python.c++/2002-07/msg00174.html)

# Build python list to return small lists #

Sometimes you'll want to return a small fixed-size list as an actual python list. For example, osg::Uniform has getters that will return int, uint and bool vectors of 2, 3 and 4 components as reference arguments. For example, for 4 ints:

```
bool get( int& i0, int& i1, int& i2, int& i3 ) const;
```

but I prefer to wrap these as functions returning python lists of 2, 3 or 4 ints/uints/bools. For example, for the above method:

```
boost::python::list Uniform_getInt41(Uniform* u)
{
  if (!u) 
    throw std::invalid_argument("Uniform is NULL"); 
  boost::python::list result; 
  int i[4];
  if (!u->get(i[0], i[1], i[2], i[3]))
    throw std::invalid_argument("Uniform does not contain a vector of 4 ints");
  result.append(i[0]); 
  result.append(i[1]); 
  result.append(i[2]); 
  result.append(i[3]); 
  return result;
}
```

Note that in the actual code I put all that on one line so the code file is less cluttered...

# General example code #

The Computational Crystallography Toolbox has some good boost.python wrappers and their code is inspiring, even if some parts are hard to understand without context.

[Source code viewer](http://cctbx.svn.sourceforge.net/viewvc/cctbx/trunk/scitbx/)

The [license](http://cctbx.svn.sourceforge.net/viewvc/cctbx/trunk/cctbx/LICENSE_2_0.txt?view=markup) seems very permissive, so I don't think I'm violating it by using some code and inspiration from it.

Parts that are inspired by cctbx are
  * The ArrayWrapper template in array.cpp (inspired by and in some cases lifted from [scitbx/array\_family/boost\_python/flex\_wrapper.h](http://cctbx.svn.sourceforge.net/viewvc/cctbx/trunk/scitbx/array_family/boost_python/flex_wrapper.h?view=markup))
  * Some to\_tuple converters in ContainerUtils.h (inspired by and in some cases lifted from [scitbx/boost\_python/container\_conversions.h](http://cctbx.svn.sourceforge.net/viewvc/cctbx/trunk/scitbx/boost_python/container_conversions.h?view=markup))
  * positive\_getitem\_index in ContainerUtils.h (lifted directly from [scitbx/misc/positive\_getitem\_index.h](http://cctbx.svn.sourceforge.net/viewvc/cctbx/trunk/scitbx/misc/positive_getitem_index.h?view=markup))

I'll soon add a LICENSE file in the repository (referring to the license that osgBoostPython is distributed under) in which I'll include methion and credit for the parts of the code that come from cctbx.

# Other things #

TODO: continue