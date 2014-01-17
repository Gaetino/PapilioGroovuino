#define FX_SHIFT 8
#define SHIFTED_1 256


class LowPassFilter
{

public:

	LowPassFilter();

	void setCutoffFreq(unsigned char cutoff)
	{
		f = cutoff;
		setFeedback((long)cutoff);
	}

	void setResonance(unsigned char resonance)
	{
		q = resonance;
	}

	inline
	long generate_audio(long in)
	{
		buf0+=(f *  ((in - buf0) + ((fb*buf0-buf1)>>8)))>>8;
		buf1+=(f * (buf0-buf1))>>8;
		return buf1;
	}


private:
	long f;
	long fb;
	long q;
	long buf0,buf1;

	inline
	void setFeedback(long f)
	{
		fb = q + ((q * (256 - f))>>8);
	}
};
