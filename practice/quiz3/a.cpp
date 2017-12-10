#include <iostream>
#include <cstring>

class Sprite{
public:
	Sprite(const char* n) : name(new char[strlen(n)+1]) {
		strcpy(name,n);
	}
	const char* getName() const {return name;}
	const char& operator[](int index) const {
		std::cout << "const []" << name[index] << std::endl;
		return name[index];
	}
	char&  operator[](int index){
		std::cout << "non-const []" << name[index] << std::endl;
		return name[index];
	}
private:
	char* name;
};

void printLetter(const Sprite& sprite, int n){
	const char letter = sprite[n];
}

int main(){
	Sprite sprite("redorb");
	printLetter(sprite, 0);
}