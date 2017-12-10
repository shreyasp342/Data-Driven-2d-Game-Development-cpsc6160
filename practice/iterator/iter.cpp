#include <iostream>
#include <vector>

void print(std::vector<int>& vec){
	// for(auto v:vec){
	// 	std::cout << v << ",";
	// }
	// std::cout << std::endl;

	// std::vector<int>::const_iterator it = vec.begin();
	// while(it != vec.end()){
	// 	std::cout << *it << ",";
	// 	++it;
	// }
	// std::cout << std::endl;

	for(unsigned int i=0; i != vec.size(); i++){
		std::cout << vec[i] << ",";
	}
	std::cout << std::endl;
}

int main(){
	std::vector<int> v;
	v.push_back(5);
	v.push_back(6);
	v.push_back(3);
	v.push_back(2);
	v.push_back(1);
	v.push_back(7);
	v.push_back(8);
	print(v);
}