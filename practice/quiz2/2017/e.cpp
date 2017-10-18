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
private:
	std::string name;
};

int main(){
	std::vector<Pokemon> pokes;
	pokes.reserve(2);
	pokes.emplace_back(std::string("Larvitar"));
	pokes.emplace_back(std::string("Steelix"));
}