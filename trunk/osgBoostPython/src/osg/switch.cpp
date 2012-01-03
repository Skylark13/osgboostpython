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

// Good sources of information:
// http://wiki.python.org/moin/boost.python
// http://www.boost.org/doc/libs/1_36_0/libs/python/doc/tutorial/doc/html/index.html
// http://www.boost.org/doc/libs/1_36_0/libs/python/doc/v2/faq.html

// General Python info
// http://docs.python.org/tut/
#include <boost/python.hpp>
using namespace boost::python;

// Sure, "Computational Crystallography Toolbox" doesn't seem like it applies 
// to us, but there's a lot of good example code for wrapping containers, etc.
// http://cctbx.sourceforge.net/
// http://cctbx.svn.sourceforge.net/viewvc/cctbx/trunk/scitbx/

#include <osg/ref_ptr>
#include <osg/Referenced>
#include <osg/Object>
#include <osg/Group>
#include <osg/Switch>
using namespace osg;

#include "defaults.h"

struct Switch_wrapper : public Switch {
  
  Switch_wrapper( PyObject* p ) : self( p ) {}
  Switch_wrapper( PyObject* p, const Switch& s ) : self( p ), Switch( s ) {}

//  /**
//   * traverse
//   */ 
//
//  /**
//   * There's currently no ideal way to override this method 
//   * just yet.  As written below NodeVisitors are copy-constructed
//   * and sliced to base.  Wrapping them in a reference_wrapper 
//   * also doesn't work, since there are 'private' NodeVisitors that are
//   * not part of the API ( and not wrappable ) that will be passed to
//   * this method and causes Python to throw with the following error :
//   *
//   *  Traceback (most recent call last):
//   *    File "examples/osg-book/animation_switch.py", line 53, in <module>
//   *      viewer.setSceneData( root )
//   *    File "examples/osg-book/animation_switch.py", line 19, in traverse
//   *      print "nv.className = ", nv.className
//   *  Boost.Python.ArgumentError: Python argument types in
//   *      None.None(NodeVisitor)
//   *  did not match C++ signature:
//   *      None(NodeVisitor_wrapper {lvalue})
//   *
//   * Hopefully there's a good solution out there, but it's escaping me
//   * at the moment.
//   */
//  void  traverse( NodeVisitor& nv ) {
//    if (override f = this->get_override("traverse")){
//      //f( boost::ref(nv) );
//      f( nv );
//    }
//    else Switch::traverse( nv );
//  }									
//  void default_traverse( NodeVisitor& nv ) { this->Switch::traverse( nv ); }

  /**
   * addChild 
   */ 
  bool  addChild( Node* node ) {
    try{
      return call_method<bool>(self,"addChild", ptr(node) );
    }catch (error_already_set) {
      return Switch::addChild( node );
    }
  }									
  bool default_addChild( Node* node ) { return this->Switch::addChild( node ); }

  bool addChild( Node* node, bool value ) {
    try{
      return call_method<bool>(self, "addChild", ptr(node), value );
    } catch (error_already_set) {
      return Switch::addChild( node, value );
    }
  }									

  bool default_addChild( Node* node, bool value ) { 
    return this->Switch::addChild( node, value ); 
  }

  /**
   * insertChild
   */ 
  bool  insertChild( unsigned int index, Node* node ) {
    try{
      return call_method<bool>(self, "insertChild", index, ptr(node) );
    } catch (error_already_set) {
      return Switch::insertChild( index, node );
    }
  }									
  bool default_insertChild( unsigned int index, Node* node ) { return this->Switch::insertChild( index, node ); }

  bool  insertChild( unsigned int index, Node* node, bool value ) {
    try{
      return call_method<bool>(self, "insertChild", index, ptr(node), value);
    }catch (error_already_set) {
      return Switch::insertChild( index, node, value );
    }
  }									
  bool default_insertChild( unsigned int index, Node* node, bool value ) { return this->Switch::insertChild( index, node, value ); }

