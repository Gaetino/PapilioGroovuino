class LowPassFilter3
{

public:

  LowPassFilter3()
  {
    y1=y2=y3=y4=oldx=oldy1=oldy2=oldy3=0;
  }

  void updateParam(long cutoff, long resonance)
  {
      p = (cutoff*(460 - ((205*cutoff)>>8)))>>8;
      k = (p<<1) - 256;

      int t = ((256 - p)*355)>>8;
      int t2 = 3072 + ((t*t)>>8);
      r = resonance * (t2 + 6*t) / (t2 - 6*t);
  }

  inline
  long generate_audio(long in)
  {
      x = input - ((r*y4)>>8);

//Four cascaded onepole filters (bilinear transform)
     y1 = ((x*p)>>8) + ((oldx*p)>>8) - ((k*y1)>>8);
     y2 = ((y1*p)>>8) + ((oldy1*p)>>8) - ((k*y2)>>8);
     y3 = ((y2*p)>>8) + ((oldy2*p)>>8) - ((k*y3)>>8);
     y4 = ((y3*p)>>8) + ((oldy3*p)>>8) - ((k*y4)>>8);

//Clipper band limited sigmoid
//  y4-=(y4*y4*y4)/6.f;
     int temp = (y4*y4)>>16;
     temp = (temp*y4)>>16;
     y4 -= temp/6;

     oldx = x; oldy1 = y1; oldy2 = y2; oldy3 = y3;
     return y4;
  }


private:
    int y1,y2,y3,y4;
    int oldx;
    int oldy1,oldy2,oldy3;
    int x, r, p, k;
};
