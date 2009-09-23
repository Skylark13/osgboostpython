#!/bin/python
import osg
import osgDB
import unittest

class osgDisplaySettingsTest(unittest.TestCase):
    def test_000_testClassAvailable(self):
        s = osg.DisplaySettings()
    def test_001_testEnumsAvailable_partial(self):
        pass #No enums defined in class
    def test_002_testMethodsAvailable(self):
        #todo
        o = osg.DisplaySettings()
        o.setMinimumNumStencilBits(8)
#        o.setDisplaySettings(osg::DisplaySettings const & vs)
#        o.merge(osg::DisplaySettings const & vs)
#        o.setDefaults()
#        o.readEnvironmentalVariables()
#        o.readCommandLine(osg::ArgumentParser & arguments)
#        o.setDisplayType(osg::DisplaySettings::DisplayType type)
#        o.getDisplayType()
#        o.setStereo(bool on)
#        o.getStereo()
#        o.setStereoMode(osg::DisplaySettings::StereoMode mode)
#        o.getStereoMode()
#        o.setEyeSeparation(float eyeSeparation)
#        o.getEyeSeparation()
#        o.setSplitStereoHorizontalEyeMapping(osg::DisplaySettings::SplitStereoHorizontalEyeMapping m)
#        o.getSplitStereoHorizontalEyeMapping()
#        o.setSplitStereoHorizontalSeparation(int s)
#        o.getSplitStereoHorizontalSeparation()
#        o.setSplitStereoVerticalEyeMapping(osg::DisplaySettings::SplitStereoVerticalEyeMapping m)
#        o.getSplitStereoVerticalEyeMapping()
#        o.setSplitStereoVerticalSeparation(int s)
#        o.getSplitStereoVerticalSeparation()
#        o.setSplitStereoAutoAdjustAspectRatio(bool flag)
#        o.getSplitStereoAutoAdjustAspectRatio()
#        o.setScreenWidth(float width)
#        o.getScreenWidth()
#        o.setScreenHeight(float height)
#        o.getScreenHeight()
#        o.setScreenDistance(float distance)
#        o.getScreenDistance()
#        o.setDoubleBuffer(bool flag)
#        o.getDoubleBuffer()
#        o.setRGB(bool flag)
#        o.getRGB()
#        o.setDepthBuffer(bool flag)
#        o.getDepthBuffer()
#        o.setMinimumNumAlphaBits(unsigned int bits)
#        o.getMinimumNumAlphaBits()
#        o.getAlphaBuffer()
#        o.setMinimumNumStencilBits(unsigned int bits)
#        o.getMinimumNumStencilBits()
#        o.getStencilBuffer()
#        o.setMinimumNumAccumBits(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha)
#        o.getMinimumNumAccumRedBits()
#        o.getMinimumNumAccumGreenBits()
#        o.getMinimumNumAccumBlueBits()
#        o.getMinimumNumAccumAlphaBits()
#        o.getAccumBuffer()
#        o.setMaxNumberOfGraphicsContexts(unsigned int num)
#        o.getMaxNumberOfGraphicsContexts()
#        o.setNumMultiSamples(unsigned int samples)
#        o.getNumMultiSamples()
#        o.getMultiSamples()
#        o.setCompileContextsHint(bool useCompileContexts)
#        o.getCompileContextsHint()
#        o.setSerializeDrawDispatch(bool serializeDrawDispatch)
#        o.getSerializeDrawDispatch()
#        o.setNumOfDatabaseThreadsHint(unsigned int numThreads)
#        o.getNumOfDatabaseThreadsHint()
#        o.setNumOfHttpDatabaseThreadsHint(unsigned int numThreads)
#        o.getNumOfHttpDatabaseThreadsHint()
#        o.setApplication(std::string const & application)
#        o.getApplication()

allTests = ['test_000_testClassAvailable',
            'test_001_testEnumsAvailable_partial',
            'test_002_testMethodsAvailable', ]

# To be able to run one single test from the command line. Could be name-based instead of index-based...
if __name__ == "__main__":
    import sys
    testToRun = -1
    if (len(sys.argv) == 2):
        testToRun = int(sys.argv[1])

    if (testToRun == -1):
        unittest.main()
    else:
        tests = [allTests[testToRun]]
        suite = unittest.TestSuite(map(osgDisplaySettingsTest, tests))
        unittest.TextTestRunner(verbosity = 2).run(suite)
