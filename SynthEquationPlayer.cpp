#include "Arduino.h"
#include "Defines.h"
#include "SynthEquationPlayer.h"

SynthEquationPlayer::SynthEquationPlayer(Module* inputs[])
{
  equation_player.equation_input = inputs[MOD_INPUT];
  equation_player.sample_rate_input = inputs[SR_INPUT];
  equation_player.param1_input = inputs[PARAM1_INPUT];
  equation_player.param2_input = inputs[PARAM2_INPUT];
  equation_player.param3_input = inputs[PARAM3_INPUT];
  equation_player.reset_input  = inputs[RESET_INPUT];
  
  this->last_module = &equation_player;
}
