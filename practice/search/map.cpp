#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include <cstdlib>
#include <algorithm>

void init(std::map<std::string, int>& mymap, std::vector<std::string>& vec){
	for(auto v:vec){
		mymap[v] = rand()%100;
	}
}

void print(std::map<std::string, int>& mymap){
	for(auto& m :mymap){
		std::cout << m.first << "," << m.second << std::endl;
	}
}

int main(){
	std::map<std::string, int> mymap;
	std::vector<std::string> vec;
	vec.push_back("A");
	vec.push_back("B");
	vec.push_back("C");
	init(mymap, vec);
	print(mymap);
	
	if(mymap.find("D")!=mymap.end()) std::cout << "found" << std::endl;
	else std::cout << "not found" << std::endl;

}