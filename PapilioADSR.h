#define ADSR_ATTACK 0
#define ADSR_DECAY 1
#define ADSR_SUSTAIN 2
#define ADSR_RELEASE 3
#define ADSR_INACTIVE 4

class ModuleADSR
{
  public:
    ModuleADSR();
	  void updateParam(long attack, long decay, long sustain, long release);
	  void updateEvent(bool trig);
	  long generateParam();
  
  private:
    long output;
    unsigned char state;
    long attackSave, decaySave, sustainSave, releaseSave;
	  long attack, decay, sustain, release;
	  bool triggered;
};
