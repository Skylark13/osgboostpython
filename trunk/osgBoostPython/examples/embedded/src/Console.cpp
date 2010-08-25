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

#include "Console.h"

#include <osgViewer/View>

#include <osgWidget/Frame>
#include <osgWidget/Input>
#include <osgWidget/WindowManager>
#include <osgWidget/ViewerEventHandlers>
#include <osgWidget/EventInterface>


class CommandInput : public osgWidget::Input
{
public:
    CommandInput(const std::string& name = "", const std::string& label = "", unsigned int size = 20)
        : osgWidget::Input(name, label, size)
    {
    }

    void setCommand(const std::string& command)
    {
        _text->setText(command);

        _index = command.length();
        _selectionStartIndex = _selectionEndIndex = _index;

        _text->update();

        _calculateCursorOffsets();

        _calculateSize(getTextSize());

        getParent()->resize();
    }
};


const unsigned int MASK_2D = 0xF0000000;

class Console::Impl : public osgWidget::Frame
{
public:
    Impl(osgViewer::View* view);

    void setVisible(bool visible, bool transition = true);
    bool isVisible() const;

    void setHeight(double heightPercent);
    double getHeight() const;

    void setTransitionTime(double time);
    double getTransitionTime() const;

    void setColor(const osg::Vec4& color);
    osg::Vec4 getColor() const;

    void update(double simulationTime);
    virtual void update();

    void deleteThis();

    virtual bool handleKeyUp(osgWidget::Event& ev);

    void addExecuteCallback(ExecuteCallback* callback);
    void removeExecuteCallback(ExecuteCallback* callback);
    const ExecuteCallbacks& getExecuteCallbacks() const;

protected:
    class ConsoleEventHandler : public osgGA::GUIEventHandler
    {
    public:
        ConsoleEventHandler(Impl* _impl, osgViewer::View* view);

        virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor* nv);

    protected:
        Impl* _impl;
        int _prevFrameNumber;
        osgWidget::WindowManager* _windowManager;
    };

    ~Impl();
    void removeFromAllViews();
    void setVisibleImmediately(bool visible);

    osg::ref_ptr<Impl> _thisPtr;

    osgWidget::Box*   _box;
    osgWidget::Label* _history;
    CommandInput*     _input;

    bool _visible;
    double _heightPercent;
    double _prevSimulationTime;
    ConsoleEventHandler* _eventHandler;

    double _yWhenVisible;
    double _yWhenHidden;

    double _oldWidth;
    double _oldHeight;

    double _transitionTime; // Number of seconds for transition

    Console::ExecuteCallbacks _executeCallbacks;
    std::vector<std::string> _commandHistory;
    unsigned int _commandHistoryIndex;
};


