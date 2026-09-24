#pragma once
#include "State.h"

class Initialization : public State
{
public:
  void on_do() override;
  void on_entry() override;
  void on_exit() override;

  void on_init() override;
  void on_operate() override;
};

extern Initialization init_state;