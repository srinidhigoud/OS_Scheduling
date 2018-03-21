#include <iostream>
// #include <vector>
// #include <fstream>
// #include <string>
// #include <map> 
// #include <unordered_map>
// #include <deque>
// #include <utility> 
// #include <iterator>
// #include <sstream>
#include <algorithm>
#include <ctime>
#include <time.h>

int main(){
	long size = 1024*1024*1024;
	clock_t t;

	char *arr = (char*)malloc(size);
	for(long i=0;i<size;i++){
		arr[i] = 0;
	}
	int sum = 0;
	t=clock();
	for(long i=0;i<size;i++){
		sum+=arr[i];
		printf(sum);

	}
	t=clock()-t;
	cout<<t<<endl;
	printf("Bandwidth = %lf", size/t);

}