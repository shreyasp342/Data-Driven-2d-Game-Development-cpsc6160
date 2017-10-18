#include <string>
#include <vector>
#include <iostream>

class Pokemon{
public:
	Pokemon() : name() {std::cout << "default" << std::endl;}
	Pokemon(const std:: string& n) : name(n) {
		std::cout << "conversion" << std::endl;
	} 
	Pokemon(const Pokemon& p) : name(p.name) {
		std::cout << "copy" << std::endl;
	}
	Pokemon& operator=(const Pokemon&) {
		std::cout << "assignment" << std::endl;
		return *this;
	}
private:
	std::string name;
};

class Pokedex{
public:
	Pokedex(const std::string& s) : pokemon(s) {
		// pokemon = s;
	}
private:
	Pokemon pokemon;
};

int main(){
	Pokedex p("Steelix");
}