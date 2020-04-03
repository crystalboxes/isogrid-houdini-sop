#include "iso_applet.h"
#include "iso_system.h"

void PIsoApplet::setup()
{
  fullScreen(P3D);
  smooth(8);
  noCursor();
  I = K = J = initialResolution;
  mini = 0;
  minj = 0;
  mink = 0;
  maxi = I;
  maxj = J;
  maxk = K;
  offset = 0;
  scale = 3.0;
  seed = (int)random(1000000);
  noiseSeed(seed);
  randomSeed(seed);

  createColors();
  iso = new IsoSystem(scale, I, J, K, 0, 0, colors, seed, this);
  creation = std::to_string(iso->seed) + "-" + std::to_string(I) + "/" + std::to_string(J) + "/" + std::to_string(K);
  operators = "\n";
  maxIJK = std::max(std::max(I, J), K);
  GUI = true;
}

void PIsoApplet::draw()
{
  if (saveFrame)
  {
    if (savePDF)
    {
      println("Begin record PDF");
      beginRecord("", "saves/" + name + "/vector.pdf");
    }
    else if (saveSVG)
    {
      println("Begin record SVG");
      beginRecord("", "saves/" + name + "/vector.svg");
    }
    else
    {
      save("saves/" + name + "/screenshot.png");
      PrintWriter pw = createWriter("saves/" + name + "/parameters.txt");
      pw.println(std::to_string(iso->seed) + "-" + std::to_string(I) + "/" + std::to_string(J) + "/" +
                 std::to_string(K) + operators);
      pw.flush();
      pw.close();
    }
    stroke = 0.25;
    translate(width / 2 + tw, height / 2 + th);
    rotate(radians((float)angle));
    scale_(1.0, -1.0);
    background(255);
    noFill();
    strokeWeight(2 * stroke);
    stroke_(0);
    iso->drawEdges();
    if (saveFrame == true)
    {
      if (!savePDF && !saveSVG)
      {
        savePDF = true;
      }
      else if (!saveSVG)
      {
        println("End record PDF");
        endRecord();
        savePDF = false;
        saveSVG = true;
      }
      else
      {
        println("End record SVG");
        endRecord();
        saveFrame = false;
        saveSVG = false;
        save("saves/" + name + "/" + name + ".png");
      }
    }
  }
  else
  {
    ortho();
    background(15);

    pushMatrix();
    translate(width / 2 + tw, height / 2 + th);
    rotate(radians((float)angle));
    scale_(1.0, -1.0);
    noStroke();

    iso->drawFaces(-2 * maxIJK, 2 * maxIJK);
    strokeWeight(1);
    stroke_(0);
    iso->drawEdges();
    popMatrix();
    if (GUI)
    {
      makeGUI();
    }
  }
}

void PIsoApplet::makeGUI()
{
  fill(240);
  int x = 10;
  int y = 0;
  int dy = 16;
  text("iso 190728", x, y += dy);
  text("", x, y += dy);
  text("spacebar: save", x, y += dy);
  text("'n': reset, same noise seed", x, y += dy);
  text("'N': reset, new noise seed", x, y += dy);
  text("", x, y += dy);
  text("'q': rotate CW", x, y += dy);
  text("'e': rotate CCW", x, y += dy);
  text("'w': shift up", x, y += dy);
  text("'s': shift down", x, y += dy);
  text("'a': shift left", x, y += dy);
  text("'d': shift right", x, y += dy);
  text("", x, y += dy);
  text("'f': toggle shading", x, y += dy);
  text("'z': darken", x, y += dy);
  text("'c': lighten", x, y += dy);
  text("'g': toggle GUI", x, y += dy);
  text("'j': toggle dual render", x, y += dy);
  text("", x, y += dy);
  text("'1'-'7': random remove blocks of size 128-64-...-2", x, y += dy);
  text("'8': random remove blocks", x, y += dy);
  text("'9': maze", x, y += dy);
  text("'0': perlin noise", x, y += dy);
  text("'/': perlin color noise", x, y += dy);
  text("'?': perlin noise", x, y += dy);

  text("'x': invert", x, y += dy);

  text("", x, y += dy);
  text("'R': edge transform", x, y += dy);
  text("'r': random selection edge transform", x, y += dy);
  text("'T': wire transform", x, y += dy);
  text("'t': random selection wire transform", x, y += dy);
  text("'H': hollow", x, y += dy);
  text("'h': random selection hollow", x, y += dy);

  text("", x, y += dy);
  text("'m': slice I direction", x, y += dy);
  text("'M': random selection slice I direction", x, y += dy);
  text("'<': slice J direction", x, y += dy);
  text("',': random selection slice J direction", x, y += dy);
  text("'>': slice K direction", x, y += dy);
  text("'.': random selection slice K direction", x, y += dy);
  text("", x, y += dy);
  text("'k' : 90° rotate I axis", x, y += dy);
  text("'l' : 90° rotate J axis", x, y += dy);
  text("';' : 90° rotate K axis", x, y += dy);
  text("", x, y += dy);
  text("'y': flip", x, y += dy);
  text("'u': mirror I plane", x, y += dy);
  text("'i': mirror J plane", x, y += dy);
  text("'o': mirror K plane", x, y += dy);
  text("'p': mirror IK plane", x, y += dy);
}

