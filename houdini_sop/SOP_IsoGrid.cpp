#include "SOP_IsoGrid.h"

#include <CH/CH_LocalVariable.h>
#include <GEO/GEO_PrimPoly.h>
#include <GU/GU_Detail.h>
#include <OP/OP_AutoLockInputs.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <SYS/SYS_Math.h>
#include <UT/UT_DSOVersion.h>
#include <UT/UT_Interrupt.h>
#include <isogrid.h>
#include <limits.h>

namespace isogrid_sop
{
#define ADD_CALLBACK(NAME)                                                  \
  int callback_##NAME(void *data, int index, float t, const PRM_Template *) \
  {                                                                         \
    auto isogrid = (SOP_IsoGrid *)data;                                     \
    isogrid->addCommand((char)Commands::NAME, t);                           \
    return 0;                                                               \
  }
#define ADD_PRM_CALLBACK(ID, NAME) PRM_Template(PRM_CALLBACK, 1, &names[ID], 0, 0, 0, isogrid_sop::callback_##NAME)
#define ADD_PRM_CALLBACK_JOIN(ID, NAME) \
  PRM_Template((PRM_Type)(PRM_CALLBACK | PRM_TYPE_JOIN_NEXT), 1, &names[ID], 0, 0, 0, isogrid_sop::callback_##NAME)

const char *CommandParmName = "Command";
PRM_Name clearName = "Clear";
PRM_Name consoleOutName = "ConsoleOut";

ADD_CALLBACK(Maze);
ADD_CALLBACK(PerlinNoise);
ADD_CALLBACK(PerlinNoise2);

ADD_CALLBACK(RemoveBlock1);
ADD_CALLBACK(RemoveBlock2);
ADD_CALLBACK(RemoveBlock3);
ADD_CALLBACK(RemoveBlock4);
ADD_CALLBACK(RemoveBlock5);
ADD_CALLBACK(RemoveBlock6);
ADD_CALLBACK(RemoveBlock7);
ADD_CALLBACK(RemoveBlocksRandom);
ADD_CALLBACK(Invert);
ADD_CALLBACK(EdgeTransform);
ADD_CALLBACK(RandomSelectionEdgeTransform);
ADD_CALLBACK(WireTransform);
ADD_CALLBACK(RandomSelectionWireTransform);
ADD_CALLBACK(Hollow);
ADD_CALLBACK(RandomSelectionHollow);
ADD_CALLBACK(SliceIDirection);
ADD_CALLBACK(RandomSelectionSliceIDirection);
ADD_CALLBACK(SliceJDirection);
ADD_CALLBACK(RandomSelectionSliceJDirection);
ADD_CALLBACK(SliceKDirection);
ADD_CALLBACK(RandomSelectionSliceKDirection);
ADD_CALLBACK(RotateIAxis);
ADD_CALLBACK(RotateJAxis);
ADD_CALLBACK(RotateKAxis);
ADD_CALLBACK(Flip);
ADD_CALLBACK(MirrorIPlane);
ADD_CALLBACK(MirrorJPlane);
ADD_CALLBACK(MirrorLPlane);
ADD_CALLBACK(MirrorIKPlane);

ADD_CALLBACK(ResetSameNoiseSeed);
ADD_CALLBACK(ResetNewNoiseSeed);

OP_Node *ctor(OP_Network *net, const char *name, OP_Operator *op)
{
  return new SOP_IsoGrid(net, name, op);
}

int clear_commands(void *data, int index, float t, const PRM_Template *)
{
  auto isogrid = (SOP_IsoGrid *)data;
  isogrid->setString(UT_String(), CH_StringMeaning::CH_STRING_LITERAL, isogrid_sop::CommandParmName, 0, t);
  return 0;
}

PRM_Name names[] = { CommandParmName,
                     PRM_Name("Maze", "Maze"),
                     PRM_Name("PerlinNoise", "Perlin Noise"),
                     PRM_Name("PerlinNoise2", "Perlin Noise 2"),

                     PRM_Name("RemoveBlock1", "Remove Block 1"),
                     PRM_Name("RemoveBlock2", "Remove Block 2"),
                     PRM_Name("RemoveBlock3", "Remove Block 3"),
                     PRM_Name("RemoveBlock4", "Remove Block 4"),
                     PRM_Name("RemoveBlock5", "Remove Block 5"),
                     PRM_Name("RemoveBlock6", "Remove Block 6"),
                     PRM_Name("RemoveBlock7", "Remove Block 7"),
                     PRM_Name("RemoveBlocksRandom", "Remove Blocks Random"),
                     PRM_Name("Invert", "Invert"),
                     PRM_Name("EdgeTransform", "Edge Transform"),
                     PRM_Name("RandomSelectionEdgeTransform", "Random Selection Edge Transform"),
                     PRM_Name("WireTransform", "Wire Transform"),
                     PRM_Name("RandomSelectionWireTransform", "Random Selection Wire Transform"),
                     PRM_Name("Hollow", "Hollow"),
                     PRM_Name("RandomSelectionHollow", "Random Selection Hollow"),
                     PRM_Name("SliceIDirection", "Slice I Direction"),
                     PRM_Name("RandomSelectionSliceIDirection", "Random Selection Slice I Direction"),
                     PRM_Name("SliceJDirection", "Slice J Direction"),
                     PRM_Name("RandomSelectionSliceJDirection", "Random Selection Slice J Direction"),
                     PRM_Name("SliceKDirection", "Slice K Direction"),
                     PRM_Name("RandomSelectionSliceKDirection", "Random Selection Slice K Direction"),
                     PRM_Name("RotateIAxis", "Rotate I Axis"),
                     PRM_Name("RotateJAxis", "Rotate J Axis"),
                     PRM_Name("RotateKAxis", "Rotate K Axis"),
                     PRM_Name("Flip", "Flip"),
                     PRM_Name("MirrorIPlane", "Mirror I Plane"),
                     PRM_Name("MirrorJPlane", "Mirror J Plane"),
                     PRM_Name("MirrorLPlane", "Mirror L Plane"),
                     PRM_Name("MirrorIKPlane", "Mirror IK Plane"),
                     PRM_Name("ResetSameNoiseSeed", "Reset Same NoiseSeed"),
                     PRM_Name("ResetNewNoiseSeed", "Reset New NoiseSeed") };
PRM_Template templates[] = {
  PRM_Template(PRM_STRING, 1, &names[0]), //
  // ADD_PRM_CALLBACK_JOIN(33, ResetSameNoiseSeed), //
  ADD_PRM_CALLBACK(34, ResetNewNoiseSeed), //
  ADD_PRM_CALLBACK_JOIN(1, Maze), //
  ADD_PRM_CALLBACK(2, PerlinNoise), //
  // ADD_PRM_CALLBACK(3, PerlinNoise2), //
  // PRM_Template(PRM_SEPARATOR), //
  ADD_PRM_CALLBACK_JOIN(4, RemoveBlock1), //
  ADD_PRM_CALLBACK_JOIN(5, RemoveBlock2), //
  ADD_PRM_CALLBACK(6, RemoveBlock3), //

  ADD_PRM_CALLBACK_JOIN(7, RemoveBlock4), //
  ADD_PRM_CALLBACK_JOIN(8, RemoveBlock5), //
  ADD_PRM_CALLBACK(9, RemoveBlock6), //

  ADD_PRM_CALLBACK_JOIN(10, RemoveBlock7), //
  ADD_PRM_CALLBACK(11, RemoveBlocksRandom), //
  // PRM_Template(PRM_SEPARATOR), //
  ADD_PRM_CALLBACK_JOIN(12, Invert), //
  ADD_PRM_CALLBACK_JOIN(13, EdgeTransform), //
  ADD_PRM_CALLBACK(14, RandomSelectionEdgeTransform), //
  ADD_PRM_CALLBACK_JOIN(15, WireTransform), //
  ADD_PRM_CALLBACK_JOIN(16, RandomSelectionWireTransform), //
  ADD_PRM_CALLBACK_JOIN(17, Hollow), //
  ADD_PRM_CALLBACK(18, RandomSelectionHollow), //
  ADD_PRM_CALLBACK_JOIN(19, SliceIDirection), //
  ADD_PRM_CALLBACK_JOIN(20, RandomSelectionSliceIDirection), //
  ADD_PRM_CALLBACK_JOIN(21, SliceJDirection), //
  ADD_PRM_CALLBACK(22, RandomSelectionSliceJDirection), //
  ADD_PRM_CALLBACK_JOIN(23, SliceKDirection), //
  ADD_PRM_CALLBACK(24, RandomSelectionSliceKDirection), //
  // PRM_Template(PRM_SEPARATOR), //
  ADD_PRM_CALLBACK_JOIN(25, RotateIAxis), //
  ADD_PRM_CALLBACK_JOIN(26, RotateJAxis), //
  ADD_PRM_CALLBACK_JOIN(27, RotateKAxis), //
  ADD_PRM_CALLBACK(28, Flip), //
  // PRM_Template(PRM_SEPARATOR), //
  ADD_PRM_CALLBACK_JOIN(29, MirrorIPlane), //
  ADD_PRM_CALLBACK_JOIN(30, MirrorJPlane), //
  ADD_PRM_CALLBACK_JOIN(31, MirrorLPlane), //
  ADD_PRM_CALLBACK(32, MirrorIKPlane), //
  PRM_Template(PRM_SEPARATOR), //
  PRM_Template(PRM_CALLBACK, 1, &clearName, 0, 0, 0, isogrid_sop::clear_commands),
  PRM_Template(PRM_LABEL, 1, &consoleOutName), //
  PRM_Template() //
}; // namespace isogrid_sop

} // namespace isogrid_sop

void newSopOperator(OP_OperatorTable *table)
{

  table->addOperator(new OP_Operator("wb_isogrid", "isogrid", isogrid_sop::ctor, isogrid_sop::templates, 0, 0, 0,
                                     OP_FLAG_GENERATOR, 0, 1));
}

SOP_IsoGrid::~SOP_IsoGrid()
{
  if (instance)
  {
    delete instance;
    instance = nullptr;
  }
}

bool SOP_IsoGrid::updateParmsFlags()
{
  enableParm(isogrid_sop::CommandParmName, false);
  return SOP_Node::updateParmsFlags();
}

void SOP_IsoGrid::addCommand(char command, float t)
{
  // var current command
  UT_String val;
  evalString(val, isogrid_sop::CommandParmName, 0, t);
  auto std_string = val.toStdString();
  std_string += command;
  setString(UT_String(std_string), CH_StringMeaning::CH_STRING_LITERAL, isogrid_sop::CommandParmName, 0, t);
}

OP_ERROR
SOP_IsoGrid::cookMySop(OP_Context &context)
{
  OP_AutoLockInputs inputs(this);
  if (inputs.lock(context) >= UT_ERROR_ABORT)
    return error();

  gdp->clearAndDestroy();

  build(gdp, context);

  return error();
}

#define DLOG 0
#if DLOG
#include <iostream>
#endif

IsoGridInstance *allocateIsogrid()
{
  auto i = new IsoGridInstance();
  i->setInitResolution(16);
  i->init();
  return i;
}

void getNextCommands(SOP_IsoGrid *isogrid, float t, std::vector<Commands> &commands, std::string &currentCommand)
{
  auto &sop = *isogrid;
  if (sop.instance == nullptr)
  {
    sop.instance = allocateIsogrid();
  }
  auto &previous = sop.previousCommand;
  UT_String cc;
  sop.evalString(cc, isogrid_sop::CommandParmName, 0, t);
  currentCommand = cc.toStdString();

#if DLOG
  std::cout << "Previous: \n" << previous << "\n";
  std::cout << "Current: \n" << currentCommand << "\n\n";
#endif

  // There is only one char difference
  if (currentCommand.size() - 1 != previous.size())
  {
    delete sop.instance;
    sop.instance = allocateIsogrid();

    for (int x = 0; x < currentCommand.size(); x++)
    {
      commands.push_back((Commands)currentCommand[x]);
    }
    return;
  }
  commands.push_back((Commands)currentCommand[currentCommand.size() - 1]);
}

void SOP_IsoGrid::build(GU_Detail *dst, OP_Context &context)
{
  std::vector<Commands> commands;
  std::string currentCommand;

  UT_AutoInterrupt boss("Building isogrid");

  getNextCommands(this, context.getTime(), commands, currentCommand);
  auto &a = *instance;

#if DLOG
  std::cout << "Executing commands\n";
#endif

  for (auto &cmd : commands)
  {
#if DLOG
    std::cout << "    Command " << (char)cmd << "\n";
#endif
    a.doOperation((char)cmd);
  }

  if (boss.wasInterrupted(75))
  {
    return;
  }
#if DLOG
  std::cout << "Generating mesh\n";
#endif
  a.getMesh(
      [this](float x, float y, float z) {
        auto offset = gdp->appendPoint();
        gdp->setPos3(offset, UT_Vector3(x * .01f, y * .01f, z * .01f));
      },
      [this](int a, int b, int c, int d) {
        GEO_PrimPoly *prim;
        prim = (GEO_PrimPoly *)gdp->appendPrimitive(GA_PRIMPOLY);
        prim->setSize(0);
        prim->appendVertex(a - 1);
        prim->appendVertex(b - 1);
        prim->appendVertex(c - 1);
        prim->appendVertex(d - 1);
        prim->close();
      });
  setString(UT_String(a.getConsoleOutput()), //
            CH_StringMeaning::CH_STRING_LITERAL, "ConsoleOut", 0, context.getTime());

  gdp->getP()->bumpDataId();

#if DLOG
  std::cout << "Writing command\n";
#endif
  previousCommand = currentCommand;
}
