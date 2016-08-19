#ifndef UNIT_H
#define UNIT_H
#include "unit.h"
#include "item.h"
#include "inventory.h"
#include <iostream>
#include <vector>
using namespace std;

class Unit{

private:
	//*****Unit stats*****

	string name;
	int health;
	int maxHealth;
	int stamina;
	int attack;
	int range;
	int defence;
	int gold;
	int maxExperience;
	int experience;
	int level;
	int dice;

	//Equipped items
	bool leftHand;
	bool rightHand;
	bool head;
	bool torso;
	bool legs;
	bool feet;

	string currentWorld;

public:
//CONSTRUCTORS
				//name,level,health,attack
	Unit(string="NoName", int=1,int =15,int=15,int=2, int=0,int =1,
	int=0,int=45, int=0,int=0, int = 6, int =28, int=20,
	bool=0,bool=0,bool=0,bool=0,bool=0,bool=0,
	string = "Farm_Yard");

//*******Map_Position********
	int posX;
	int posY;
	void getPos();
	int getPosX();
	int getPosY();
	//void distanUnit();

//********I/O_Files************
	void loadUnit(string);//
	void saveUnit(string);//

//************get stats*********
	int rollDice();

	void setName(string);
	string getName()const;//
	int getLevel()const;//
	int getMaxExp()const;
	int getExp()const;//
	int getRange()const;
	int getMaxHealth()const;
	int getHealth()const;//
	int getDefence()const;//
	int getAttack()const;//
	int getGold()const;//
	int getStamina()const;//

	string getCurrentWorld();
	void setCurrentWorld(string);

	void displayStats();

	void levelUp();
//***********COMBAT*************
	void attackUnit(Unit&);//
	int distanceTo(const int, const int);



//*********Inventory************
/*
	struct inventory{
  	//main container for inventory
  	vector<Item> invContainer;

  	void loadInventory(string);//
  	void saveInventory(string);//
	  //functions for inventory
  	void pickUp(Item);//
 	 	void dropItem(Item);
 	 	bool search(const Item);//
 	 	bool searchWeaponEquipped();
 	 	Item& getItemEquipped();
 	 	Item getSearch(Item);

 	 	inventory& operator = (const inventory&);

	};

	*/

	//Unit's own inventory and function to display
	Inventory inv;
	void displayInv();//
	void lootUnit(string,Unit&);


//******get Equipment***********
//need to pass these
	void unEquipItem(string);
	void equipItem(string);//
	bool leftHandEquipped;
	bool rightHandEquipped;
	bool headEquipped;
	bool torsoEquipped;
	bool legsEquipped;
	bool feetEquipped;
	//************Operators************
	Unit& operator = (const Unit&);//

	friend ostream& operator << (ostream&, const Unit&);
	friend istream& operator >> (istream&, Unit&);

};	//end of Unit
#endif
