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

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <osg/Group>
#include <osgGA/GUIEventHandler>

namespace osg
{
    class Camera;
}

namespace osgViewer
{
    class View;
}

class Console
{
public:
    Console(osgViewer::View* view);
    ~Console();

    void setVisible(bool visible);
    bool isVisible() const;

    void setHeight(double heightPercent);
    double getHeight() const;

    void setTransitionTime(double time);
    double getTransitionTime() const;

    void setColor(const osg::Vec4& color);
    osg::Vec4 getColor() const;

protected:
    class Impl;
    Impl* _impl;
};

#endif  // __CONSOLE_H__
