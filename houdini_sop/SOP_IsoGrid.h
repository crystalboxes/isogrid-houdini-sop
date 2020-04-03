#pragma once

#include <SOP/SOP_Node.h>

#include <string>

class SOP_IsoGrid : public SOP_Node
{
  public:
  SOP_IsoGrid(OP_Network *net, const char *name, OP_Operator *op)
      : SOP_Node(net, name, op)
  {
  }

  void addCommand(char command, float t);

  struct IsoGridInstance *instance = nullptr;
  std::string previousCommand;

  protected:
  virtual ~SOP_IsoGrid();

  virtual bool updateParmsFlags() override;
  virtual OP_ERROR cookMySop(OP_Context &context);

  void build(GU_Detail *dst, OP_Context &context);
  static int resetSim(void *data, int index, float t, const PRM_Template *);
};
