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


    {
       scope in_Camera = class_<Camera, bases<Transform>, ref_ptr<Camera>, boost::noncopyable >("Camera")      //bases are Transform and CullSettings, but how to tell boost??
            .def(init<>())
            .def("setClearColor", &Camera::setClearColor)
            .def("setClearMask", &Camera::setClearMask)
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
    }

        enum_<Camera::RenderTargetImplementation>("RenderTargetImplementation")
            .value("FRAME_BUFFER_OBJECT",     Camera::FRAME_BUFFER_OBJECT)
            .value("PIXEL_BUFFER_RTT",      Camera::PIXEL_BUFFER_RTT)
            .value("PIXEL_BUFFER", Camera::PIXEL_BUFFER)
            .value("FRAME_BUFFER", Camera::FRAME_BUFFER)
            .value("SEPERATE_WINDOW", Camera::SEPERATE_WINDOW)
        ;

       enum_<Camera::RenderOrder>("RenderOrder")
            .value("PRE_RENDER",     Camera::PRE_RENDER)
            .value("NESTED_RENDER",      Camera::NESTED_RENDER)
            .value("POST_RENDER", Camera::POST_RENDER)
        ;

       enum_<Camera::BufferComponent>("BufferComponent")
            .value("DEPTH_BUFFER",     Camera::DEPTH_BUFFER)
            .value("STENCIL_BUFFER",      Camera::STENCIL_BUFFER)
            .value("PACKED_DEPTH_STENCIL_BUFFER", Camera::PACKED_DEPTH_STENCIL_BUFFER)
            .value("COLOR_BUFFER",     Camera::COLOR_BUFFER)
            .value("COLOR_BUFFER0",    Camera::COLOR_BUFFER0)
            .value("COLOR_BUFFER1",     Camera::COLOR_BUFFER1)
            //todo: add other color buffer enum values...
        ;

}