#include <algorithm>
#include <array>

void PIsoApplet::createColors()
{
  colors.resize(20);

  float hsqrt2 = (float)(sqrt(2.0) * 0.5);
  float hsqrt3 = (float)(sqrt(3.0) * 0.5);

  std::array<std::array<float, 3>, 10> normals;

  normals[0] = { 1, 0, 0 };
  normals[1] = { 0, 1, 0 };
  normals[2] = { 0, 0, 1 };
  normals[3] = { hsqrt2, hsqrt2, 0 };
  normals[4] = { hsqrt2, 0, hsqrt2 };
  normals[5] = { 0, hsqrt2, hsqrt2 };
  normals[6] = { hsqrt3, hsqrt3, hsqrt3 };
  normals[7] = { -hsqrt3, hsqrt3, hsqrt3 };
  normals[8] = { hsqrt3, -hsqrt3, hsqrt3 };
  normals[9] = { hsqrt3, hsqrt3, -hsqrt3 };

  vec<vec<float>> light = { { 1, 0, 0, 255, 255, 0 }, { 0, 1, 0, 0, 255, 255 }, { 0, 0, 1, 255, 0, 255 } };

  for (int i = 0; i < 10; i++)
  {
    float red, green, blue, dot;
    red = green = blue = 0;
    for (int l = 0; l < 3; l++)
    {
      dot = ((i > 6) ? 1.0 : 1.0) *
            std::max(0.f, normals[i][0] * light[l][0] + normals[i][1] * light[l][1] + normals[i][2] * light[l][2]);
      red += dot * light[l][3];
      green += dot * light[l][4];
      blue += dot * light[l][5];
    }

    float max = std::max(std::max(red, green), blue);
    if (max > 400.0)
    {
      red *= 400.0 / max;
      green *= 400.0 / max;
      blue *= 400.0 / max;
    }
    colors[i] = makeColor(constrain(red, 0, 255), constrain(green, 0, 255), constrain(blue, 0, 255));
  }

  light = { { 1, 0, 0, 255, 255, 255 }, { 0, 1, 0, 80, 80, 80 }, { 0, 0, 1, 0, 0, 0 } };

  for (int i = 0; i < 10; i++)
  {
    float red, green, blue, dot;
    red = green = blue = 0;
    for (int l = 0; l < 3; l++)
    {
      dot = std::max(0.f, normals[i][0] * light[l][0] + normals[i][1] * light[l][1] + normals[i][2] * light[l][2]);
      red += dot * light[l][3];
      green += dot * light[l][4];
      blue += dot * light[l][5];
    }

    float max = std::max(std::max(red, green), blue);
    if (max > 400.0)
    {
      red *= 400.0 / max;
      green *= 400.0 / max;
      blue *= 400.0 / max;
    }
    colors[i + 10] = makeColor(constrain(red, 0, 255), constrain(green, 0, 255), constrain(blue, 0, 255));
  }
}

