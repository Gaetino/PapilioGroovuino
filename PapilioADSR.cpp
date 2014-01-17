#include "PapilioADSR.h"
#include "arduino.h"

ModuleADSR::ModuleADSR()
{
  triggered = false;
  state = ADSR_INACTIVE;
  output = 0;
  sustainSave = 0;
  updateParam(3, 20, 200, 20);
}

void ModuleADSR::updateParam(unsigned long attackInput, unsigned long decayInput, unsigned long sustainInput, unsigned long releaseInput)
{
  if(attackInput != attackSave)
  {
    attack = 4874/((attackInput<<4)+1); // 2.5 ms to 10 s
	  attackSave = attackInput;
  }
  if(sustainInput != sustainSave)
  {
    sustain = sustainInput<<11; // convert to 19 bits
	  sustainSave = sustainInput;
  }
  if(decayInput != decaySave)
  {
    decay = (522240 - sustain)/(((decayInput<<4)+1)*107); // 2.5 ms to 10s
	  decayInput = decaySave;
  }
  if(releaseInput != releaseSave)
  {
    release = (sustain * 4874/((releaseInput<<4)+1))>>19; // 2.5 ms to 10s
	  releaseInput = releaseSave;
  }
 
}

void ModuleADSR::updateEvent(bool triggerInput)
{
  if(triggerInput && !triggered) 
  {
    triggered = true;
    state = ADSR_ATTACK;
  }
  if((!triggerInput) && triggered) 
  {
    triggered = false;
    state = ADSR_RELEASE;
  }
}

long ModuleADSR::generateParam()
{
  
  
  switch(state)
  {
    case ADSR_ATTACK: 
        if((output + attack) > 522240)
        {
          output = 522240;
		      state = ADSR_DECAY; 
        }
        else
        {
          output += attack; // increase the volume until 100 %
        }
        break;    
      
    case ADSR_DECAY:

      // Decrease the volume until sustain value is reached
      if(output >= decay)
      {
        output -= decay;
      }
      else
      {
        output = 0;
      }

      if(output <= sustain)
      {
        state = ADSR_SUSTAIN;
        output = sustain;
      }
      break;

    // Do nothing in the sustain case. The sound stays played until the trigger is trigged off

    case ADSR_RELEASE:
      
      // Decrease the output until 0 is reached

      if(output >= release)
      {
        output -= release;       
      }
      else
      {
        state = ADSR_INACTIVE;
	    output = 0;
      }
      
      break;
      
  } // end switch
  
  return (output >> 11); 
}

