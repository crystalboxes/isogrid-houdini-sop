#include "isogrid.h"
#include "iso_applet.h"
#include "iso_system.h"

IsoGridInstance::IsoGridInstance()
{
  allocate();
}

void IsoGridInstance::setInitResolution(int res)
{
  initialResolution = res;
}

const char *IsoGridInstance::getConsoleOutput()
{
  if (applet)
  {
    return applet->std_out.c_str();
  }
  return "";
}

void IsoGridInstance::allocate()
{
  if (applet != nullptr)
  {
    delete applet;
  }
  applet = new PIsoApplet();
  applet->outputToConsole = false;
  applet->initialResolution = initialResolution;
}

void IsoGridInstance::init()
{
  allocate();
  applet->std_out.clear();
  applet->setup();
  applet->draw();
}

void IsoGridInstance::doOperation(char key)
{
  applet->key = key;
  applet->keyPressed();
  applet->draw();
}

void IsoGridInstance::executeCommands(const std::string &commands)
{
  init();
  for (auto &ch : commands)
  {
    doOperation(ch);
  }
}

void IsoGridInstance::executeCommands(const std::vector<Commands> &commands)
{

  init();
  for (auto &ch : commands)
  {
    doOperation((char)ch);
  }
}

#include "WB_CubeGridExporter.h"

void IsoGridInstance::getMesh(std::function<void(float, float, float)> addVertexCallback,
                              std::function<void(int, int, int, int)> addFaceCallback)
{
  WB_CubeGridExporter::getMesh(addVertexCallback, addFaceCallback, 0, 0, 0, applet->I, applet->J, applet->K,
                               applet->scale, applet->scale, applet->scale, applet->iso->voxels, 0, applet->I, 0,
                               applet->J, 0, applet->K);
}

IsoGridInstance::~IsoGridInstance()
{
  if (applet)
  {
    delete applet;
  }
}