  /**
   * removeChildren
   */ 
  bool  removeChildren( unsigned int pos, unsigned int numChildrenToRemove ) {
    try{
      return call_method<bool>( self, "removeChildren", pos, numChildrenToRemove );
    } catch (error_already_set) {
     return Switch::removeChildren( pos, numChildrenToRemove );
    }
  }									
  bool default_removeChildren( unsigned int pos, unsigned int numChildrenToRemove) 
  { return this->Switch::removeChildren( pos, numChildrenToRemove ); }

  /**
   * computeBound
   */ 
  BoundingSphere  computeBound( ) const {
    try {
      return call_method<BoundingSphere>( self, "computeBound" );
    }catch (error_already_set) {
      return Switch::computeBound();
    }
  }									
  BoundingSphere default_computeBound() const 
  { return this->Switch::computeBound(); }

 private:
    PyObject* self;

};


// these should go somewhere else
template <typename T>
struct VecToList{
  static PyObject* convert(const std::vector<T>& vec)
    {
        boost::python::list* l = new boost::python::list();
        for(size_t i = 0; i < vec.size(); i++)
            (*l).append(vec[i]);

        return l->ptr();
    }
};

void set_value_list( Switch& s, boost::python::list& l ){
  std::vector<bool> vec;
  for( int i(0); i < len(l); i++)
    vec.push_back( boost::python::extract<bool>(l[i]) );
  s.setValueList( vec );
}

void export_Switch(){
  bool(Switch::*addChild_Node)( Node* ) = &Switch::addChild;
  bool(Switch::*addChild_Node_Val)( Node*, bool) = &Switch::addChild;
  bool(Switch::*insertChild_Node)( unsigned , Node*) = &Switch::insertChild;
  bool(Switch::*insertChild_Node_Val)( unsigned, Node*, bool) = &Switch::insertChild;

  bool(Switch_wrapper::*default_addChild_Node)( Node* ) = &Switch_wrapper::default_addChild;
  bool(Switch_wrapper::*default_addChild_Node_Val)( Node* , bool) = &Switch_wrapper::default_addChild;
  bool(Switch_wrapper::*default_insertChild_Node)( unsigned, Node* ) = &Switch_wrapper::default_insertChild;
  bool(Switch_wrapper::*default_insertChild_Node_Val)( unsigned, Node* , bool) = &Switch_wrapper::default_insertChild;

  to_python_converter<std::vector<bool>, VecToList<bool> >();

  class_<Switch, Switch_wrapper, bases<Group, Node>, ref_ptr<Switch>  >("Switch")
    // virtual member functions
    //.def("traverse", &Switch::traverse, &Switch_wrapper::default_traverse )
    .def("traverse", &Switch::traverse )
    .def("addChild", addChild_Node, default_addChild_Node )
    .def("addChild", addChild_Node_Val,  default_addChild_Node_Val )
    .def("insertChild", insertChild_Node, default_insertChild_Node )
    .def("insertChild", insertChild_Node_Val, default_insertChild_Node_Val )
    .def("removeChildren", &Switch::removeChildren, &Switch_wrapper::default_removeChildren )
    .def("computeBound", &Switch::computeBound, &Switch_wrapper::default_computeBound )
    // non-virtual member functions as properties
    .add_property("newChildDefaultValue", &Switch::getNewChildDefaultValue, &Switch::setNewChildDefaultValue)
    .add_property("valueList", make_function( &Switch::getValueList, osgBoostPython::default_const_reference_policy() ),
		  set_value_list )
    .add_property("__setitem__", &Switch::setValue)
    .add_property("__getitem__", &Switch::getValue)
    .def("setChildValue", &Switch::setChildValue)
    .def("getChildValue", &Switch::getChildValue)
    .def("setNewChildDefaultValue", &Switch::setNewChildDefaultValue)
    .def("setAllChildrenOff", &Switch::setAllChildrenOff)
    .def("setAllChildrenOn", &Switch::setAllChildrenOn)
    .def("setSingleChildOn", &Switch::setSingleChildOn)
   ;

} 

