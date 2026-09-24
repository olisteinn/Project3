#pragma once

class State;

class Context
{
private:
  State *state_;

public:
  Context(State *state);
  ~Context();

  void transition_to(State *state);

  void do_work();

};