void PIsoApplet::keyPressed()
{
  if (key == 'z')
  {
    offset++;
  }
  else if (key == 'c')
  {
    offset--;
  }
  else if (key == 'q')
  {
    angle = (angle + 30) % 360;
  }
  else if (key == 'e')
  {
    angle = ((angle - 30) % 360 + 360) % 360;
  }
  else if (key == 'a')
  {
    tw -= 10;
  }
  else if (key == 'd')
  {
    tw += 10;
  }
  else if (key == 'w')
  {
    th -= 10;
  }
  else if (key == 's')
  {
    th += 10;
  }
  else if (key == 'x')
  {
    iso->invert();
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "invert\n";
  }
  else if (key == '+')
  {
    scale *= 1.1f;
    iso->grid->setSize(scale, scale);
  }
  else if (key == '-')
  {
    scale *= 0.9f;
    iso->grid->setSize(scale, scale);
  }
  else if (key == '1')
  {
    iso->subdivideRandomGrid(128, 25.f, 50.0f, 0.0f);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "subdivide 128/25/50/0\n";
  }
  else if (key == '2')
  {
    iso->subdivideRandomGrid(64, 25.f, 50.0f, 0.0f);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "subdivide 64/25/50/0\n";
  }
  else if (key == '3')
  {
    iso->subdivideRandomGrid(32, 25.f, 50.0f, 0.0f);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "subdivide 32/25/50/0\n";
  }
  else if (key == '4')
  {
    iso->subdivideRandomGrid(16, 25.f, 50.0f, 0.0f);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "subdivide 16/25/50/0\n";
  }
  else if (key == '5')
  {
    iso->subdivideRandomGrid(8, 25.f, 50.0f, 0.0f);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "subdivide 8/25/50/0\n";
  }
  else if (key == '6')
  {
    iso->subdivideRandomGrid(4, 25.f, 35.0f, -40.0f);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "subdivide 4/25/50/0\n";
  }
  else if (key == '7')
  {
    iso->subdivideRandomGrid(2, 25.0f, 50.0f, 0.0f);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "subdivide 2/25/50/0\n";
  }
  else if (key == '8')
  {
    iso->subdivideGrid();
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "subdivide 64-32-16-8-4/50-40-30-20-1/50-50-50-50-20/0\n";
  }
  else if (key == '9')
  {
    maze(8, 16, 16, 16);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "maze 8/16/16/16\n";
  }
  else if (key == '0')
  {
    iso->noise(1, 1, 1, 0.04, 0.04, 0.04f, 0.60f);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "noise 1/1/1/0.04/0.04/0.04/0.6\n";
  }
  else if (key == 'r')
  {
    iso->edgeGrid(32, 50);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "edge 32/50\n";
  }
  else if (key == 'R')
  {
    iso->edgeGrid(maxIJK, 101);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "edge ALL\n";
  }
  else if (key == 't')
  {
    iso->wireGrid(32, 25.0f);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "wire 32/25\n";
  }
  else if (key == 'T')
  {
    iso->wireGrid(maxIJK, 101);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "wire ALL\n";
  }
  else if (key == 'y')
  {
    iso->flip();
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "flip\n";
  }
  else if (key == 'u')
  {
    iso->mirrorI();
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "mirror I\n";
  }
  else if (key == 'i')
  {
    iso->mirrorJ();
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "mirror J\n";
  }
  else if (key == 'o')
  {
    iso->mirrorK();
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "mirror K\n";
  }
  else if (key == 'p')
  {
    iso->mirrorIK();
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "mirror IK\n";
  }
  else if (key == 'f')
  {
    FADE = !FADE;
  }
  else if (key == 'g')
  {
    GUI = !GUI;
  }
  else if (key == 'h')
  {
    iso->hollowGrid(32, 25);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "hollow 32/25\n";
  }
  else if (key == 'H')
  {
    iso->hollowGrid(maxIJK, 100);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "hollow ALL\n";
  }
  else if (key == 'j')
  {
    DUAL = !DUAL;
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "dual\n";
  }
  else if (key == 'k')
  {
    iso->rotateI();
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "rotate I\n";
  }
  else if (key == 'l')
  {
    iso->rotateJ();
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "rotate J\n";
  }
  else if (key == ';')
  {
    iso->rotateK();
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "rotate K\n";
  }
  else if (key == 'n')
  {
    noiseSeed(seed);
    randomSeed(seed);
    iso = new IsoSystem(scale, I, J, K, 0, 0, colors, seed, this);
    creation = std::to_string(iso->seed) + "-" + std::to_string(I) + "/" + std::to_string(J) + "/" + std::to_string(K);
    operators = '\n';
  }
  else if (key == 'N')
  {
    seed = (int)random(1000000);
    noiseSeed(seed);
    randomSeed(seed);
    iso = new IsoSystem(scale, I, J, K, 0, 0, colors, seed, this);
    creation = std::to_string(iso->seed) + "-" + std::to_string(I) + "/" + std::to_string(J) + "/" + std::to_string(K);
    operators = '\n';
  }
  else if (key == 'm')
  {
    iso->sliceIGrid(72, 25);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "slice I 72/25\n";
  }
  else if (key == 'M')
  {
    iso->sliceIGrid(maxIJK, 100);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "slice I ALL\n";
  }
  else if (key == ',')
  {
    iso->sliceJGrid(32, 25);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "slice J 32/25\n";
  }
  else if (key == '<')
  {
    iso->sliceJGrid(maxIJK, 100);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "slice J ALL\n";
  }
  else if (key == '.')
  {
    iso->sliceKGrid(72, 25);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "slice K 72/25\n";
  }
  else if (key == '>')
  {
    iso->sliceKGrid(maxIJK, 100);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "slice K ALL\n";
  }
  else if (key == '/')
  {
    iso->colorNoise(4, 4, 4, 0.06, 0.06, 0.06, 0.45);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "colorNoise 4/4/4/0.06/0.06/0.6/0.45\n";
  }
  else if (key == '?')
  {
    iso->colorGrid(16, 0.35);
    iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
    operators += "colorNoise 16/0.35\n";
  }
  else if (key == ' ')
  {
  }

  println(creation + operators);
}

