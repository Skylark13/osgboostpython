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
#include <boost/python.hpp>
using namespace boost::python;

#include <osg/ref_ptr>
#include <osg/Sequence>
using namespace osg;

#include "defaults.h"

struct Sequence_wrapper : public Sequence {
  
  Sequence_wrapper( PyObject* p ) : self( p ) {}
  Sequence_wrapper( PyObject* p, const Sequence& s ) : self( p ), Sequence( s ) {}
  /**
   * addChild 
   */ 
  bool  addChild( Node* node ) {
    try{
      return call_method<bool>(self,"addChild", ptr(node) );
    }catch (error_already_set) {
      return Sequence::addChild( node );
    }
  }									
  bool default_addChild( Node* node ) { return this->Sequence::addChild( node ); }

  bool addChild( Node* node, double value ) {
    try{
      return call_method<bool>(self, "addChild", ptr(node), value );
    } catch (error_already_set) {
      return Sequence::addChild( node, value );
    }
  }									

  bool default_addChild( Node* node, double value ) { 
    return this->Sequence::addChild( node, value ); 
  }

  /**
   * insertChild
   */ 
  bool  insertChild( unsigned int index, Node* node ) {
    try{
      return call_method<bool>(self, "insertChild", index, ptr(node) );
    } catch (error_already_set) {
      return Sequence::insertChild( index, node );
    }
  }									
  bool default_insertChild( unsigned int index, Node* node ) { return this->Sequence::insertChild( index, node ); }

  bool  insertChild( unsigned int index, Node* node, double value ) {
    try{
      return call_method<bool>(self, "insertChild", index, ptr(node), value);
    }catch (error_already_set) {
      return Sequence::insertChild( index, node, value );
    }
  }									
  bool default_insertChild( unsigned int index, Node* node, double value ) { return this->Sequence::insertChild( index, node, value ); }

  /**
   * removeChildren
   */ 
  bool  removeChildren( unsigned int pos, unsigned int numChildrenToRemove ) {
    try{
      return call_method<bool>( self, "removeChildren", pos, numChildrenToRemove );
    } catch (error_already_set) {
     return Sequence::removeChildren( pos, numChildrenToRemove );
    }
  }									
  bool default_removeChildren( unsigned int pos, unsigned int numChildrenToRemove) 
  { return this->Sequence::removeChildren( pos, numChildrenToRemove ); }

  /**
   * removeChildren
   */ 
  bool  removeChild( Node* node ) {
    try{
      return call_method<bool>( self, "removeChild", ptr(node));
    } catch (error_already_set) {
     return Sequence::removeChild( node );
    }
  }									
  bool default_removeChild( Node* node) 
  { return this->Sequence::removeChild( node ); }

  /**
   * computeBound
   */ 
  BoundingSphere  computeBound( ) const {
    try {
      return call_method<BoundingSphere>( self, "computeBound" );
    }catch (error_already_set) {
      return Sequence::computeBound();
    }
  }									
  BoundingSphere default_computeBound() const 
  { return this->Sequence::computeBound(); }

 private:
    PyObject* self;

};

tuple get_interval( Sequence&s ){
  Sequence::LoopMode lm;
  int begin(INT_MIN);
  int end(INT_MIN);
  s.getInterval( lm, begin, end);
  return make_tuple( lm, begin, end );
}

tuple get_duration( Sequence&s ){
  float speed(NAN);
  int nreps(INT_MIN);
  s.getDuration( speed, nreps);
  return make_tuple( speed, nreps );
}

void export_Sequence(){
  bool(Sequence::*addChild_Node)( Node* ) = &Sequence::addChild;
  bool(Sequence::*addChild_Node_Val)( Node*, double) = &Sequence::addChild;
  bool(Sequence::*insertChild_Node)( unsigned , Node*) = &Sequence::insertChild;
  bool(Sequence::*insertChild_Node_Val)( unsigned, Node*, double) = &Sequence::insertChild;

  bool(Sequence_wrapper::*default_addChild_Node)( Node* ) = &Sequence_wrapper::default_addChild;
  bool(Sequence_wrapper::*default_addChild_Node_Val)( Node* , double) = &Sequence_wrapper::default_addChild;
  bool(Sequence_wrapper::*default_insertChild_Node)( unsigned, Node* ) = &Sequence_wrapper::default_insertChild;
  bool(Sequence_wrapper::*default_insertChild_Node_Val)( unsigned, Node* , double) = &Sequence_wrapper::default_insertChild;

  scope in_Sequence = class_<Sequence, Sequence_wrapper, bases<Group>, ref_ptr<Sequence>  >("Sequence")
    .def("traverse", &Sequence::traverse )
    .def("addChild", addChild_Node, default_addChild_Node )
    .def("addChild", addChild_Node_Val,  default_addChild_Node_Val )
    .def("insertChild", insertChild_Node, default_insertChild_Node )
    .def("insertChild", insertChild_Node_Val, default_insertChild_Node_Val )
    .def("removeChild", &Sequence::removeChild, &Sequence_wrapper::default_removeChild )
    .def("removeChildren", &Sequence::removeChildren, &Sequence_wrapper::default_removeChildren )
    .def("computeBound", &Sequence::computeBound, &Sequence_wrapper::default_computeBound )
    .add_property("value", &Sequence::getValue, &Sequence::setValue )
    .add_property("time", &Sequence::getTime, &Sequence::setTime )
    .add_property("timeList", make_function( &Sequence::getTimeList, osgBoostPython::default_const_reference_policy() ),
		  &Sequence::setTimeList )
    .add_property("defaultTime", &Sequence::getDefaultTime, &Sequence::setDefaultTime )
    .add_property("lastFrameTime", &Sequence::getLastFrameTime, &Sequence::setLastFrameTime )
    .add_property("numFrames", &Sequence::getNumFrames )
    .add_property("loopMode", &Sequence::getLoopMode, &Sequence::setLoopMode )
    .add_property("begin", &Sequence::getBegin, &Sequence::setBegin )
    .add_property("end", &Sequence::getEnd, &Sequence::setEnd )
    .def("setInterval", &Sequence::setInterval )
    .def("getInterval", get_interval )
    .add_property("speed", &Sequence::getSpeed, &Sequence::setSpeed )
    .add_property("numRepeats", &Sequence::getNumRepeats, &Sequence::setNumRepeats )
    .def("setDuration", &Sequence::setDuration )
    .def("getDuration", get_duration )
    .add_property("mode", &Sequence::getMode, &Sequence::setMode )
    .add_property("sync", &Sequence::getSync, &Sequence::setSync )
    .add_property("clearOnStop", &Sequence::getClearOnStop, &Sequence::setClearOnStop )
    
    ;

   enum_<Sequence::LoopMode>("LoopMode");
   scope().attr("LOOP") = Sequence::LOOP;
   scope().attr("SWING") = Sequence::SWING;
   
   enum_<Sequence::SequenceMode>("SequenceMode");
   scope().attr("START") = Sequence::START;
   scope().attr("STOP") = Sequence::STOP;
   scope().attr("PAUSE") = Sequence::PAUSE;
   scope().attr("RESUME") = Sequence::RESUME;
   
} 

