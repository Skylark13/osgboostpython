#include <boost/python.hpp>
using namespace boost::python;

#include <osgViewer/CompositeViewer>
using namespace osg;
using namespace osgViewer;

#include <QtGui/QWidget>

#include "defaults.h"

class QWidget_CompositeViewer :
  public QWidget, public CompositeViewer {};

void export_Composites()
{
  class_<QWidget_CompositeViewer, bases<QWidget, CompositeViewer>, boost::noncopyable >
    ("QWidget_CompositeViewer");
}
