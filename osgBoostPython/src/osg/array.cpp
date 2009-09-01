#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
using namespace boost::python;

#define WIN32

#include <osg/Array>
#include <osg/MixinVector>

#include "ContainerUtils.h"

using namespace osg;


// http://cci.lbl.gov/cctbx_sources/scitbx/array_family/boost_python/flex_wrapper.h
template<typename ContainerType>
struct ArrayWrapper
{
    //typedef ContainerType::ElementDataType ElementType;

    typedef boost::python::class_<ContainerType, bases<Array>, ref_ptr<ContainerType> > class_t;

    static class_t wrap(const std::string& name)
    {
        class_t result(name.c_str());
        result
            .def("__len__", &ContainerType::size)

            // TODO: Not all are needed, but a few...
            // At least support whatever is needed to give a python-esque interface.

            //.def(init<flex_grid<> const&, optional<ElementType const&> >())
            //.def(init<std::size_t, optional<ElementType const&> >())
            //.def(init<shared_plain<ElementType> const&>())
            //.def("element_size", element_size)
            //.staticmethod("element_size")
            //.def("accessor", accessor)
            //.def("nd", nd)
            //.def("is_0_based", is_0_based)
            //.def("origin", origin)
            //.def("all", all)
            //.def("last", last_0)
            //.def("last", last_1)
            //.def("is_padded", is_padded)
            //.def("focus", focus_0)
            //.def("focus", focus_1)
            //.def("focus_size_1d", focus_size_1d)
            //.def("is_trivial_1d", is_trivial_1d)
            //.def("shift_origin", shift_origin)
            //.def("id", id)
            //.def("size", size)
            //.def("__len__", size)
            //.def("capacity", capacity)
            //.def("__getitem__", getitem_1d, GetitemReturnValuePolicy())
            //.def("__getitem__", getitem_1d_slice)
            //.def("__getitem__", getitem_flex_grid, GetitemReturnValuePolicy())
            //.def("__setitem__", setitem_1d)
            //.def("__setitem__", setitem_flex_grid)
            //.def("__delitem__", delitem_1d)
            //.def("__delitem__", delitem_1d_slice)
            //.def("front", front, GetitemReturnValuePolicy())
            //.def("back", back, GetitemReturnValuePolicy())
            //.def("fill", fill)
            //.def("reserve", reserve)
            //.def("deep_copy", deep_copy)
            //.def("shallow_copy", shallow_copy)
            //.def("as_1d", as_1d)
            //.def("assign", assign)
            //.def("pop_back", pop_back)
            //.def("append", append)
            //.def("insert", insert_i_x)
            //.def("insert", insert_i_n_x)
            //.def("resize", resize_1d_1)
            //.def("resize", resize_1d_2)
            //.def("resize", resize_flex_grid_1)
            //.def("resize", resize_flex_grid_2)
            //.def("reshape", reshape)
            //.def("clear", clear)
            //.def("extend", extend)
            //.def("concatenate", concatenate)
            //.def("reversed", reversed)
        ;
        
        return result;
    }
};

void export_array()
{
    // Vec3Array, Vec4Array, ...

    // TODO: For a complete wrapping, we would need to:
    //       Wrap osg::Array, osg::MixinVector<T>
    //       Then osg::TemplateArray : public Array, public MixinVector<T>
    //       Then Vec3Array et al.

    // osg::Array
    {
        scope in_Array = class_<Array, bases<Object>, ref_ptr<Array>, boost::noncopyable >("Array", no_init)
            .def("dirty", &Array::dirty)
            .def("getType", &Array::getType)
        ;

        enum_<Array::Type>("Type")
            .value("ArrayType",       Array::ArrayType       )
            .value("ByteArrayType",   Array::ByteArrayType   )
            .value("ShortArrayType",  Array::ShortArrayType  )
            .value("IntArrayType",    Array::IntArrayType    )
            .value("UByteArrayType",  Array::UByteArrayType  )
            .value("UShortArrayType", Array::UShortArrayType )
            .value("UIntArrayType",   Array::UIntArrayType   )
            .value("Vec4ubArrayType", Array::Vec4ubArrayType )
            .value("FloatArrayType",  Array::FloatArrayType  )
            .value("Vec2ArrayType",   Array::Vec2ArrayType   )
            .value("Vec3ArrayType",   Array::Vec3ArrayType   )
            .value("Vec4ArrayType",   Array::Vec4ArrayType   )
            .value("Vec2sArrayType",  Array::Vec2sArrayType  )
            .value("Vec3sArrayType",  Array::Vec3sArrayType  )
            .value("Vec4sArrayType",  Array::Vec4sArrayType  )
            .value("Vec2bArrayType",  Array::Vec2bArrayType  )
            .value("Vec3bArrayType",  Array::Vec3bArrayType  )
            .value("Vec4bArrayType",  Array::Vec4bArrayType  )
            .value("DoubleArrayType", Array::DoubleArrayType )
            .value("Vec2dArrayType",  Array::Vec2dArrayType  )
            .value("Vec3dArrayType",  Array::Vec3dArrayType  )
            .value("Vec4dArrayType",  Array::Vec4dArrayType  )
        ;
    }

    // osg::MixinVector<T>
    //{
    //}

    // TODO: Not all array types are needed...
    ArrayWrapper<Vec2Array>::wrap("Vec2Array");
    ArrayWrapper<Vec3Array>::wrap("Vec3Array");
    ArrayWrapper<Vec4Array>::wrap("Vec4Array");

    //osgBoostPython::container_utils::tuple_mapping_variable_capacity< Vec3Array >();
}