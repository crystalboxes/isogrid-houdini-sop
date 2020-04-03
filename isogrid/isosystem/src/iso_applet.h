#include "applet.h"
#include "typedef.h"

struct IsoSystem;

struct PIsoApplet : public PApplet
{
  void keyPressed();

  IsoSystem *iso;

  int initialResolution = 128;

  String name;
  String operators;
  String creation;
  boolean saveFrame = false, savePDF = false, saveSVG = false;
  PrintWriter param;
  vec<color> colors;

  int width = 640;
  int height = 480;
  char key = 0;

  float stroke = 0;
  int maxIJK = 0;
  int I = 0, J = 0, K = 0, mini = 0, maxi = 0, minj = 0, maxj = 0, mink = 0, maxk = 0;
  int offset = 0;
  float scale = 0;
  int seed = 0;

  boolean DUAL = false;
  boolean FADE = false;
  boolean GUI = false;

  int angle = 0;
  float tw = 0, th = 0;

  int min = 0, max = 0;

  void maze(int x, int MI, int MJ, int MK);
  void createColors();
  void setup();
  void draw();
  void makeGUI();
};
