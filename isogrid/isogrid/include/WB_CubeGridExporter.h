#pragma once

#include <functional>
#include <string>
#include <vector>

class WB_CubeGridExporter
{
  public:
  static void export(const std::string &path, double cx, double cy, double cz, int I, int J, int K, double dx,
                     double dy, double dz, const std::vector<bool> &values, int li, int ui, int lj, int uj, int lk,
                     int uk);

  static void getMesh(std::function<void(float, float, float)> addVertexCallback,
                      std::function<void(int, int, int, int)> addFaceCallback, double cx, double cy, double cz, int I,
                      int J, int K, double dx, double dy, double dz, const std::vector<bool> &values, int li, int ui,
                      int lj, int uj, int lk, int uk);

  private:
  WB_CubeGridExporter()
  {
  }
};
