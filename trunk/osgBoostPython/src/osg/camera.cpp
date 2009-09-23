#include <boost/python.hpp>
//#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
using namespace boost::python;

#include <osg/Camera>
#include <osg/CullSettings>

using namespace osg;

#include "defaults.h"

void (Camera::*Camera_setViewport1)( osg::Viewport* viewport ) = &Camera::setViewport;
void (Camera::*Camera_setViewport2)( int x,int y,int width,int height ) = &Camera::setViewport;
void (Camera::*Camera_setRenderTargetImplementation1)( Camera::RenderTargetImplementation impl ) = &Camera::setRenderTargetImplementation;
void (Camera::*Camera_setRenderTargetImplementation2)( Camera::RenderTargetImplementation impl, Camera::RenderTargetImplementation fallback ) = &Camera::setRenderTargetImplementation;

void (Camera::*Camera_attach1)( Camera::BufferComponent buffer, GLenum internalFormat ) = &Camera::attach;
void (Camera::*Camera_attach2)( Camera::BufferComponent buffer, osg::Texture* texture, unsigned int level, unsigned int face, bool mipMapGeneration, unsigned int multisampleSamples, unsigned int multisampleColorSamples ) = &Camera::attach;
void (Camera::*Camera_attach3)( Camera::BufferComponent buffer, osg::Image* image, unsigned int multisampleSamples, unsigned int multisampleColorSamples ) = &Camera::attach;

void Camera_setDefaultClearMask(osg::Camera*c){
    c->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void export_camera()
{

       class_<CullSettings, boost::noncopyable>("CullSettings");

       scope in_Camera = class_<Camera, bases<Transform, CullSettings>, ref_ptr<Camera>, boost::noncopyable >("Camera")
            .def(init<>())
  
            .def("setClearColor", &Camera::setClearColor)
            .def("setClearMask", &Camera::setClearMask)
            .def("getClearMask", &Camera::getClearMask)
            .def("setProjectionMatrixAsFrustum", &Camera::setProjectionMatrixAsFrustum)
            .def("setReferenceFrame", &Camera::setReferenceFrame)
            .def("setViewMatrixAsLookAt", &Camera::setViewMatrixAsLookAt)
            .def("setViewport", Camera_setViewport1)
            .def("setViewport", Camera_setViewport2)
            .def("setRenderOrder", &Camera::setRenderOrder)
            .def("setRenderTargetImplementation", Camera_setRenderTargetImplementation1)
            .def("setRenderTargetImplementation", Camera_setRenderTargetImplementation2)
            .def("setDefaultClearMask", &Camera_setDefaultClearMask)
            .def("attach", Camera_attach1)
            .def("attach", Camera_attach2)
            .def("attach", Camera_attach3)
            .def("setPostDrawCallback", &Camera::setPostDrawCallback)
            .def("addChild", &Camera::addChild)
       ;

       enum_<Camera::RenderTargetImplementation>("RenderTargetImplementation");
            scope().attr("FRAME_BUFFER_OBJECT") = Camera::FRAME_BUFFER_OBJECT;
            scope().attr("PIXEL_BUFFER_RTT") = Camera::PIXEL_BUFFER_RTT;
            scope().attr("PIXEL_BUFFER") = Camera::PIXEL_BUFFER;
            scope().attr("FRAME_BUFFER") = Camera::FRAME_BUFFER;
            scope().attr("SEPERATE_WINDOW") = Camera::SEPERATE_WINDOW;

       enum_<Camera::RenderOrder>("RenderOrder");
            scope().attr("PRE_RENDER") = Camera::PRE_RENDER;
            scope().attr("NESTED_RENDER") = Camera::NESTED_RENDER;
            scope().attr("POST_RENDER") = Camera::POST_RENDER;

       enum_<Camera::BufferComponent>("BufferComponent");
            scope().attr("DEPTH_BUFFER") = Camera::DEPTH_BUFFER;
            scope().attr("STENCIL_BUFFER") = Camera::STENCIL_BUFFER;
            scope().attr("PACKED_DEPTH_STENCIL_BUFFER") = Camera::PACKED_DEPTH_STENCIL_BUFFER;
            scope().attr("COLOR_BUFFER") = Camera::COLOR_BUFFER;
            scope().attr("COLOR_BUFFER0") = Camera::COLOR_BUFFER0;
            scope().attr("COLOR_BUFFER1") = Camera::COLOR_BUFFER1;
            scope().attr("COLOR_BUFFER2") = Camera::COLOR_BUFFER2;
            scope().attr("COLOR_BUFFER3") = Camera::COLOR_BUFFER3;
            scope().attr("COLOR_BUFFER4") = Camera::COLOR_BUFFER4;
            scope().attr("COLOR_BUFFER5") = Camera::COLOR_BUFFER5;
            scope().attr("COLOR_BUFFER6") = Camera::COLOR_BUFFER6;
            scope().attr("COLOR_BUFFER7") = Camera::COLOR_BUFFER7;
            scope().attr("COLOR_BUFFER8") = Camera::COLOR_BUFFER8;
            scope().attr("COLOR_BUFFER9") = Camera::COLOR_BUFFER9;
            scope().attr("COLOR_BUFFER10") = Camera::COLOR_BUFFER10;
            scope().attr("COLOR_BUFFER11") = Camera::COLOR_BUFFER11;
            scope().attr("COLOR_BUFFER12") = Camera::COLOR_BUFFER12;
            scope().attr("COLOR_BUFFER13") = Camera::COLOR_BUFFER13;
            scope().attr("COLOR_BUFFER14") = Camera::COLOR_BUFFER14;
            scope().attr("COLOR_BUFFER15") = Camera::COLOR_BUFFER15;        

        enum_< Camera::ProjectionResizePolicy>("ProjectionResizePolicy");
            scope().attr("FIXED") = Camera::FIXED;
            scope().attr("HORIZONTAL") = Camera::HORIZONTAL;
            scope().attr("VERTICAL") = Camera::VERTICAL;

        enum_< Camera::TransformOrder>("TransformOrder");
            scope().attr("PRE_MULTIPLY") = Camera::PRE_MULTIPLY;
            scope().attr("POST_MULTIPLY") = Camera::POST_MULTIPLY;

}