Console::Impl::Impl(osgViewer::View* view)
    : osgWidget::Frame("console", osgWidget::Frame::FRAME_ALL)
    , _thisPtr()
    , _box(new osgWidget::Box("consoleBox", osgWidget::Box::VERTICAL))
    , _history(new osgWidget::Label("consoleHistory", ""))
    , _input(new CommandInput("consoleInput", "", 100))
    , _visible(false)
    , _heightPercent(0.7)
    , _prevSimulationTime(0.0)
    , _eventHandler(NULL)
    , _yWhenVisible(floor(768.0 - 768.0 * _heightPercent))
    , _yWhenHidden(768.0)
    , _oldWidth(1024.0)
    , _oldHeight(768.0)
    , _transitionTime(0.5)
    , _executeCallbacks()
    , _commandHistory()
    , _commandHistoryIndex(0)
{
    osgWidget::Frame::createSimpleFrame(
        "console",
        0,
        0,
        1024.0,
        floor(768.0 * _heightPercent),
        osgWidget::Frame::FRAME_ALL,
        this
    );

    _thisPtr = this;
    _eventHandler = new ConsoleEventHandler(this, view);
    view->addEventHandler(_eventHandler);

    this->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    this->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
    this->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    this->getOrCreateStateSet()->setAttribute(new osg::Program);

    this->getEmbeddedWindow()->setColor(osg::Vec4(0.5, 0.5, 0.5, 0.5));
    this->getEmbeddedWindow()->setCanFill(true);

    this->getBackground()->setColor(osg::Vec4(0.0, 0.0, 0.0, 0.0));

    this->setWindow(_box);

    _box->getBackground()->setColor(osg::Vec4(0.0, 0.0, 0.0, 0.0));
    _box->getBackground()->setCanFill(true);

    _input->setColor(osg::Vec4(0.8, 0.8, 0.8, 0.8));
    _input->setFont("fonts/VeraMono.ttf");
    _input->setFontColor(0.0f, 0.0f, 0.0f, 1.0f);
    _input->setFontSize(15);
    _input->setYOffset(_input->calculateBestYOffset("y"));
    _input->setSize(1024.0, _input->getText()->getCharacterHeight());
    _box->addWidget(_input);

    _history->setCanFill(true);
    _history->setColor(osg::Vec4(0.0, 0.0, 0.0, 0.0));
    _history->setFont("fonts/VeraMono.ttf");
    _history->setFontColor(1.0f, 1.0f, 1.0f, 1.0f);
    _history->setFontSize(15);
    _history->setSize(1024.0, 768.0 - _input->getText()->getCharacterHeight());
    _history->getText()->setMaximumWidth(1024.0);
    _history->getText()->setMaximumHeight(768.0 - _input->getText()->getCharacterHeight());
    _history->setAlignHorizontal(osgWidget::Widget::HA_LEFT);
    _history->setAlignVertical(osgWidget::Widget::VA_BOTTOM);
    _history->getText()->setAlignment(osgText::Text::LEFT_BOTTOM_BASE_LINE);
    _history->getText()->setKerningType(osgText::KERNING_NONE);
    _history->getText()->update();
    _box->addWidget(_history);

    // To apply the correct initial position.
    setVisible(_visible, false);

    _input->addCallback(
        new osgWidget::Callback(
            &Console::Impl::handleKeyUp,
            this,
            osgWidget::EVENT_KEY_UP
        ));

    // Set initial focus correctly.
    this->setFocused(_input);
}

Console::Impl::~Impl()
{
    removeFromAllViews();
}

void Console::Impl::removeFromAllViews()
{/*
    int i = this->getNumParents() - 1;
    while (i >= 0)
    {
        osg::Group* parent = this->getParent(i);
        parent->removeChild(this);

        osg::Camera* camera = dynamic_cast<osg::Camera*>(parent);
        if (camera)
        {
            osgViewer::View* view = dynamic_cast<osgViewer::View*>(camera->getView());
            if (view)
            {
                view->removeEventHandler(_eventHandler);
            }
        }

        --i;
    }*/
}

void Console::Impl::update(double simulationTime)
{
    double y = this->getY();
    double deltaTime = simulationTime - _prevSimulationTime;
    if (_visible)
    {
        if (y > _yWhenVisible)
        {
            double newY = floor(y - (_yWhenHidden - _yWhenVisible) / _transitionTime * deltaTime);
            if (newY < _yWhenVisible)
                newY = _yWhenVisible;
            this->setY(newY);
            update();
        }
    }
    else
    {
        if (y < _yWhenHidden)
        {
            double newY = floor(y + (_yWhenHidden - _yWhenVisible) / _transitionTime * deltaTime);
            if (newY > _yWhenHidden)
                newY = _yWhenHidden;
            this->setY(newY);
            update();
        }
    }

    _prevSimulationTime = simulationTime;
}

void Console::Impl::update()
{
    if (this->getWidth() != _oldWidth || 
        this->getHeight() != _oldHeight)
    {
        _input->setSize(this->getWidth(), _input->getText()->getCharacterHeight());
        _history->setSize(this->getWidth(), this->getHeight() - _input->getText()->getCharacterHeight());

        _yWhenVisible = floor(this->getHeight() - this->getHeight() * _heightPercent);
        _yWhenHidden = this->getHeight();

        _oldWidth = this->getWidth();
        _oldHeight = this->getHeight();
    }

    _box->update();
    osgWidget::Frame::update();
}

