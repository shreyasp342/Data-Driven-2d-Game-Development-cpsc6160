#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

const int MAX = 20;
const int MAX_NUMBER = 100;

class Number{
public:
	Number() : number(0) {}
	Number(int n) : number(n) {}
	Number(const Number& n) : number(n.number) {}
	int getNumber() const { return number;}
	// bool operator<(const Number* n) const {
	// 	return number < n->getNumber();
	// }
private:
	int number;
};

std::ostream& operator<<(std::ostream& out, const Number* n){
	return out << n->getNumber();
}

class NumberLess{
public:
	bool operator()(const Number* lhs, const Number* rhs) const{
		return lhs->getNumber() < rhs->getNumber();
	}
};

void init(std::vector<Number*>& v){
	v.reserve(20);
	for(int i=0; i<MAX; i++){
		v.push_back(new Number(rand()%MAX_NUMBER));
	}
}

void print(std::vector<Number*>& vec){
	for(auto v:vec){
		std::cout << v << ",\t";
	}
	std::cout << std::endl;
}

int main(){
	std::vector<Number*> vec;
	init(vec);
	print(vec);
	sort(vec.begin(), vec.end(), NumberLess());
	print(vec);
}