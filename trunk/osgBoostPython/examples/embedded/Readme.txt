This example shows how to run python embedded in a C++ app. If you set the 
PYTHONPATH to be able to find the osgBoostPython python modules, you can then
use this embedded python interpreter to run OSG code.

Eventually I want to be able to have a "console" inside an OSG app, which 
would be able to add things to the scene graph using python code and 
osgBoostPython. Thus I would have OSG within python within OSG! (kinda)
How recursively recursive! (OK I'll calm down now)