class LowPassFilter2
{

public:

	LowPassFilter2()
	{
	  b0=b1=b2=b3=b4=t1=t2=0;
	}

	void updateParam(long cutoff, long resonance)
	{
      q = 256 - cutoff; 
      p = cutoff + ((((205 * cutoff)>>8) * q)>>8); 
      f = (int_p<<1) - 256; 
      long temp1 = (q * q)>>8;
      temp1 = (1434 * temp1)>>8;
      temp1 = temp1 + 256 - q;
      temp1 = (temp1*q)>>8;
      temp1 = temp1>>1;
      temp1 += 256;
      q = (temp1*resonance)>>8;
	}



	inline
	long generate_audio(long in)
	{
      in -= (q * b4)>>8;                          //feedback 
      t1 = b1; 
      b1 = (((in + b0) * p)>>8) - ((b1 * f)>>8); 
   
      t2 = b2; 
      b2 = (((b1 + t1) * p)>>8) - ((b2 * f)>>8); 
      t1 = b3; 
      b3 = (((b2 + t2) * p)>>8) - ((b3 * f)>>8); 
      b4 = (((b3 + t1) * p)>>8) - ((b4 * f)>>8); 
//    b4 = b4 - ((((((b4 * b4)>>8) * b4)>>8) * 10922)>>16);    //clipping 
      b0 = in; 
      return b4;
	}


private:
	long q,p,f;
	long b0,b1,b2,b3,b4,t1,t2;
	
};
