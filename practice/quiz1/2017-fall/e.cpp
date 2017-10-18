#include <iostream>
#include <cstring>

class Game{
public:
	Game() : name(new char[1]) {name[0] = '\0';}
	Game(const char* n) : name(new char[strlen(n) + 1]){
		strcpy(name, n);
	}
	Game(const Game& vg) : name(new char[strlen(vg.name) + 1]){
		strcpy(name, vg.name);
	}
	~Game() {delete [] name;}
	const char* getName() const {return name;}
	Game& operator=(const Game& rhs){
		if(this == &rhs) return *this;
		delete [] name;
		name = new char[strlen(rhs.name) + 1];
		strcpy(name, rhs.name);
		return *this;
	}
private:
	char* name;
};

int main(){
	Game left4Dead, massEffect("Mass Effect"), ms = massEffect;
	left4Dead = "left4Dead";
	std::cout << ms.getName() << std::endl;
	std::cout << left4Dead.getName() << std::endl;
}

