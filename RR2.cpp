#include <iomanip>
using namespace std;

class RR2{
public:
	int findIdx(vector<Process> buf, int k){
		for(int i=0;i<buf.size();i++){
			if(buf[i].id==k) return i;
		}
		return -1;
	}
	int findIdx(deque<Process> buf, int k){
		for(int i=0;i<buf.size();i++){
			if(buf[i].id==k) return i;
		}
		return -1;
	}
	vector<Process> run(bool verbose, bool vverbose, vector<Process> process, printAll* p){
		int cpuT = 0;
		int finished_proc = 0;
		int ioT = 0;
		int time = 0;
		randomNumGen* random = new randomNumGen();
		random->filename = "./Random_Number.txt";
		random->vverbose = vverbose;
		deque<Process> waiting;
		deque<Process> ready;
		deque<Process> running;
		deque<Process> blocked;
		vector<Process> finished;
		int n_proc = process.size();
		auto compT = [](Process A, Process B){
			if(A.A!= B.A) return A.A<B.A;
			else return A.id<B.id;
		};
		// auto compio = [](Process A, Process B){
		// 	return A.ioT<B.ioT;
		// };
		

		sort(process.begin(),process.end(),compT);
		for(int i=0;i<n_proc;i++){
			process[i].id = i;
			waiting.push_back(process[i]);
		} 
		if(verbose){
			cout<<left<<"Before Cycle"<<setw(10)<<0<<":"<<setw(10);
			for(int i=0;i<n_proc;i++){
				cout<<"unstarted"<<setw(10)<<0<<setw(10);
			}
			cout<<endl;
		}
		while(finished_proc!=n_proc){
			sort(waiting.begin(),waiting.end(),compT);
			for(int i =0; i<waiting.size(); i++){
				//waiting[i].waitingT = time;
				if(waiting[i].A <= time) {
					ready.push_back(waiting[i]);
					waiting.pop_front();
					i--;
				}
			} 
			//sort(ready.begin(),ready.end(),compT);
			if(running.empty()){
				if(!ready.empty()){
					Process runningP = ready.front();
					ready.pop_front();
					if(runningP.burstT==0){
						if(vverbose) cout<<endl<<"Random Number for Burst time:  ";
						runningP.randomBurstT(random);
					}  ////////imp//is blocked also waiting
					runningP.q=2;
					running.push_back(runningP);
				}
			}
			for(int i=0;i<ready.size();i++){
				ready[i].waitingT++;
			} 
			if(verbose){
				//cout<<time<<endl;
				cout<<left<<"Before Cycle"<<setw(10)<<time+1<<":"<<setw(10);
				for(int i=0;i<n_proc;i++){
					
					int val = findIdx(blocked,i);
					if(val>=0) cout<<"blocked"<<setw(10)<<blocked[val].ioT<<setw(10);
					else {
						val = findIdx(ready,i);
						if(val>=0) cout<<"ready"<<setw(10)<<ready[val].q<<setw(10);
						else {
							val = findIdx(finished,i);
							if(val>=0) cout<<"terminated"<<setw(10)<<""<<setw(10);
							else {
								val = findIdx(waiting, i);
								if(val>=0) cout<<"unstarted"<<setw(10)<<waiting[val].q<<setw(10);
								else cout<<"running"<<setw(10)<<min(running[0].q, running[0].burstT)<<setw(10);
							}
						}
					}
				}
				cout<<endl;
			}
			time++;
			if(running.size()>0){
				p->CPU_Util++;
				running[0].burstT--;
				running[0].remT--;
				running[0].cpuT++;
				running[0].q--;
				cpuT++;
			}
			
			if(!blocked.empty()){
				p->IO_Util++;
				ioT++;
				//sort(blocked.begin(),blocked.end(),compio);
				for(int i=0;i<blocked.size();i++){
					blocked[i].ioT--;
					blocked[i].ioTime++;
					if(blocked[i].ioT==0){
						waiting.push_back(blocked[i]);
						blocked.erase(blocked.begin()+i);
						i--;
					} 
				}
			} 
			if(running.size()>0){
				if(running[0].remT==0){
					running[0].finishT = time;
					finished.push_back(running[0]);
					running.pop_front();
					finished_proc++;
				}
				else if(running[0].burstT==0) {
					if(vverbose) cout<<endl<<"Random Number for I/O time:  ";
					running[0].randomiotT(random);
					blocked.push_back(running[0]);
					running.pop_front();
				}
				else if(running[0].q==0){
					waiting.push_back(running[0]);
					running.pop_front();
				}
			}
		}
		random->reset();
		p->proc = finished;
		p->throughp = n_proc;
		return finished;
	}
};