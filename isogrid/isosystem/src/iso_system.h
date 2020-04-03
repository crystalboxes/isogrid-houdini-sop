#pragma once
#include "applet.h"
#include "typedef.h"
#include <array>

#include "WB_IsoHexGrid.h"

struct WB_IsoHexGrid;
struct PApplet;

struct WB_IsoGridLine;

struct IsoSystem
{
  WB_IsoHexGrid *grid;
  vec<int> colors;
  vec<boolean> voxels;
  vec<boolean> buffer;
  vec<boolean> swap;
  vec<int> colorIndices;
  vec<int> bufferci;
  vec<int> swapci;
  double L;
  int I, J, K, IJK;
  double centerX, centerY;
  PApplet *home;
  int seed;

  IsoSystem(double L, int I, int J, int K, double centerX, double centerY, vec<int> &colors, int seed, PApplet *home);

  IsoSystem(double L, int I, int J, int K, double centerX, double centerY, vec<int> &colors, int seed,
            vec<boolean> &voxels, PApplet *home);
  void clear();

  void set(int i, int j, int k, int blocki, int blockj, int blockk);

  void set(int i, int j, int k, int colorIndex, int blocki, int blockj, int blockk);
  void clear(int i, int j, int k, int blocki, int blockj, int blockk);
  void and (int i, int j, int k, int blocki, int blockj, int blockk);

  void or (int i, int j, int k, int blocki, int blockj, int blockk);

  void xor (int i, int j, int k, int blocki, int blockj, int blockk);

  void invert(int i, int j, int k, int blocki, int blockj, int blockk);

  void invert();

  void noise();

  void noise(int blocki, int blockj, int blockk, float dx, float dy, float dz, float n);

  void colorNoise(int blocki, int blockj, int blockk, float dx, float dy, float dz, float n);

  void subdivideGrid();

  void subdivideRandomGrid(int step, float divide, float retain, float jgradient);

  void createFullGrid();

  void colorGrid(int step, float chance1);

  void colorBlock(int di, int dj, int dk, int step, int col);

  void sliceIGrid(int step, float chance);

  void sliceIBlock(int di, int dj, int dk, int step);

  void sliceJGrid(int step, float chance);

  void sliceJBlock(int di, int dj, int dk, int step);
  void sliceKGrid(int step, float chance);

  void sliceKBlock(int di, int dj, int dk, int step);

  boolean sliceI(int i, int j, int k, int period, int on);
  boolean sliceJ(int i, int j, int k, int period, int on);
  boolean sliceK(int i, int j, int k, int period, int on);

  void copyFromBuffer(int di, int dj, int dk, int step);

  void edgeGrid(int step, float chance);
  void edgeBlock(int di, int dj, int dk, int step, float chance);
  void wireGrid(int step, float chance);
  void wireBlock(int di, int dj, int dk, int step, float chance);
  void IKGrid();

  void hollowGrid(int step, float chance);
  void hollowBlock(int di, int dj, int dk, int step, float chance);
  void rotateI();
  void rotateJ();

  void rotateK();

  void flip();
  void mirrorI();
  void mirrorJ();

  void mirrorK();
  void mirrorIK();
  void tri();
  void swapMe();
  void swapciMe();
  void mapVoxelsToHexGrid(boolean dual, int mini, int maxi, int minj, int maxj, int mink, int maxk);
  int state(int i, int j, int k, boolean dual);
  int index(int i, int j, int k);
  void drawEdges();
  void drawFaces(int zmin, int zmax);
};
