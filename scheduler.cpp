
/***************************************************

	Srinidhi Goud Myadaboyina
	N12449860	
	Lab 2


***************************************************/
///g++ scheduler.cpp -Wall -std=c++0x


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map> 
#include <unordered_map>
#include <deque>
#include <utility> 
#include <iterator>
#include <sstream>
#include <algorithm>
#include "randomNumGen.cpp"
#include "printAll.cpp"
#include "uni.cpp"
#include "FCFS.cpp"
#include "RR2.cpp"
#include "SRTN.cpp"


using namespace std;





vector<Process> readFileToProcess(string inputFilename){
	vector< Process > output;
	ifstream source;
	source.open(inputFilename);
	string line;
	getline(source, line);
	istringstream iss(line);
	// int n;
	// iss >> n;
	int enterNumber;
	int n;
	iss>>n;

	for(int i=0;i<n;i++){
		Process p;
		iss >> enterNumber;
		p.id = i;
		p.A = enterNumber;
		iss >> enterNumber;
		p.B = enterNumber;
		iss >> enterNumber;
		p.C = enterNumber;
		p.remT = p.C;
		iss >> enterNumber;
		p.D = enterNumber;

		output.push_back(p);
	}
	return output;

}

// void printAll(vector<Process> p){
// 	int Finishi_Time = 0;
// }


int main(int argc, char* argv[]){
	int index = 1;
	bool verbose = false;
	bool vverbose = false;
	string sss(argv[index]);
	if(sss.compare("-verbose")==0) {
		index++;
		verbose = true;
	} 
	else if(sss.compare("-vverbose")==0) {
		index++;
		verbose = true;
		vverbose = true;
	} 
	string inputFilename(argv[index]);
	vector<Process> process = readFileToProcess(inputFilename);
	cout<<"The original input was: "<<process.size()<<" ";
	for(int i=0;i<process.size();i++){
		//cout<<process[i].id<<" ";
		cout<<process[i].A<<" ";
		cout<<process[i].B<<" ";
		cout<<process[i].C<<" ";
		cout<<process[i].D<<" ";
		//cout<<endl;
	}
	cout<<endl;
	vector<Process> buf(process);
	auto compT = [](Process A, Process B){
			if(A.A!= B.A) return A.A<B.A;
			else return A.id<B.id;
		};
	sort(buf.begin(),buf.end(),compT);
	cout<<"The sorted input is: "<<buf.size()<<" ";
	for(int i=0;i<process.size();i++){
		//cout<<process[i].id<<" ";
		cout<<buf[i].A<<" ";
		cout<<buf[i].B<<" ";
		cout<<buf[i].C<<" ";
		cout<<buf[i].D<<" ";
		//cout<<endl;
	}
	cout<<endl;
	FCFS* f = new FCFS();
	printAll pp1;
	cout<<endl;
	cout<<"Part a"<<endl<<endl;
	cout<<"This detailed printout gives the state and remaining burst for each process\n";
	cout<<endl;
	f->run(verbose, vverbose, process, &pp1);
	cout<<"The scheduling algorithm used is FCFS"<<endl<<endl;
	pp1.printa();
	cout<<endl;
	RR2* r = new RR2();
	printAll pp2;
	cout<<endl;
	cout<<"Part b"<<endl<<endl;
	cout<<"This detailed printout gives the state and remaining burst for each process\n";
	cout<<endl;
	r->run(verbose, vverbose, process, &pp2);
	cout<<"The scheduling algorithm used is RR2"<<endl;
	pp2.printa();
	cout<<endl;
	uni* u = new uni();
	printAll pp3;
	cout<<endl;
	cout<<"Part c"<<endl<<endl;
	cout<<"This detailed printout gives the state and remaining burst for each process\n";
	cout<<endl;
	u->run(verbose, vverbose, process, &pp3);
	cout<<"The scheduling algorithm used is Uniprogrammed"<<endl;
	pp3.printa();
	cout<<endl;
	SRTN* srt = new SRTN();
	printAll pp4;
	cout<<endl;
	cout<<"Part d"<<endl<<endl;
	cout<<"This detailed printout gives the state and remaining burst for each process\n";
	cout<<endl;
	srt->run(verbose, vverbose, process, &pp4);
	cout<<"The scheduling algorithm used is SRTN"<<endl;
	pp4.printa();
	cout<<endl;

	return 0;
	


}