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

void IsoGridInstance::getMesh(std::function<void(float, float, float)> addVertexCallback,
                              std::function<void(int, int, int, int)> addFaceCallback)
{
  auto export_mesh = [addVertexCallback, addFaceCallback](double cx, double cy, double cz, int I, int J, int K,
                                                          double dx, double dy, double dz, vec<boolean> &values, int li,
                                                          int ui, int lj, int uj, int lk, int uk) {
    auto vertexCount = 0;
    auto index = [](int i, int j, int k, int JK, int K, int li, int ui, int lj, int uj, int lk, int uk) {
      if (i > li - 1 && j > lj - 1 && k > lk - 1 && i < ui && j < uj && k < uk)
      {
        return k + j * K + i * JK;
      }
      else
      {
        return -1;
      }
    };

    vec<vec<vec<int>>> vertexIndices;
    vec<double> c = { cx - I * 0.5f * dx, cy - J * 0.5f * dy, cz - K * 0.5f * dz };

    auto getVindex = [&vertexIndices, c, addVertexCallback, &vertexCount](int i, int j, int k, double dx, double dy,
                                                                          double dz) {
      if (vertexIndices[i][j][k] == -1)
      {
        vertexIndices[i][j][k] = (vertexCount++) + 1;
        addVertexCallback((float)(c[0] + i * dx), (float)(c[1] + j * dy), (float)(c[2] + k * dz));
      }
      return vertexIndices[i][j][k];
    };

    vertexIndices.resize(I + 1);
    for (int i = 0; i <= I; i++)
    {
      vertexIndices[i].resize(J + 1);
      for (int j = 0; j <= J; j++)
      {
        vertexIndices[i][j].resize(K + 1);
        for (int k = 0; k <= K; k++)
        {
          vertexIndices[i][j][k] = -1;
        }
      }
    }

    int val0 = 0, valm = 0, sum = 0;
    int idx = 0;
    int JK = J * K;

    for (int i = li; i <= ui; i++)
    {
      for (int j = lj; j < uj; j++)
      {
        for (int k = lk; k < uk; k++)
        {
          idx = index(i, j, k, J, JK, li, ui, lj, uj, lk, uk);
          val0 = idx == -1 ? 0 : values[idx] ? 1 : 0;
          idx = index(i - 1, j, k, J, JK, li, ui, lj, uj, lk, uk);
          valm = idx == -1 ? 0 : values[idx] ? 1 : 0;
          sum = val0 + valm;
          if (sum == 1)
          {
            addFaceCallback(getVindex(i, j, k, dx, dy, dz), getVindex(i, j + 1, k, dx, dy, dz),
                            getVindex(i, j + 1, k + 1, dx, dy, dz), getVindex(i, j, k + 1, dx, dy, dz));
          }
        }
      }
    }

    for (int i = li; i < ui; i++)
    {
      for (int j = lj; j <= uj; j++)
      {
        for (int k = lk; k < uk; k++)
        {
          idx = index(i, j, k, J, JK, li, ui, lj, uj, lk, uk);
          val0 = idx == -1 ? 0 : values[idx] ? 1 : 0;
          idx = index(i, j - 1, k, J, JK, li, ui, lj, uj, lk, uk);
          valm = idx == -1 ? 0 : values[idx] ? 1 : 0;
          sum = val0 + valm;
          if (sum == 1)
          {
            addFaceCallback(getVindex(i, j, k, dx, dy, dz), getVindex(i + 1, j, k, dx, dy, dz),
                            getVindex(i + 1, j, k + 1, dx, dy, dz), getVindex(i, j, k + 1, dx, dy, dz));
          }
        }
      }
    }

    for (int i = li; i < ui; i++)
    {
      for (int j = lj; j < uj; j++)
      {
        for (int k = lk; k <= uk; k++)
        {
          idx = index(i, j, k, J, JK, li, ui, lj, uj, lk, uk);
          val0 = idx == -1 ? 0 : values[idx] ? 1 : 0;
          idx = index(i, j, k - 1, J, JK, li, ui, lj, uj, lk, uk);
          valm = idx == -1 ? 0 : values[idx] ? 1 : 0;
          sum = val0 + valm;
          if (sum == 1)
          {
            addFaceCallback(getVindex(i, j, k, dx, dy, dz), getVindex(i + 1, j, k, dx, dy, dz),
                            getVindex(i + 1, j + 1, k, dx, dy, dz), getVindex(i, j + 1, k, dx, dy, dz));
          }
        }
      }
    }
  };

  export_mesh(0, 0, 0, applet->I, applet->J, applet->K, applet->scale, applet->scale, applet->scale,
              applet->iso->voxels, 0, applet->I, 0, applet->J, 0, applet->K);
}

IsoGridInstance::~IsoGridInstance()
{
  if (applet)
  {
    delete applet;
  }
}