void Console::Impl::setVisible(bool visible, bool transition)
{
    if (!transition)
    {
        this->setY(visible ? _yWhenVisible : _yWhenHidden);
        update();
    }

    _visible = visible;
}

bool Console::Impl::isVisible() const
{
    return _visible;
}

void Console::Impl::setHeight(double heightPercent)
{
    _heightPercent = heightPercent;
    _yWhenVisible = floor(this->getHeight() - this->getHeight() * _heightPercent);

    this->resize(this->getWidth(), floor(this->getHeight() * _heightPercent));
}

double Console::Impl::getHeight() const
{
    return osgWidget::Frame::getHeight();
}

void Console::Impl::setTransitionTime(double time)
{
    _transitionTime = time;
}

double Console::Impl::getTransitionTime() const
{
    return _transitionTime;
}

void Console::Impl::setColor(const osg::Vec4& color)
{
    this->getEmbeddedWindow()->setColor(color);
}

osg::Vec4 Console::Impl::getColor() const
{
    return this->getEmbeddedWindow()->getColor();
}

void Console::Impl::deleteThis()
{
    removeFromAllViews();
    _thisPtr = 0;
}

void Console::Impl::addExecuteCallback(ExecuteCallback* callback)
{
    _executeCallbacks.push_back(callback);
}

void Console::Impl::removeExecuteCallback(ExecuteCallback* callback)
{
    ExecuteCallbacks::iterator it = std::find(_executeCallbacks.begin(), _executeCallbacks.end(), callback);
    if (it != _executeCallbacks.end())
        _executeCallbacks.erase(it);
}

const Console::ExecuteCallbacks& Console::Impl::getExecuteCallbacks() const
{
    return _executeCallbacks;
}

bool Console::Impl::handleKeyUp(osgWidget::Event& ev)
{
    if (ev.key == osgGA::GUIEventAdapter::KEY_Return && ev.keyMask == 0x0)
    {
        // Get the command from the command input field.
        std::string command = _input->getLabel();
        _input->clear();

        // Add command to history and set the current history index to the 
        // end of the list.
        _commandHistory.push_back(command);
        if (_commandHistory.size() > 50)
            _commandHistory.pop_back();
        _commandHistoryIndex = _commandHistory.size();

        // Call all callbacks and get their output.
        std::string output;
        for (unsigned int i = 0; i < _executeCallbacks.size(); ++i)
        {
            output.append( (*_executeCallbacks[i])(command) );
            if (i + 1 < _executeCallbacks.size())
                output.append("\n");
        }

        _history->setLabel(_history->getLabel() + "> " + command + "\n" + output);

        return true;
    }
    else if (ev.key == osgGA::GUIEventAdapter::KEY_Up && ev.keyMask == 0x0)
    {
        if (_commandHistoryIndex > 0)
            --_commandHistoryIndex;

        if (_commandHistory.size() > 0)
        {
            _input->clear();
            _input->setCommand(_commandHistory[_commandHistoryIndex]);
        }

        return true;
    }
    else if (ev.key == osgGA::GUIEventAdapter::KEY_Down && ev.keyMask == 0x0)
    {
        if (_commandHistoryIndex < _commandHistory.size())
            ++_commandHistoryIndex;

        // When pressing down, when we get to the end of the command history, 
        // the command should be empty (as it was before we started to press 
        // up). So in both cases we clear the command input field.
        _input->clear();

        if (_commandHistoryIndex < _commandHistory.size())
        {
            _input->setCommand(_commandHistory[_commandHistoryIndex]);
        }

        return true;
    }

    return false;
}


