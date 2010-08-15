#include <boost/python.hpp>
using namespace boost::python;

#include <osg/NodeCallback>
#include <osg/NodeVisitor>
#include <osg/Group>
#include <osg/Drawable>
#include <osg/FrameStamp>
#include <osg/RenderInfo>

using namespace osg;

#include "defaults.h"

#include <iostream>

typedef Drawable::UpdateCallback UpdateCallback;

/// Note, need a way to document that the method that needs to be 
/// implemented in Python is call, not operator() or __call__ or
/// anything like that.
struct NodeCallback_wrapper : public NodeCallback
{
    // NodeCallback constructor storing initial self parameter
    NodeCallback_wrapper(PyObject *p)
        : NodeCallback(), self(p)
    {
        //PyINCREF(self);
        std::cout << "NodeCallback_wrapper(p) : ref count is " << this->referenceCount() << std::endl;
        //this->ref();
    }

    // In case NodeCallback is returned by-value from a wrapped function
    NodeCallback_wrapper(PyObject *p, const NodeCallback& x)
        : NodeCallback(x), self(p)
    {
        //PyINCREF(self);
        std::cout << "NodeCallback_wrapper(p,x) : ref count is " << this->referenceCount() << std::endl;
        std::cout << "x had " << x.referenceCount() << " refs" << std::endl;
        //this->ref();
    }

    // Override operator() to call back into Python
    void operator()(Node* node, NodeVisitor* nv)
    {
        call_method<void>(self, "call", ptr(node), ptr(nv));
    }

    // Supplies the default implementation of operator()
    void default_call(NodeCallback& self_, Node* node, NodeVisitor* nv)
    {
        self_.NodeCallback::operator()(node, nv);
    }

//protected:
    ~NodeCallback_wrapper()
    {
        //PyDECREF(self);
        std::cout << "~NodeCallback_wrapper : ref count is " << this->referenceCount() << std::endl;
        //this->unref();
    }


 private:
    PyObject* self;
};

struct NodeVisitor_wrapper : public NodeVisitor
{
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
        call_method<void>(self, "apply_Node", boost::ref(node));
    }

    // Supplies the default implementation of apply
    void default_apply_Node(NodeVisitor& self_, Node& node)
    {
        self_.NodeVisitor::apply(node);
    }

    // Override apply to call back into Python
    void apply(Group& node)
    {
        call_method<void>(self, "apply_Group", boost::ref(node));
    }

    // Supplies the default implementation of apply
    void default_apply_Group(NodeVisitor& self_, Group& node)
    {
        self_.NodeVisitor::apply(node);
    }

 private:
    PyObject* self;
};


struct Drawable_UpdateCallback_wrapper : public Drawable::UpdateCallback
{
    // Drawable::UpdateCallback constructors storing initial self parameter
    Drawable_UpdateCallback_wrapper(PyObject *p) 
        : Drawable::UpdateCallback(), self(p) {}
    // In case Drawable::UpdateCallback is returned by-value from a wrapped function
    Drawable_UpdateCallback_wrapper(PyObject *p, const Drawable::UpdateCallback& x) 
        : Drawable::UpdateCallback(x), self(p) {}

    // Override update to call back into Python
    void update(NodeVisitor* nv, Drawable* d)
    {
        call_method<void>(self, "update", ptr(nv), ptr(d));
    }

    // Supplies the default implementation of update
    void default_update(Drawable::UpdateCallback& self_, NodeVisitor* nv, Drawable* d)
    {
        self_.Drawable::UpdateCallback::update(nv,d);
    }
 private:
    PyObject* self;
};


struct Drawable_EventCallback_wrapper : public Drawable::EventCallback
{
    // Drawable::EventCallback constructor storing initial self parameter
    Drawable_EventCallback_wrapper(PyObject *p)
        : Drawable::EventCallback(), self(p) {}

    // In case Drawable::EventCallback is returned by-value from a wrapped function
    Drawable_EventCallback_wrapper(PyObject *p, const Drawable::EventCallback& x)
        : Drawable::EventCallback(x), self(p) {}

    // This version will be called by OSG, and calls the python version.
    void event(osg::NodeVisitor* nv, osg::Drawable* drawable)
    {
        call_method<void>(self, "event", ptr(nv), ptr(drawable));
    }

    // Supplies the default implementation of update
    void default_event(Drawable::EventCallback& self_, osg::NodeVisitor* nv, osg::Drawable* drawable)
    {
        self_.Drawable::EventCallback::event(nv, drawable);
    }

private:
    PyObject* self;
};


struct Drawable_CullCallback_wrapper : public Drawable::CullCallback
{
    // Drawable::CullCallback constructor storing initial self parameter
    Drawable_CullCallback_wrapper(PyObject *p)
        : Drawable::CullCallback(), self(p) {}

    // In case Drawable::CullCallback is returned by-value from a wrapped function
    Drawable_CullCallback_wrapper(PyObject *p, const Drawable::CullCallback& x)
        : Drawable::CullCallback(x), self(p) {}

    // This version will be called by OSG, and calls the python version.
    bool cull(osg::NodeVisitor* nv, osg::Drawable* drawable, osg::State* state)
    {
        return call_method<bool>(self, "cull", ptr(nv), ptr(drawable), ptr(state));
    }

