#pragma once

class State;

class Context
{
private:
  State *state_;

public:
  Context(State *state);
  
  void transition_to(State *state);

  void do_work();

  void reset();

  void on_operate();

};