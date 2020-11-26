#include "Character.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

//FIND INDEX OF GIVEN CHARACTER IN THE COMMUNITY LIST
int findIndex(const vector<Character*>& community,string characterName);
//PRINT OUT THE VECTOR TO GIVEN OUTSTREAM
string printer(ostream &out,const vector<Character*> &v);
//COMPARE 2 CHARACTER ACCORDING TO THEIR NAME, Used for sorting
bool comparePtrToObject(Character* first,Character* second);
//FIND GIVEN CHARACTER'S NAME AND RETURN IF ALIVE,ELSE FIND NEXT ALIVE CHARACTER;
Character* findCharacter(const vector<Character*> &community,string name);
//MANAGE SPECIAL SKILLS
void specialChecks(const vector<Character*> &community,string special, Character* attacker,string &lastKilledName,bool& doubleDwarf);
//CHECK EVERY MEMBER OF COMMUNITY ALIVE OR NOT
bool allMembersALive(const vector<Character*> &community);
//Update special round of every character in the community 
void updateSpecialRounds(const vector<Character*> &community);
//Update health history of every character in the community
void updateHealthHistory(const vector<Character*> &community,int currentRound);
//print health records of everybody
void healthRecords(ostream &out,const vector<Character*> &community1,const vector<Character*> &community2,int& roundsOfWar);
//check whether the game ending conditions satisfied or not
bool isGameOver(const vector<Character*> &community1,const vector<Character*> &community2,int& winner);
//swap two community's characters
void communitySwap(vector<Character*> *&attackerCommunity,vector<Character*> *&defenderCommunity);

static int currentRound = 1;
int main(int argc, char* argv[]) {

	string infile_name = argv[1];//READ INPUT FILE NAME
	string outfile_name = argv[2];//READ OUTPUT FILE NAME

	//OPEN INPUT AND OUTPUT FILE STREAMS
	ifstream infile;
	infile.open(infile_name);
	ofstream outfile;
	outfile.open(outfile_name);

	//READ NUMBER OF MAXIMUM ROUNDS
	int maxRounds;
	infile >> maxRounds;
	infile.ignore();//ESCAPE FROM READING \n

	cout<< maxRounds <<endl;

	//Community lists with pointers to characters
	vector<Character*> community1;
	vector<Character*> community2;

	for (int i = 0; i < 10; ++i){
	//Read every character's properties, create an instance and put in the lists.
		string characterName,characterType;
		int attack,defense,health;
		infile >> characterName;
		infile >> characterType;
		infile >> attack;
		infile >> defense;
		infile >> health;

		Character *c = new Character(characterName,characterType,attack,defense,health,maxRounds);

		if (i < 5) community1.push_back(c);//First 5 characters belong to community 1
		else community2.push_back(c);//Rest is in community 2
	}
	
	// WAR PHASE
	int winner = 0;// If winner variable is 0, war ends in draw, if 1 community 1 wins,if 2 community 2 wins
	string lastKilledFromC1 = "";//Name of the last killed character of community 1
	string lastKilledFromC2 = "";//Name of the last killed character of community 2

	vector<Character*> *attackerCommunity = &community1;
	vector<Character*> *defenderCommunity = &community2;
	while(currentRound <= maxRounds){//If round limit is reached, it's a draw.
		//Reading current round's attacker's and defender's properties
		string attackerName,defenderName,usedSpecialStr;
		Character* attacker;
		Character* defender;
		infile >> attackerName;
		infile >> defenderName;
		infile >> usedSpecialStr;//Indicates whether special skills used this round by attacker or not.

		bool doubleDwarf = false;//Whether attacker dwarf used his special skill or not.

		//Community 1 attacks first, then communities attack consecutively
		attacker = findCharacter(*attackerCommunity,attackerName);
		defender = findCharacter(*defenderCommunity,defenderName);

		//Handles special effects if used.
		if(currentRound%2==1){
			specialChecks(*attackerCommunity,usedSpecialStr,attacker,lastKilledFromC1,doubleDwarf);
		}
		else{
			specialChecks(*attackerCommunity,usedSpecialStr,attacker,lastKilledFromC2,doubleDwarf);
		}

		int attackDamage = (attacker->attack) - (defender->defense);//Damage given by attacker
		if(attacker->type == "Dwarfs" && doubleDwarf) attackDamage*=2;//Damage doubles if attacker dwarf uses special skill

		if(attackDamage>0){//Defender's health reduced according to damage
			defender->remainingHealth -= attackDamage;
			if(defender->remainingHealth <= 0){//If damage exceeds health kill defender
				defender->remainingHealth = 0;
				defender->isAlive = false;
				if(currentRound%2==1){
					lastKilledFromC2 = defender->name;
				}
				else{
					lastKilledFromC1 = defender->name;
				}
			}
		}
		//Increase rounds passed since special effect is used by 1 for every character
		updateSpecialRounds(community1);
		updateSpecialRounds(community2);

		//Update every character's health history at the end of the round.
		updateHealthHistory(community1,currentRound);
		updateHealthHistory(community2,currentRound);

		//Checking Game winning conditions
		if(isGameOver(community1,community2,winner)) break;

		currentRound++;
		communitySwap(attackerCommunity,defenderCommunity);
	}

	if(winner==1) {
		outfile << "Community-1" << endl;
	}
	else if(winner==2){
		outfile << "Community-2" << endl;
	}
	else{
		outfile << "Draw" << endl;
	}

	if(currentRound>maxRounds) currentRound--;
	outfile << currentRound << endl;

	int deadCount = 0;
	for(auto ch : community1){
		if(ch->isAlive == false) deadCount++;
	}
	for(auto ch : community2){
		if(ch->isAlive == false) deadCount++;
	}
	outfile << deadCount << endl;

	healthRecords(outfile,community1,community2,currentRound);

	infile.close();
	outfile.close();

    return 0;
}

