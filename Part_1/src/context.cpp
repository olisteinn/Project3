#include "Context.h"
#include "State.h"

Context::Context(State *state) : state_(nullptr)
{
  this->transition_to(state);
}

void Context::transition_to(State *state)
{
  if (this->state_ != nullptr)
  {
    this->state_->on_exit();
  }

  this->state_ = state;

  this->state_->set_context(this);

  this->state_->on_entry();
}

void Context::do_work()
{
  this->state_->on_do();
}

void Context::on_init()
{
  this->state_->on_init();
}

void Context::on_operate()
{
  this->state_->on_operate();
}