#include <unordered_set>
template <typename T>
class LinkedHashSet
{
  public:
  void add(T value)
  {
    map.insert(value);
  }

  void remove(T value)
  {
    map.erase(value);
  }
  bool contains(T value)
  {
    return map.find(value) != map.end();
  }
  int size()
  {
    return (int)map.size();
  }
  std::unordered_set<T> map;
};

struct Cell
{
  int layer, row, column;
  Cell *N;
  Cell *S;
  Cell *E;
  Cell *W;
  Cell *U;
  Cell *D;
  LinkedHashSet<Cell *> links;
  boolean visited;
  int label;
  Cell(int layer, int row, int column)
  {
    this->layer = layer;
    this->row = row;
    this->column = column;
    links = LinkedHashSet<Cell *>();
    visited = false;
  }

  void link(Cell *cell, boolean bidirectional)
  {
    links.add(cell);
    if (bidirectional)
      cell->link(this, false);
  }

  void unlink(Cell *cell, boolean bidirectional)
  {
    links.remove(cell);
    if (bidirectional)
      cell->unlink(this, false);
  }

  void link(Cell *cell)
  {
    link(cell, true);
  }

  void unlink(Cell *cell)
  {
    unlink(cell, true);
  }

  boolean isLinked(Cell *cell)
  {
    return links.contains(cell);
  }

  LinkedHashSet<Cell *> getLinks()
  {
    return links;
  }

  void getNeighbors(vec<Cell *> &neighbors)
  {
    neighbors.clear();
    if (U != nullptr)
      neighbors.push_back(U);
    if (D != nullptr)
      neighbors.push_back(D);
    if (N != nullptr)
      neighbors.push_back(N);
    if (S != nullptr)
      neighbors.push_back(S);
    if (E != nullptr)
      neighbors.push_back(E);
    if (W != nullptr)
      neighbors.push_back(W);
  }
};

struct Maze
{
  int layers, rows, columns, unvisited;
  vec<vec<vec<Cell *>>> cells;
  Maze(int layers, int rows, int columns)
  {
    this->layers = layers;
    this->rows = rows;
    this->columns = columns;
    initGrid();
    configureCells();
    AldousBroder();
  }

  void initGrid()
  {
    cells.resize(layers);
    // cells = new Cell[layers][rows][columns];
    for (int l = 0; l < layers; l++)
    {
      cells[l].resize(rows);
      for (int r = 0; r < rows; r++)
      {
        cells[l][r].resize(columns);
        for (int c = 0; c < columns; c++)
        {
          cells[l][r][c] = new Cell(l, r, c);
        }
      }
    }
  }

  void configureCells()
  {
    unvisited = layers * rows * columns;
    for (int l = 0; l < layers; l++)
    {
      for (int r = 0; r < rows; r++)
      {
        for (int c = 0; c < columns; c++)
        {
          cells[l][r][c]->N = getCell(l, r - 1, c);
          cells[l][r][c]->S = getCell(l, r + 1, c);
          cells[l][r][c]->W = getCell(l, r, c - 1);
          cells[l][r][c]->E = getCell(l, r, c + 1);
          cells[l][r][c]->U = getCell(l + 1, r, c);
          cells[l][r][c]->D = getCell(l - 1, r, c);
        }
      }
    }
    for (int l = layers / 3; l < 2 * layers / 3; l++)
    {
      for (int r = rows / 3; r < 2 * rows / 3; r++)
      {
        for (int c = columns / 3; c < 2 * columns / 3; c++)
        {
          cells[l][r][c]->visited = true;
          unvisited--;
        }
      }
    }
  }

