
using namespace std;

class Process{
public:
	int A;
	int B;
	int C;
	int D;
	int id;
	int burstT;
	int ioT;
	int finishT;
	int waitingT;
	int cpuT;
	int turnaroundT;
	int remT;
	int ioTime;
	int q;
	Process(){
		A = 0;
		B = 0;
		C = 0;
		D = 0;
		id = 0;
		burstT = 0;
		ioT = 0;
		finishT = 0;
		waitingT = 0;
		q = 0;
	}

	void randomBurstT(randomNumGen* x){
		int val = x->get();
		val = 1+val%B;
		this->burstT = val;
	}
	void randomiotT(randomNumGen* x){
		if(this->C == 0) this->ioT = 0;
		else {
			int val = x->get();
			val = 1+val%D;
			this->ioT = val;
		} 
	}
};