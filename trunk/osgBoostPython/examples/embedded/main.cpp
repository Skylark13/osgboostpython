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

// This code initially from http://wiki.python.org/moin/boost.python/EmbeddingPython
// with some modifications.
#include <iostream>
#include <string>

#include <boost/python.hpp>

using namespace boost::python;

int main( int argc, char ** argv )
{
    Py_Initialize();

    object main_module((
        handle<>(borrowed(PyImport_AddModule("__main__")))));

    object main_namespace = main_module.attr("__dict__");

    std::string command;
    while (true)
    {
        // Print a prompt and read the command from the user.
        std::cout << "> ";
        getline(std::cin, command);

        // Try to execute the command.
        try 
        {
            handle<> ignored(( PyRun_String( command.c_str(),
                                             Py_file_input,
                                             main_namespace.ptr(),
                                             main_namespace.ptr() ) ));

            // I just want to be a bit more lenient that the python 
            // interpreter, which nags you to type exit() or quit()
            // when it's already pretty clear you want to exit the
            // interpreter...
            if (command == "exit" || command == "quit")
            {
                break;
            }
        }
        catch( error_already_set )
        {
            PyErr_Print();
        }
    }
}
