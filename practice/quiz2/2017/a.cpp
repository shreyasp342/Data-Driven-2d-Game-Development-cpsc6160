#include <iostream>

int main(){
	int a = 9, b = 11;
	int c = a%3? b:17;
	std::cout << c << std::endl;
	int v = 320;
	v = v * ((a%2)?-1:1);
	std::cout << v << std::endl;
}