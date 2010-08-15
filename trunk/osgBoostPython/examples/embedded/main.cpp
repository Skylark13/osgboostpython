#include <iostream>
#include <string>

#include <boost/python.hpp>

using namespace boost::python;

int main( int argc, char ** argv )
{
    bool exit = false;

    while (!exit)
    {
        try
        {
            Py_Initialize();

            object main_module((
                handle<>(borrowed(PyImport_AddModule("__main__")))));

            object main_namespace = main_module.attr("__dict__");

            while (true)
            {
                std::string command;
                std::cout << "> ";
                getline(std::cin, command);
                handle<> ignored(( PyRun_String( command.c_str(),
                                                 Py_file_input,
                                                 main_namespace.ptr(),
                                                 main_namespace.ptr() ) ));
                if (command == "exit")
                {
                    exit = true;
                    break;
                }
            }
        }
        catch( error_already_set )
        {
            PyErr_Print();
        }
    }
}