Console::Impl::ConsoleEventHandler::ConsoleEventHandler(Console::Impl* impl, osgViewer::View* view)
    : _impl(impl)
    , _windowManager(new osgWidget::WindowManager(view, 1024.0, 768.0, MASK_2D/*, osgWidget::WindowManager::WM_PICK_DEBUG*/))
    , _prevFrameNumber(0)
{
    _windowManager->addChild(_impl);

    osg::Camera* camera = _windowManager->createParentOrthoCamera();
    camera->setProjectionResizePolicy(osg::Camera::FIXED);
    _windowManager->resizeAllWindows();

    view->getCamera()->addChild(camera);
    // Add myself first else the osgWidget KeyboardHandler gobbles all my 
    // keyboard events...
    osgViewer::View::EventHandlers& eventHandlers = view->getEventHandlers();
    osgViewer::View::EventHandlers::iterator it = eventHandlers.begin();
    it = eventHandlers.insert(it, this);
    it = eventHandlers.insert(++it, new osgWidget::MouseHandler(_windowManager));
    it = eventHandlers.insert(++it, new osgWidget::KeyboardHandler(_windowManager));
    it = eventHandlers.insert(++it, new osgWidget::ResizeHandler(_windowManager, camera));
    it = eventHandlers.insert(++it, new osgWidget::CameraSwitchHandler(_windowManager, camera));

    // Set initial focus correctly.
    if (_impl->isVisible())
    {
        _windowManager->setFocused(_impl);
    }
    else
    {
        _windowManager->setFocused(0);
    }
}

bool Console::Impl::ConsoleEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor* nv)
{
    if (ea.getHandled()) return false;
    osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);

    switch(ea.getEventType())
    {
        case osgGA::GUIEventAdapter::FRAME:
            if (view->getFrameStamp() != NULL)
            {
                const osg::FrameStamp* frameStamp = view->getFrameStamp();
                if (_prevFrameNumber < frameStamp->getFrameNumber())
                {
                    _impl->update(frameStamp->getSimulationTime());
                    _prevFrameNumber = frameStamp->getFrameNumber();
                }
            }
            return true;

        // Just so osgWidget's KeyboardHandler doesn't get that key.
        case osgGA::GUIEventAdapter::KEYDOWN:
            if (ea.getKey() == '`')
            {
                return true;
            }
            return false;

        case osgGA::GUIEventAdapter::KEYUP:
            if (ea.getKey() == '`')
            {
                _impl->setVisible(!_impl->isVisible());

                if (_impl->isVisible())
                {
                    _windowManager->setFocused(_impl);
                }
                else
                {
                    _windowManager->setFocused(0);
                }
                return true;
            }
            return false;

        case osgGA::GUIEventAdapter::RESIZE:
            _impl->resize(ea.getWindowWidth(), ea.getWindowHeight());
            return true;

        default:
            return false;
    }
    return false;
}


Console::Console(osgViewer::View* view)
    : _impl(new Impl(view))
{
}

Console::~Console()
{
    _impl->deleteThis();
}

void Console::setVisible(bool visible)
{
    _impl->setVisible(visible);
}

bool Console::isVisible() const
{
    return _impl->isVisible();
}

void Console::setHeight(double heightPercent)
{
    _impl->setHeight(heightPercent);
}

double Console::getHeight() const
{
    return _impl->getHeight();
}

void Console::setTransitionTime(double time)
{
    _impl->setTransitionTime(time);
}

double Console::getTransitionTime() const
{
    return _impl->getTransitionTime();
}

void Console::setColor(const osg::Vec4& color)
{
    _impl->setColor(color);
}

osg::Vec4 Console::getColor() const
{
    return _impl->getColor();
}

void Console::addExecuteCallback(ExecuteCallback* callback)
{
    _impl->addExecuteCallback(callback);
}

void Console::removeExecuteCallback(ExecuteCallback* callback)
{
    _impl->removeExecuteCallback(callback);
}

const Console::ExecuteCallbacks& Console::getExecuteCallbacks() const
{
    return _impl->getExecuteCallbacks();
}
