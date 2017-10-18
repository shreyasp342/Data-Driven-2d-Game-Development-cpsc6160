#include <iostream>

void initialize(int x, int y){
	x = 7;
	y = 8;
}

int main(){
	int a = 10, b = 11;
	initialize(a, b);
	std::cout << a << std::endl;
	std::cout << b << std::endl;
}