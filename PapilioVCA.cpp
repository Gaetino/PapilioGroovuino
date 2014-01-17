#include "PapilioVCA.h"


VCA::VCA()
{
  input_volume = 200;
}

long VCA::output(long input_audio)
{
  return (input_audio*input_volume)>>8;
}
