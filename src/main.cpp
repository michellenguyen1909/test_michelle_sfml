#include "Program.hpp"

int main()
{
  Program program;

  while (!program.hasTerminated())
  {
    program.events();
    program.update();
    program.render();
  }

  return 0;
}