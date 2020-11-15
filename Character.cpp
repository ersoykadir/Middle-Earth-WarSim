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

	//Array of possible character types.
	string types[5] = {"Hobbit","Men","Elves","Dwarfs","Wizards"};
	int typeIndex=-1;//Index that shows this characters type,initialized negative to avoid wrong input.
	for (int i = 0; i < 5; ++i)//Search for given type in the types list
	{
		if (this->type == types[i])
		{
			typeIndex = i;//Match our index with the found type in array
		}
	}
	//Initialize nRoundsSinceSpecial according to type
	switch(typeIndex)
	{
		case 0://Hobbit
			this->nRoundsSinceSpecial = -1;
			break;
		case 1://Men
			this->nRoundsSinceSpecial = -1;
			break;
		case 2://Elves
			this->nRoundsSinceSpecial = 10;
			break;
		case 3://Dwarfs
			this->nRoundsSinceSpecial = 20;
			break;
		case 4://Wizards
			this->nRoundsSinceSpecial = 50;
			break;
	}

	this->attack = _attack;
	this->defense = _defense;
	this->remainingHealth = _remainingHealth;
	this->nMaxRounds = _nMaxRounds;//????????????

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
	this->nMaxRounds = character.nMaxRounds;//????????????
	
	this->nRoundsSinceSpecial = character.nRoundsSinceSpecial;
	
	// unassigned array elements are random numbers would it cause any problem ??????
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
	this->nMaxRounds = character.nMaxRounds;//????????????
	
	this->nRoundsSinceSpecial = character.nRoundsSinceSpecial;
	
	this->healthHistory = new int[character.nMaxRounds+1];
	for (int i = 0; i < character.nMaxRounds+1; ++i)
	{
		this->healthHistory[i] = character.healthHistory[i];
	}
}
/*
	Overloading comparison operator
*/
bool Character::operator<(const Character& other) {
	//cout << "helllooo"<<endl;
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