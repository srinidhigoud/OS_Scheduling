using namespace std;

class randomNumGen{
public:
	int k;
	bool vverbose;
	string filename;
	randomNumGen(){
		k=0;
	}
	void reset(){
		this->k = 0;
		this->filename = "";
		this->vverbose = false;
	}
	int get(){
		int n = 0;
		ifstream source;
		source.open(filename);
		string line;
		int i=0;
		while(getline(source, line)){
			if(i==k){
				istringstream iss(line);
				iss>>n;
				break;
			}
			else {
				istringstream iss(line);
				iss>>n;
				i++;
			}
		}
		k++;
		if(vverbose){
			
			cout<<"  "<<n<<endl;
			cout<<endl;
		}
		return n;

	}
	
};
