#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/slice.hpp>
using namespace boost::python;

#define WIN32

#include <osg/Array>
#include <osg/MixinVector>

#include <stdexcept>
#include "ContainerUtils.h"

using namespace osg;

// http://cci.lbl.gov/cctbx_sources/scitbx/misc/positive_getitem_index.h
template <typename IndexType, typename SizeType>
SizeType positive_getitem_index(IndexType const& i, SizeType const& size, bool allow_i_eq_size=false, 
                                const char* index_out_of_range = "Index out of range.")
{
    if (i >= 0)
    {
        SizeType result = static_cast<SizeType>(i);

        if ( result > size ||
             (result == size && !allow_i_eq_size))
        {
            throw std::out_of_range(index_out_of_range);
        }
        return result;
    }
    if (static_cast<SizeType>(-i) > size) 
    {
        throw std::out_of_range(index_out_of_range);
    }
    return size + i;
}


// http://cci.lbl.gov/cctbx_sources/scitbx/array_family/boost_python/flex_wrapper.h
template<typename ContainerType,
         typename GetitemReturnValuePolicy = return_value_policy<copy_non_const_reference> >
struct ArrayWrapper
{
    typedef typename ContainerType::ElementDataType ElementType;

    typedef boost::python::class_<ContainerType, bases<Array>, ref_ptr<ContainerType> > class_t;

    static ElementType& getitem_1d(ContainerType& container, long i)
    {
      //if (!a.check_shared_size()) raise_shared_size_mismatch();
      std::size_t j = positive_getitem_index(i, container.size());
      return container[j];
    }

    // Needs to return ref_ptr because ContainerType has protected dtor - conversion will be done automatically in python
    static ref_ptr<ContainerType> getitem_1d_slice(ContainerType& container, slice const& sl)
    {
        ref_ptr<ContainerType> result = new ContainerType;

        slice::range<ContainerType::iterator> bounds;
        try 
        {
            bounds = sl.get_indicies<>(container.begin(), container.end());
        }
        catch (std::invalid_argument)
        {
            return result;
        }

        while (bounds.start != bounds.stop)
        {
            result->push_back(*bounds.start);
            std::advance( bounds.start, bounds.step);
        }
        result->push_back(*bounds.start);

        return result;
    }

    static void setitem_1d(ContainerType& container, long i, ElementType const& element)
    {
      //if (!a.check_shared_size()) raise_shared_size_mismatch();
      std::size_t j = positive_getitem_index(i, container.size());
      container[j] = element;
    }

    /*
    // Doesn't work.
    static void setitem_1d_slice(ContainerType& container, slice const& sl, ContainerType& container2)
    {
        slice::range<ContainerType::iterator> c1Bounds;
        slice::range<ContainerType::iterator> c2Bounds;

        try 
        {
            c1Bounds = sl.get_indicies<>(container.begin(),  container.end());
            c1Bounds = sl.get_indicies<>(container2.begin(), container2.end());
        }
        catch (std::invalid_argument)
        {
            return;
        }

        while (c1Bounds.start != c1Bounds.stop)
        {
            *c1Bounds.start = *c2Bounds.start;
            std::advance( c1Bounds.start, c1Bounds.step);
            std::advance( c2Bounds.start, c2Bounds.step);
        }
        *c1Bounds.start = *c2Bounds.start;
    }
    */

    static void delitem_1d(ContainerType& container, long i)
    {
        std::size_t j = positive_getitem_index(i, container.size());
        container.erase(container.begin()+j);
    }

    // Untested
    static void delitem_1d_slice(ContainerType& container, slice const& sl)
    {
        slice::range<ContainerType::iterator> bounds;
        try 
        {
            bounds = sl.get_indicies<>(container.begin(), container.end());
        }
        catch (std::invalid_argument)
        {
            return;
        }

        while (bounds.start != bounds.stop)
        {
            container.erase(bounds.start);
            std::advance( bounds.start, bounds.step);
        }
        container.erase(bounds.start);
    }

    /// Add an item to the end of the list; equivalent to a[len(a):] = [x].
    static void append(ContainerType& container, ElementType const& element)
    {
        container.push_back(element);
    }

    /// Extend the list by appending all the items in the given list; 
    /// equivalent to a[len(a):] = L.
    static void extend(ContainerType& container, ContainerType /*const*/& container2) // const causes "cannot access protected member ~TemplateArray"
    {
        container.insert(container.end(), container2.begin(), container2.end());
    }

    /// Insert an item at a given position. The first argument is the index of 
    /// the element before which to insert, so a.insert(0, x) inserts at the 
    /// front of the list, and a.insert(len(a), x) is equivalent to a.append(x).
    static void insert(ContainerType& container, long i, ElementType const& element)
    {
        std::size_t j = positive_getitem_index(i, container.size(), true);
        container.insert(container.begin()+j, element);
    }

    /// Remove the first item from the list whose value is x. It is an error if 
    /// there is no such item.
    static void remove(ContainerType& container, ElementType const& element)
    {
        ContainerType::iterator it = std::find(container.begin(), container.end(), element);
        if (it != container.end())
            container.erase(it);
        else
        {
            throw std::invalid_argument("Element does not exist");
        }
    }

    /// Remove the item at the given position in the list, and return it. If no 
    /// index is specified, a.pop() removes and returns the last item in the 
    /// list.
    static ElementType pop(ContainerType& container)
    {
        ElementType element = container.back();
        container.erase(container.end() - 1);
        return element;
    }


    /// Remove the item at the given position in the list, and return it. If no 
    /// index is specified, a.pop() removes and returns the last item in the 
    /// list.
    static ElementType pop_i(ContainerType& container, long i)
    {
        std::size_t j = positive_getitem_index(i, container.size(), true);
        ElementType element = *(container.begin() + j);
        container.erase(container.begin() + j);
        return element;
    }

    /// Return the index in the list of the first item whose value is x. It is 
    /// an error if there is no such item.
    static long index(ContainerType& container, ElementType const& element)
    {
        long i = 0;
        for (ContainerType::const_iterator it = container.begin(); it != container.end(); ++it)
        {
            if (*it == element)
                return i;
            i++;
        }

        throw std::invalid_argument("Element does not exist");
    }

    /// Return the number of times x appears in the list.
    static long count(ContainerType& container, ElementType const& element)
    {
        long num = 0;
        for (ContainerType::const_iterator it = container.begin(); it != container.end(); ++it)
        {
            if (*it == element)
                num++;
        }

        return num;
    }

    /// Sort the items of the list, in place.
    static void sort(ContainerType& container)
    {
    }

    /// Reverse the elements of the list, in place.
    static void reverse(ContainerType& container)
    {
    }

    static class_t wrap(const std::string& name)
    {
        class_t result(name.c_str());
        result
            .def("__len__", &ContainerType::size)
            .def("__getitem__", getitem_1d, GetitemReturnValuePolicy())
            .def("__getitem__", getitem_1d_slice)
            .def("__setitem__", setitem_1d)
            //.def("__setitem__", setitem_1d_slice)
            .def("__delitem__", delitem_1d)
            .def("__delitem__", delitem_1d_slice)
            .def("append", append)
            .def("extend", extend)
            .def("insert", insert)
            .def("remove", remove)
            .def("pop", pop)
            .def("pop", pop_i)
            .def("index", index)
            .def("count", count)
            //.def("sort", sort)
            //.def("reverse", reverse)


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