//Swap two given communities
void communitySwap(vector<Character*> *&attackerCommunity,vector<Character*> *&defenderCommunity){
	vector<Character*> *temp = attackerCommunity;
	//vector<Character*> tempB = *defenderCommunity;
	attackerCommunity = defenderCommunity;
	defenderCommunity = temp;
}

void healthRecords(ostream &out,const vector<Character*> &community1,const vector<Character*> &community2,int& roundsOfWar){
	for(auto character : community1){
		out << character->name << " ";
		for (int i = 0; i < roundsOfWar+1 ; ++i)
		{
			out << character->healthHistory[i] << " ";
		}
		out<<endl;
	}
	for(auto character : community2){
		out << character->name << " ";
		for (int i = 0; i < roundsOfWar+1 ; ++i)
		{
			out << character->healthHistory[i] << " ";
		}
		out<<endl;
	}
}

//Check conditions of winning
bool isGameOver(const vector<Character*> &community1,const vector<Character*> &community2,int& winner){
	Character* hobbit1 = findCharacter(community1,"Hobbit");
	Character* hobbit2 = findCharacter(community2,"Hobbit");
	//Check if hobbits are alive
	if(currentRound==245){
	    cout<<endl;
	}
	if( !(hobbit1->isAlive && hobbit2->isAlive) ){
		if(hobbit1->isAlive)
			winner = 1;
		else {
			winner = 2;
		}
		return true;
	}
	//If code reaches here both hobbits are alive
	//Check if everybody except hobbit in a commmunity is dead
	bool allDeadCommunity1 = true;
	for(auto ch : community1){
		if(ch->type != "Hobbit" && ch->isAlive == true) {
			allDeadCommunity1 = false;
		}
	}
	bool allDeadCommunity2 = true;
	for(auto ch : community2){
		if(ch->type != "Hobbit" && ch->isAlive == true) {
			allDeadCommunity2 = false;
		}
	}
	if(allDeadCommunity1 || allDeadCommunity2){
		if(allDeadCommunity1){
			winner = 2;
		}
		else{
			winner = 1;
		}
	}
	return allDeadCommunity1 || allDeadCommunity2;
}

