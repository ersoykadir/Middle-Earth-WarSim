#include "Character.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int findIndex(vector<Character*>* v,Character *c);
string printer(ostream &out,vector<Character*>* v);
bool comparePtrToObject(Character* first,Character* second);
Character* findCharacterA(Character* community[],string name);
Character* findCharacterV(vector<Character*> *community,string name);
int main(int argc, char* argv[]) {

	string infile_name = argv[1];
	string outfile_name = argv[2];
	
	ifstream infile;
	infile.open(infile_name);
	ofstream outfile;
	outfile.open(outfile_name);

	int maxRounds;
	infile >> maxRounds;
	infile.ignore();
	cout<< maxRounds <<endl;
	vector<Character*> community1;
	vector<Character*> community2;
	
	//Character* community1[5];
	//Character* community2[5];

	for (int i = 0; i < 10; ++i)
	{
		string characterName,characterType;
		int attack,defense,health;
		infile >> characterName;
		infile >> characterType;
		infile >> attack;
		infile >> defense;
		infile >> health;
		Character *c = new Character(characterName,characterType,attack,defense,health,maxRounds);
	
		if (i < 5){
			community1.push_back(c);
			//community1[i] = c;
		}
		else{
			community2.push_back(c);
			//community2[i] = c;
		}
	}
	
	Character* c = findCharacterV(&community1,"Blair");
	Character* b = findCharacterV(&community1,"Lynn");
	
	cout << c->name << endl;
	cout << community1.size()<<endl;
	sort(community1.begin(),community1.end(),comparePtrToObject);
	printer(cout,&community1);
	cout << findIndex(&community1,c)<<endl;

	//indexx
	// Character* attacker = findCharacterV(&community1,"Daryl");
	// attacker->isAlive = false;
	// 		if (!attacker->isAlive){
	// 			int index = findIndex(&community1,attacker);
	// 			for (int i = index; i < community1.size(); ++i)
	// 			{
	// 				if (community1[i]->isAlive){
	// 					attacker = community1[i];
	// 					break;
	// 				}
	// 			}
	// 		}
	// cout << attacker->name << endl;
	
	// iterator
	//Character *attacker = findCharacterV(community1,"Daryl");
	// attacker->isAlive = false;
	// 		if (!attacker->isAlive){
	// 			vector<Character*>::iterator vectorIt;
	// 			for (vectorIt = community1.begin(); vectorIt < community1.end(); vectorIt++)
	// 			{
					
	// 			}
	// 			for (*vectorIt=attacker; vectorIt < community1.end(); vectorIt++){
	// 				cout << "insideloop"  << (*vectorIt)->name << endl;
	// 				// if ((*vectorIt) -> isAlive){
	// 				// 	attacker = *vectorIt;
	// 				// 	//cout << attacker->name << endl;
	// 				// 	break;
	// 				// }
	// 			}
	// 		}
	//cout << attacker->name << endl;
	
	// vector<Character*>::iterator vectorIt = find(community1.begin(),community1.end(),);
	// cout <<  (*vectorIt + 1) - community1.begin() << endl;
	//  WAR
	// int currentRound = maxRounds;
	
	// while(maxRounds>0){
	// 	string attackerName,defenderName,usedSpecialStr;
	// 	Character* attacker,defender;
	// 	infile >> attackerName;
	// 	infile >> defenderName;
	// 	infile >> usedSpecialStr;
	// 	if ( (maxRounds - currentRound) % 2 == 0 ){
	// 		//find attacker in community 1
	// 		//find defender in community 2
	// 		attacker = findCharacterV(&community1,attackerName);
	// 		if (!attacker->isAlive){
	// 			int index = findIndex(&community1,attacker);
	// 			for (int i = index; i < community1.size(); ++i)
	// 			{
	// 				if (community1[i]->isAlive){
	// 					attacker = community1[i];
	// 					break;
	// 				}
	// 			}
	// 		}
	// 		defender = findCharacterV(&community2,defenderName);
	// 	}
	// 	else{
	// 		//find attacker in community 2
	// 		//find defender in community 1
	// 		attacker = findCharacterV(&community2,attackerName);
	// 		defender = findCharacterV(&community1,defenderName);

	// 	}
	// 	//CHECK IF ATTACKER ALIVE
	// 	//WHAT HAPPENS IF DEFENDER IS DEAD ?????????
	// 	if (attacker->isAlive == false)
	// 	{
			
	// 	}
	// 	if (usedSpecialStr == "SPECIAL"){
	// 		//check character type, check cooldown, check doable or not
	// 		if (attacker->type == "Elves"){
				
	// 		}
	// 	}
	// 	else{
	// 		usedSpecial=false;
	// 	}
	// 	int attackDamage = attacker->attack - defender->defense;

	// }

	infile.close();
	outfile.close();

	//At the end of every round, decrease every characters "special rounds remaining" by one UNTIL THEY BECOME 0, DONT DECREASE THEN
	//At the end of every round, update the character.healthHistory[currentRound] to its character.remainingHealth
	//cout<< <<endl;
	// int currentRound = 0;
	// int* pToVector = new int[5];
	// pToVector[1] = 10;
	// cout<< pToVector[1] <<endl;

    return 0;
}

int findIndex(vector<Character*>* v,Character *c){
	int index;
	for (index = 0; index < v->size(); ++index){
		if ((*v)[index]->name == c->name)
		{
			return index;
		}
	}
}

bool comparePtrToObject(Character* first,Character* second){
	return *first < *second;
}

Character* findCharacterA(Character* community[],string name)
{

	for (int i = 0; i < 5;++i){
		if (community[i]->name == name){
			//cout << "heytheree" << endl;
			return community[i];
		}
	}
	//cout<< "wwrooong" <<endl;
	return NULL;
}

Character* findCharacterV(vector<Character*> *community,string name)
{
	for (int i = 0; i < community->size(); ++i){
		if ((*community)[i]->name == name){
			return (*community)[i];
		}
	}
	return NULL;
}


string printer(ostream &out,vector<Character*>* v){

	vector<Character*>::iterator vectorIt;
				for (vectorIt=v->begin(); vectorIt < v->end(); vectorIt++){
					cout << "printer"  << (*vectorIt)->name << endl;
				}

	// for (int i = 0; i < v->size(); ++i)
	// {
	// 	//cout << "here"<<endl;
	// 	//out <<(*v)[i]<< " "; 
	// 	out << (*v)[i]->name << " ";
	// }
	// 	out <<endl;
}