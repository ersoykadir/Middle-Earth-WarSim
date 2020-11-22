#include <string>
#include "Character.h"
#include <vector>
#include <iostream>
using namespace std;

/*
	Constructor

*/
Character::Character(string _name, string _type, int _attack, int _defense, int _remainingHealth, int _nMaxRounds) {

	this->name = _name;
	this->type = _type;
	this->nRoundsSinceSpecial = 0;
	this->attack = _attack;
	this->defense = _defense;
	this->remainingHealth = _remainingHealth;
	this->nMaxRounds = _nMaxRounds;

	//Health history array, first element is the starting health
	this->healthHistory = new int[_nMaxRounds+1];
	this->healthHistory[0] = _remainingHealth;
	cout << "Character created" << this->name <<endl;
}

/*
	Copy constructor
*/
Character::Character(const Character& character) {
	cout << "Copy constructor is called." << endl;
	
	this->name = character.name;
	this->type = character.type;

	this->attack = character.attack;
	this->defense = character.defense;
	this->remainingHealth = character.remainingHealth;
	this->nMaxRounds = character.nMaxRounds;
	
	this->nRoundsSinceSpecial = character.nRoundsSinceSpecial;
	
	this->healthHistory = new int[character.nMaxRounds+1];
	for (int i = 0; i < character.nMaxRounds+1; ++i)
	{
		this->healthHistory[i] = character.healthHistory[i];
	}
}
/*
	Overloading assignment operator
*/
Character& Character::operator=(const Character& character) {

	cout << "Assinment operator called" << endl;
	if (this == &character) {
		return *this;
	}
	if (this->healthHistory != NULL) { 
		cout << "Deleting previously used (Assignment operator)" << endl;
		delete[] this->healthHistory;		
	}

	this->name = character.name;
	this->type = character.type;

	this->attack = character.attack;
	this->defense = character.defense;
	this->remainingHealth = character.remainingHealth;
	this->nMaxRounds = character.nMaxRounds;
	
	this->nRoundsSinceSpecial = character.nRoundsSinceSpecial;
	
	this->healthHistory = new int[character.nMaxRounds+1];
	for (int i = 0; i < character.nMaxRounds+1; ++i)
	{
		this->healthHistory[i] = character.healthHistory[i];
	}
	return *this;
}
/*
	Overloading comparison operator
*/
bool Character::operator<(const Character& other) {
	return (this->name < other.name) ;
}
/*
	Destructor
*/
Character::~Character() {
	cout << "Destructing"<< this->name << endl;
	if (this->healthHistory!=NULL)
	{
		delete[] this->healthHistory;
	}
}
