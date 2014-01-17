#define SAMPLE_RATE 44100.0 
#define SAMPLES_PER_CYCLE 600 
#define SAMPLES_PER_CYCLE_FIXEDPOINT (SAMPLES_PER_CYCLE<<20) 
#define TICKS_PER_CYCLE (float)((float)SAMPLES_PER_CYCLE_FIXEDPOINT/(float)SAMPLE_RATE) 



class Osc
{
	
public:
   Osc();
   void updateParam(long input_freq);
   char input_waveform;
   char input_volume;
   short int output();
   

private:
   unsigned long ulPhaseIncrement;
   unsigned long ulPhaseAccumulator;

};
