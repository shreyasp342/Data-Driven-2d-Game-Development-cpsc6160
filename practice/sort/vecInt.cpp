#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

const int MAX = 20;
const int MAX_NUMBER = 100;

void init(std::vector<int>& v){
	v.reserve(20);
	for(int i=0; i<MAX; i++){
		v.push_back(rand()%MAX_NUMBER);
	}
}

void print(std::vector<int>& vec){
	for(auto v:vec){
		std::cout << v << ",\t";
	}
	std::cout << std::endl;
}

int main(){
	std::vector<int> vec;
	init(vec);
	print(vec);
	sort(vec.begin(), vec.end());
	print(vec);
}