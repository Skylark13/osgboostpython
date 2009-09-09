#include <boost/python.hpp>
using namespace boost::python;

#define WIN32

#include <osg/NodeCallback>
#include <osg/NodeVisitor>
#include <osg/Group>

using namespace osg;

#include <iostream>

struct NodeCallback_wrapper : public NodeCallback
{
    // NodeCallback constructor storing initial self parameter
    NodeCallback_wrapper(PyObject *p)
        : NodeCallback(), self(p) {}

    // In case NodeCallback is returned by-value from a wrapped function
    NodeCallback_wrapper(PyObject *p, const NodeCallback& x)
        : NodeCallback(x), self(p) {}

    // Override handle to call back into Python
    void operator()(Node* node, NodeVisitor* nv)
    {
        //std::cout << "in operator()(Node*, NodeVisitor*)" << std::endl;
        try {
            //std::cout << "Calling override" << std::endl;
            call_method<void>(self, "call", boost::ref(node), boost::ref(nv));
        }
        // Catch boost::python exception, means method was not overridden in subclass.
        catch (error_already_set) {
            NodeCallback::operator()(node, nv);
        }
    }

    // Supplies the default implementation of handle
    void default_operator(NodeCallback& self_, Node* node, NodeVisitor* nv)
    {
        //std::cout << "in default_operator(Node*, NodeVisitor*)" << std::endl;
        self_.NodeCallback::operator()(node, nv);
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

    // Override handle to call back into Python
    void apply(Node& node)
    {
        //std::cout << "in apply(Node&)" << std::endl;
        try {
            //std::cout << "Calling override" << std::endl;
            call_method<void>(self, "apply_Node", boost::ref(node));
        }
        // Catch boost::python exception, means method was not overridden in subclass.
        catch (error_already_set) {
            NodeVisitor::apply(node);
        }
    }

    // Supplies the default implementation of handle
    void default_apply_Node(NodeVisitor& self_, Node& node)
    {
        //std::cout << "in default_apply(Node&)" << std::endl;
        self_.NodeVisitor::apply(node);
    }

    // Override handle to call back into Python
    void apply(Group& node)
    {
        //std::cout << "in apply(Group&)" << std::endl;
        try {
            //std::cout << "Calling override" << std::endl;
            call_method<void>(self, "apply_Group", boost::ref(node));
        }
        // Catch boost::python exception, means method was not overridden in subclass.
        catch (error_already_set) {
            NodeVisitor::apply(node);
        }
    }

    // Supplies the default implementation of handle
    void default_apply_Group(NodeVisitor& self_, Group& node)
    {
        //std::cout << "in default_apply(Group&)" << std::endl;
        self_.NodeVisitor::apply(node);
    }

 private:
    PyObject* self;
};

void export_util()
{
    {
        scope in_NodeVisitor = class_<NodeVisitor, NodeVisitor_wrapper, bases<Referenced>, ref_ptr<NodeVisitor> >("NodeVisitor")
            .def(init<NodeVisitor::TraversalMode>())
            .def(init<NodeVisitor::VisitorType, NodeVisitor::TraversalMode>())
            .def("traverse", &NodeVisitor::traverse)
            .def("apply_Node", &NodeVisitor_wrapper::default_apply_Node)
            .def("apply_Group", &NodeVisitor_wrapper::default_apply_Group)
            .add_property("traversalMode", &NodeVisitor::getTraversalMode, &NodeVisitor::setTraversalMode)
        ;

        enum_<NodeVisitor::TraversalMode>("TraversalMode")
            .value("TRAVERSE_NONE",            NodeVisitor::TRAVERSE_NONE)
            .value("TRAVERSE_PARENTS",         NodeVisitor::TRAVERSE_PARENTS)
            .value("TRAVERSE_ALL_CHILDREN",    NodeVisitor::TRAVERSE_ALL_CHILDREN)
            .value("TRAVERSE_ACTIVE_CHILDREN", NodeVisitor::TRAVERSE_ACTIVE_CHILDREN)
        ;

        enum_<NodeVisitor::VisitorType>("VisitorType")
            .value("NODE_VISITOR",             NodeVisitor::NODE_VISITOR)
            .value("UPDATE_VISITOR",           NodeVisitor::UPDATE_VISITOR)
            .value("EVENT_VISITOR",            NodeVisitor::EVENT_VISITOR)
            .value("COLLECT_OCCLUDER_VISITOR", NodeVisitor::COLLECT_OCCLUDER_VISITOR)
            .value("CULL_VISITOR",             NodeVisitor::CULL_VISITOR)
        ;

    }

    class_<NodeCallback, NodeCallback_wrapper, bases<Object>, ref_ptr<NodeCallback> >("NodeCallback")
        .def("call", &NodeCallback_wrapper::default_operator)
        .def("traverse", &NodeCallback::traverse)
    ;


}