  Cell *getCell(int layer, int row, int column)
  {
    if (layer >= 0 && layer < layers && row >= 0 && row < rows && column >= 0 & column < columns)
    {
      return cells[layer][row][column];
    }
    return nullptr;
  }

  Cell *getRandomCell()
  {
    return getCell((int)random((float)layers), (int)random((float)rows), (int)random((float)columns));
  }

  void AldousBroder()
  {
    Cell *cell = getRandomCell();
    if (cell->visited)
    {
    }
    else
    {
      cell->visited = true;
      unvisited--;
    }
    cell->label = 0;
    Cell *neighbor;

    vec<Cell *> neighbors; // = new ArrayList<Cell>();
    while (unvisited > 0)
    {
      cell->getNeighbors(neighbors);
      auto idx = (int)random(neighbors.size());
      if (idx == neighbors.size())
      {
        idx -= 1;
      }
      neighbor = neighbors[idx];
      if (!neighbor->visited)
      {
        cell->link(neighbor);
        neighbor->visited = true;

        unvisited--;
      }
      cell = neighbor;
    }
  }

  boolean isLinked(int l1, int r1, int c1, int l2, int r2, int c2)
  {
    Cell *cell1 = getCell(l1, r1, c1);
    Cell *cell2 = getCell(l2, r2, c2);
    return cell1 != nullptr && cell2 != nullptr && cell1->isLinked(cell2);
  }
};

boolean isCenterx(int x, int v)
{
  return (x % 2 == 0) ? (v % x) == x / 2 - 1 || (v % x) == x / 2 : (v % x) == x / 2;
}
boolean isUpx(int x, int v)
{
  return (v % x) > x / 2;
}

boolean isDownx(int x, int v)
{
  return (x % 2 == 0) ? (v % x) < x / 2 - 1 : (v % x) < x / 2;
}

void PIsoApplet::maze(int x, int MI, int MJ, int MK)
{
  I = x * MI;
  J = x * MJ;
  K = x * MK;
  mini = 0;
  minj = 0;
  mink = 0;
  maxi = I;
  maxj = J;
  maxk = K;
  maxIJK = std::max(std::max(I, J), K);
  vec<boolean> voxels(I * J * K);
  Maze maze(MI, MJ, MK);
  int id = 0;
  for (int i = 0; i < I; i++)
  {
    for (int j = 0; j < J; j++)
    {
      for (int k = 0; k < K; k++)
      {

        if (isCenterx(x, i) && isCenterx(x, j) && isCenterx(x, k) &&
            maze.getCell(i / x, j / x, k / x)->links.size() > 0)
        {
          voxels[id] = true;
        }
        else if (isDownx(x, i) && isCenterx(x, j) && isCenterx(x, k))
        {
          voxels[id] = maze.isLinked(i / x - 1, j / x, k / x, i / x, j / x, k / x);
        }
        else if (isUpx(x, i) && isCenterx(x, j) && isCenterx(x, k))
        {
          voxels[id] = maze.isLinked(i / x, j / x, k / x, i / x + 1, j / x, k / x);
        }
        else if (isDownx(x, j) && isCenterx(x, i) && isCenterx(x, k))
        {
          voxels[id] = maze.isLinked(i / x, j / x - 1, k / x, i / x, j / x, k / x);
        }
        else if (isUpx(x, j) && isCenterx(x, i) && isCenterx(x, k))
        {
          voxels[id] = maze.isLinked(i / x, j / x, k / x, i / x, j / x + 1, k / x);
        }
        else if (isDownx(x, k) && isCenterx(x, i) && isCenterx(x, j))
        {
          voxels[id] = maze.isLinked(i / x, j / x, k / x - 1, i / x, j / x, k / x);
        }
        else if (isUpx(x, k) && isCenterx(x, i) && isCenterx(x, j))
        {
          voxels[id] = maze.isLinked(i / x, j / x, k / x, i / x, j / x, k / x + 1);
        }
        id++;
      }
    }
  }
  iso = new IsoSystem(scale, I, J, K, 0.0, 0.0, colors, seed, voxels, this);
  iso->mapVoxelsToHexGrid(DUAL, mini, maxi, minj, maxj, mink, maxk);
}
