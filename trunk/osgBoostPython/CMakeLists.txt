cmake_minimum_required(VERSION 2.8)

project(boost_python_osg)

#
# Find Open Scene Graph and set needed variables
#
set(OSG_COMPONENTS osgDB osgGA osgViewer osgUtil)
find_package(OpenSceneGraph REQUIRED 
  COMPONENTS ${OSG_COMPONENTS} )

#
# Find Boost and set needed variables
#
set(BOOST_COMPONENTS python)
find_package(Boost REQUIRED COMPONENTS 
  ${BOOST_COMPONENTS} )
include_directories(${Boost_INCLUDE_DIRS})

#
# Find Python and set needed variables
#
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

#
# Now setup our build
# 
include_directories(${CMAKE_SOURCE_DIR}/include/)

# loop over all of these libraries and link them to boost::python and python
set(PYOSG_LIBS osg osgUtil osgGA osgDB osgViewer)
foreach( LIB ${PYOSG_LIBS} )  
  file(GLOB THIS_SOURCE_LIST "${CMAKE_SOURCE_DIR}/src/${LIB}/*.cpp")
  add_library(${LIB} SHARED
    ${THIS_SOURCE_LIST}
    )
  set_target_properties(${LIB} PROPERTIES PREFIX "_")
  set_target_properties(${LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${LIB}/")
  target_link_libraries(${LIB} ${OPENSCENEGRAPH_LIBRARIES})
  target_link_libraries(${LIB} ${Boost_LIBRARIES})
  target_link_libraries(${LIB} ${PYTHON_LIBRARIES})
endforeach( LIB PYOSG_LIBS )

