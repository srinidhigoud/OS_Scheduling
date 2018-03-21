#include "Process.cpp"
//#include "randomNumGen.cpp"
using namespace std;
class printAll{
public:
	vector<Process> proc;
	int finishing_time = 0;
	float CPU_Util = 0;
	float IO_Util = 0;
	float throughp = 0;
	float avg_turn = 0;
	float avg_waiting = 0;
	printAll(){};
	
	void printa(){
		auto compS = [](Process A, Process B){
			return A.id<B.id;
		};
		cout<<endl;
		sort(proc.begin(),proc.end(),compS);
		for(int i=0;i<proc.size();i++){
			proc[i].turnaroundT = proc[i].finishT - proc[i].A;
			cout<<"Process "<<i<<":"<<endl;
			this->finishing_time = max(this->finishing_time, proc[i].finishT);
			cout<<'\t'<<"(A,B,C,IO) "<<"("<<proc[i].A<<","<<proc[i].B<<","<<proc[i].C<<","<<proc[i].D<<")"<<endl;
			cout<<'\t'<<" Finishing Time "<<proc[i].finishT<<endl;
			cout<<'\t'<<" Turnaround Time "<<proc[i].turnaroundT<<endl;
			avg_turn += proc[i].turnaroundT;
			cout<<'\t'<<" I/O Time "<<proc[i].ioTime<<endl;
			cout<<'\t'<<" Waiting Time "<<proc[i].waitingT<<endl;
			avg_waiting += proc[i].waitingT;
			cout<<endl;
		}
		CPU_Util /= finishing_time;
		CPU_Util *= 100;
		IO_Util /= finishing_time;
		IO_Util *= 100;
		throughp /= finishing_time;
		throughp *= 100;
		avg_turn = (float)avg_turn/proc.size();
		avg_waiting = (float)avg_waiting/(float)proc.size();
		cout<<" Finishing Time "<<finishing_time<<endl;
		cout<<" CPU Utilization "<<CPU_Util<<endl;
		cout<<" IO Utilization "<<IO_Util<<endl;
		cout<<" Throughput "<<throughp<<endl;
		cout<<" Average Turnaround Time "<<avg_turn<<endl;
		cout<<" Average Waiting Time "<<avg_waiting<<endl;
		cout<<endl;
		cout<<"---------------------------";
		cout<<endl;
	}

};