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

#include <iostream>
#include <string>

#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include "PythonInterpreter.h"
#include "Console.h"

int main( int argc, char ** argv )
{
    osg::ArgumentParser arguments(&argc,argv);
    arguments.getApplicationUsage()->addCommandLineOption("--noViewer","Start in console mode, no graphical viewer.");

    osgViewer::Viewer viewer(arguments);

    unsigned int helpType = 0;
    if ((helpType = arguments.readHelpType()))
    {
        arguments.getApplicationUsage()->write(std::cout, helpType);
        return 1;
    }

    // report any errors if they have occurred when parsing the program arguments.
    if (arguments.errors())
    {
        arguments.writeErrorMessages(std::cout);
        return 1;
    }

    bool useViewer = true;
    if (arguments.read("--noViewer")) useViewer = false;

    if (useViewer)
    {
        osg::Group* root = new osg::Group;
        root->addChild(osgDB::readNodeFile("cow.osg"));

        viewer.setSceneData(root);
        viewer.addEventHandler(new osgViewer::StatsHandler);

        Console* console = new Console(&viewer);

        viewer.setUpViewInWindow(50, 50, 1024, 768);
        viewer.run();
    }
    else
    {
        PythonInterpreter interpreter;

        std::string command;
        while (true)
        {
            // Print a prompt and read the command from the user.
            std::cout << "> ";
            getline(std::cin, command);

            // Try to execute the command.
            interpreter.execute(command);

            std::cout << interpreter.getOutput();

            // I just want to be a bit more lenient that the python 
            // interpreter, which nags you to type exit() or quit()
            // when it's already pretty clear you want to exit the
            // interpreter...
            if (command == "exit" || command == "quit")
            {
                break;
            }
        }
    }
}