    // Supplies the default implementation of update
    bool default_cull1(Drawable::CullCallback& self_, osg::NodeVisitor* nv, osg::Drawable* drawable, osg::State* state)
    {
        return self_.Drawable::CullCallback::cull(nv, drawable, state);
    }

    // This version will be called by OSG, and calls the python version.
    bool cull(osg::NodeVisitor* nv, osg::Drawable* drawable, osg::RenderInfo* renderInfo)
    {
        return call_method<bool>(self, "cull", ptr(nv), ptr(drawable), ptr(renderInfo));
    }

    // Supplies the default implementation of update
    bool default_cull2(Drawable::CullCallback& self_, osg::NodeVisitor* nv, osg::Drawable* drawable, osg::RenderInfo* renderInfo)
    {
        return self_.Drawable::CullCallback::cull(nv, drawable, renderInfo);
    }

private:
    PyObject* self;
};


struct Drawable_DrawCallback_wrapper : public Drawable::DrawCallback
{
    // Drawable::DrawCallback constructor storing initial self parameter
    Drawable_DrawCallback_wrapper(PyObject *p)
        : Drawable::DrawCallback(), self(p) {}

    // In case Drawable::DrawCallback is returned by-value from a wrapped function
    Drawable_DrawCallback_wrapper(PyObject *p, const Drawable::DrawCallback& x)
        : Drawable::DrawCallback(x), self(p) {}

    // This version will be called by OSG, and calls the python version.
    void drawImplementation(osg::RenderInfo& renderInfo, const osg::Drawable* drawable)
    {
        call_method<void>(self, "drawImplementation", boost::ref(renderInfo), ptr(drawable));
    }

    // Supplies the default implementation of update
    void default_drawImplementation(Drawable::DrawCallback& self_, osg::RenderInfo& renderInfo, const osg::Drawable* drawable)
    {
        self_.Drawable::DrawCallback::drawImplementation(renderInfo, drawable);
    }

private:
    PyObject* self;
};



void export_util()
{
    class_<RenderInfo>("RenderInfo")
        // TODO
    ;

    {
        scope in_NodeVisitor = class_<NodeVisitor, NodeVisitor_wrapper, bases<Referenced>, ref_ptr<NodeVisitor> >("NodeVisitor")
            .def(init<NodeVisitor::TraversalMode>())
            .def(init<NodeVisitor::VisitorType, NodeVisitor::TraversalMode>())
            .def("traverse", &NodeVisitor::traverse)
            .def("apply_Node", &NodeVisitor_wrapper::default_apply_Node)
            .def("apply_Group", &NodeVisitor_wrapper::default_apply_Group)
            .add_property("traversalMode", &NodeVisitor::getTraversalMode, &NodeVisitor::setTraversalMode)
            .def("getFrameStamp", &NodeVisitor::getFrameStamp, osgBoostPython::default_pointer_policy())

        ;

        enum_<NodeVisitor::TraversalMode>("TraversalMode");
            scope().attr("TRAVERSE_NONE") = NodeVisitor::TRAVERSE_NONE;
            scope().attr("TRAVERSE_PARENTS") = NodeVisitor::TRAVERSE_PARENTS;
            scope().attr("TRAVERSE_ALL_CHILDREN") = NodeVisitor::TRAVERSE_ALL_CHILDREN;
            scope().attr("TRAVERSE_ACTIVE_CHILDREN") = NodeVisitor::TRAVERSE_ACTIVE_CHILDREN;

        enum_<NodeVisitor::VisitorType>("VisitorType");
            scope().attr("NODE_VISITOR") = NodeVisitor::NODE_VISITOR;
            scope().attr("UPDATE_VISITOR") = NodeVisitor::UPDATE_VISITOR;
            scope().attr("EVENT_VISITOR") = NodeVisitor::EVENT_VISITOR;
            scope().attr("COLLECT_OCCLUDER_VISITOR") = NodeVisitor::COLLECT_OCCLUDER_VISITOR;
            scope().attr("CULL_VISITOR") = NodeVisitor::CULL_VISITOR;

    }

    class_<NodeCallback, NodeCallback_wrapper, bases<Object>, ref_ptr<NodeCallback> >("NodeCallback")
        .def("call", &NodeCallback_wrapper::default_call)
        .def("traverse", &NodeCallback::traverse)
    ;

    class_<Drawable::UpdateCallback, Drawable_UpdateCallback_wrapper, bases<Object>, ref_ptr<UpdateCallback> >("UpdateCallback")
        .def("update", &Drawable_UpdateCallback_wrapper::default_update)
    ;

    class_<Drawable::EventCallback, Drawable_EventCallback_wrapper, bases<Object>, ref_ptr<Drawable::EventCallback> >("EventCallback")
        .def("event", &Drawable_EventCallback_wrapper::default_event)
    ;

    class_<Drawable::CullCallback, Drawable_CullCallback_wrapper, bases<Object>, ref_ptr<Drawable::CullCallback> >("CullCallback")
        .def("cull", &Drawable_CullCallback_wrapper::default_cull1)
        .def("cull", &Drawable_CullCallback_wrapper::default_cull2)
    ;

    class_<Drawable::DrawCallback, Drawable_DrawCallback_wrapper, bases<Object>, ref_ptr<Drawable::DrawCallback> >("DrawCallback")
        .def("drawImplementation", &Drawable_DrawCallback_wrapper::default_drawImplementation)
    ;

}