//Write every character's remaining health in current round to health history
void updateHealthHistory(const vector<Character*> &community,int currentRound){
	for(auto character : community){
		character->healthHistory[currentRound] = character->remainingHealth;
	}
}

//Increase "rounds passed since special effect is used" by 1
void updateSpecialRounds(const vector<Character*> &community){
	for(auto character : community){
		character->nRoundsSinceSpecial++;
	}
}
//True if every member of community is alive
bool allMembersALive(const vector<Character*> &community){
	for(auto character : community){
		if(character->isAlive == false) return false;
	}
	return true;
}
//Do special skill arrangements 
void specialChecks(const vector<Character*> &community,string special, Character* attacker,string &lastKilledName,bool &doubleDwarf){

	if (special == "SPECIAL"){
		//check character type, check cooldown, check doable or not
		if (attacker->type == "Elves" && attacker->nRoundsSinceSpecial > 10){
				Character* hobbit = findCharacter(community,"Hobbit");//if hobbit is dead code would not reach here
				hobbit->remainingHealth += attacker->remainingHealth / 2;
				attacker->remainingHealth -= attacker->remainingHealth/2;
		}
		if (attacker->type == "Dwarfs" && attacker->nRoundsSinceSpecial > 20){
			doubleDwarf = true;
		}
		if (attacker->type == "Wizards" && attacker->nRoundsSinceSpecial > 50){
			if(!allMembersALive(community) && lastKilledName != ""){
				Character* lastKilled = community[findIndex(community,lastKilledName)];
				if(lastKilled->isAlive == true){
					lastKilled->remainingHealth = lastKilled->healthHistory[0];
				}
				else{
					lastKilled->isAlive = true;
					lastKilled->remainingHealth = lastKilled->healthHistory[0];
					lastKilled->nRoundsSinceSpecial = 0;
				}
			}
		}
		attacker->nRoundsSinceSpecial = 0;
	}
}


//Find index of given character name
int findIndex(const vector<Character*>& community,string name){
	if(name == "Hobbit"){//EXCEPTION JUST FOR FINDING HOBBIT, USE GIVEN NAME AS TYPE
		int index = 0;
		string type = name;
		for (auto ch : community){
			if (ch->type == type){
				return index;
			}
			index++;
		}
	}
	int index = 0;
	for (auto ch : community){
		if (ch->name == name){
			return index;
		}
		index++;
	}
}

bool comparePtrToObject(Character* first,Character* second){
	return *first < *second;
}


Character* findCharacter(const vector<Character*> &community,string chName)
{
	
	if(chName == "Hobbit"){
		int indexOfHobbit = findIndex(community,chName);
		return community[indexOfHobbit];
	}
	//Create list of names and sort alphabetically
	vector<string> nameList;
	for(auto ch : community){
		nameList.push_back(ch->name);
	}
	sort(nameList.begin(),nameList.end());
	//Find index of given character name in the name list
	int index=0;
	for(auto nm : nameList){
		if(nm==chName) {
			break;
		}
		index++;
	}
	//iterator on name list started on desired character
	auto vectorIt = nameList.begin() + index;
	Character *c = community[findIndex(community,(*vectorIt))];
	//if desired character is alive return it
	if (c->isAlive) return c;
	else{
		//
		bool direction = true;//alphabetically next
		while(vectorIt!=nameList.end()-1){
			if(direction) {
				vectorIt++;
				c = community[findIndex(community,(*vectorIt))];
			}
			else {
				vectorIt--;
				c = community[findIndex(community,(*vectorIt))];
			}
			if (c->isAlive) return c;
			if (vectorIt==nameList.end()-1 && direction){
				direction = false;
				vectorIt = nameList.begin() + index;
				c = community[findIndex(community,(*vectorIt))];
			}
		}
	}
	return NULL;
}


string printer(ostream &out,const vector<Character*> &v){

	for (auto element : v)
	{
		out << "printer"  << element->name << element->isAlive << endl;
	}
}