#include <iostream>
#include <vector>

const int MAX = 3;

class Number{
public:
	Number() : number(0) {std::cout << "default" << std::endl;}
	explicit Number(int n) : number(n) {
		std::cout << "convert: " << n << std::endl;
	}
	Number(const Number& a) : number(a.number) {
		std::cout << "copy: " << a.number << std::endl;
	}
	Number& operator=(const Number& rhs) {
		if (this != &rhs) {number = rhs.number;}
		std::cout << "copy: " << rhs.number << std::endl;
		return *this;
	}
	int getNumber() const {return number;}
private:
	int number;
};

void print(const std::vector<Number>& vec){
	for(unsigned int i = 0; i < vec.size(); ++i){
		std::cout << vec[i].getNumber() << ", ";
	}
	std::cout << std::endl;
}

void init (std::vector<Number>& vec){
	for (unsigned int i = 0; i < MAX; ++i){
		vec.push_back(Number(i+1));
	}
}

int main(){
	std::vector<Number> vec;
	vec.reserve(3);
	init(vec);
	vec.push_back(Number(4));
	std::cout << "SIZE: " << vec.size() << std::endl;
	std::cout << "CAPACITY: " << vec.capacity() << std::endl;
	print(vec);
}