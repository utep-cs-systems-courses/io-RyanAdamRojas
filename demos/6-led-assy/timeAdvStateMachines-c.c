#include "blinkUpdate.h"
#include "secondUpdate.h"

void timeAdvStateMachines() // called every 1/250 sec
{
  blinkUpdate();
  secondUpdate();
}