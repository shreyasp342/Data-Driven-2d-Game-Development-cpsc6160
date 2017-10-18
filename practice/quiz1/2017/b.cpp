#include <iostream>

class Pokemon{
public:
	Pokemon() : combatPower(0){
		std::cout << "default" << std::endl;
	}
	Pokemon(int c) : combatPower(c) {
		std::cout << "conversion" << std::endl;
	}
	Pokemon(const Pokemon& p) : combatPower(p.combatPower){
		std::cout << "copy" << std::endl;
	}
	Pokemon& operator=(const Pokemon&){
		std::cout << "assignment" << std::endl;
		return *this;
	}
	unsigned int getCP() const {return combatPower;}
private:
	unsigned int combatPower;
};

void display(const Pokemon pokemon){
	std::cout << pokemon.getCP() << std::endl;
}

int main(){
	Pokemon snorlax(2840), dragonite = snorlax;
	display(dragonite);
}