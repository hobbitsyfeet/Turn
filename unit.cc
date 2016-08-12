#include "unit.h"
#include "item.h"
//#include "inventory.h"
#include <cmath>
//#include <ifstream>
//#include <ofstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;
//default constructor
Unit::Unit(string Name,int Level, int Health,int MaxHealth,int Attack,int Range,int Defence,
	int Exp, int MaxExp, int Gold, int Stam, int Dice, int xpos, int ypos,
bool lEquip, bool rEquip, bool hEquip,bool tEquip, bool legEquip, bool ftEquip,
 string cWorld){
  name=Name;
  level = Level;

  health=Health;
  maxHealth=MaxHealth;

  attack=Attack;
  range=Range;
  defence=Defence;

  gold=Gold;

  experience=Exp;
  maxExperience = MaxExp;
  stamina = Stam;
  dice = Dice;

  posX = xpos;
  posY = ypos;


//need to pass in or else will always spawn with empty items, thus will enable equiping multiple items.
	leftHandEquipped = lEquip;
	rightHandEquipped =rEquip;
  torsoEquipped = tEquip;
	headEquipped =hEquip;
	legsEquipped =legEquip;
	feetEquipped =ftEquip;

  currentWorld = cWorld;

}

//*******STATS*********
  int rollDice(int dice){
    return (rand() % dice) +1;
  }

//Functions:Getters
//returns individually values of stats
void Unit::setName(string input){
  name = input;
}
string Unit::getName()const{
  return name;
}
int Unit::getLevel()const{
	return level;
}
int Unit::getMaxHealth()const{
  return maxHealth;
}
int Unit::getHealth()const{
  return health;
}
int Unit::getStamina()const{
  return stamina;
}
int Unit::getAttack()const{
  return attack;//add to item damage
}
int Unit::getRange()const{
  return range;
}
int Unit::getDefence()const{
  return defence;
}
int Unit::getGold()const{
  return gold;
}
int Unit::getMaxExp()const{
  return ( ((level)*(level)) + (22*(level)) +(22) );
}
int Unit::getExp()const{
  return experience;
}
int Unit::getPosY(){
	return posY;
}
int Unit::getPosX(){
	return posX;
}

string Unit::getCurrentWorld(){
  return currentWorld;
}

void Unit::setCurrentWorld(string input){
  currentWorld = input;
}

void Unit::levelUp(){
  if(experience >= maxExperience){
    //increases level
    level++;
    //resets exp starting from 0+excess experience
    experience -= maxExperience;
    //increase maxExperience with equation y=(x^2)+(22x)+22
    maxExperience = ( ((level)*(level)) + (22*(level)) +(22) );

    maxHealth++;
    if(level %3 ==0){
      maxHealth++;
    }
    if(level%5 == 0){
      maxHealth++;
    }
    if(level%10 == 0){
      attack++;
      defence++;
      dice++;
    }
  }
}
//Function:displayStats
//prints out status of Unit in an in-line order
void Unit::displayStats(){
  cout<<"==============STATS=============="<<endl;
  cout<<setfill(' ');
  cout<<"NAME:"<<name<<" x:"<<posX<<" y:"<< posY<<endl;
  cout<<"Health:"<<health<<'/'<<left<<setw(14)<<maxHealth<<"Experience:"<<experience<<endl;
  cout<<"Attack:"<<left<<setw(17)<<attack<<"Defence:"<<defence<<endl;
  cout<<setfill('=')<<setw(35)<<"==";
}

//**********COMBAT************

//Function:attackUnit
//passes in another unit and does damage accordingly
void Unit::attackUnit(Unit& target){
  int totalDamage = (this->getAttack()-target.getDefence());
  Item* equipmentUsed;

  //if in range, engage
  if(this->getRange() >= distanceTo( target.getPosX(),target.getPosY() ) ){
		cout<<"inrange"<<endl;
    //if not dead, attack
    if(target.getHealth() > totalDamage){
			cout<<"target not dead"<<endl;
      if(inv.searchWeaponEquipped()){
        //getEquipped Weapon
        equipmentUsed = &inv.getItemEquipped();
				cout<<"i got a weapon"<<endl;
        //if weapon's durability
        if(equipmentUsed->itemGetDurability() > 0){
        //if the total damage is positive
				cout<<"my damage is greater than his defence"<<endl;
         if(totalDamage > 0){
          //do damage
					cout<<"target hit!"<<endl;
              target.health -= totalDamage;
              equipmentUsed->decrementDurability();
          //decrement item's durability
          }
          //no damage inflicted
          else{
          cout<<this->getName()<<" dealt 0 damage to"<< target.getName();
          }
        }
        //the item is broken
        else{
          totalDamage = 1;
          cout<<equipmentUsed->itemGetName()<<" is broken! "<<endl;
          target.health -= totalDamage;
       }
         //show results
        cout<<this->getName()<<" dealt "
	       <<totalDamage
	       <<" damage to "<<target.getName();
      }
       //save b/c stat change
      target.saveUnit(target.getName());
   }

    //they are dead, announce and do no action
    else{
      if(target.getHealth() != 0){
				target.saveUnit(target.getName());
        target.health = 0;
        experience += target.getExp();
        cout<<"you killed "<<target.getName()<<" and gained"<<target.getExp()<<" experience."<<endl;
        if(experience >= maxExperience)
          this->levelUp();
      }
      else
        cout<<target.getName()<<" is dead";
    }
  }
  else{
    cout<<"Not in range";
  }
}

//Function:lootUnit
//will access another unit's inventory
void Unit::lootUnit(string iName,Unit& target){
  if(iName == "Fists"){
    cout<<"You cannot yet remove hands";
    return;
  }
  if(distanceTo(target.getPosX(),target.getPosY() ) <= 1){
  vector<Item>::iterator it;
  for(it=target.inv.invContainer.begin();it<target.inv.invContainer.end();it++){
      if(iName == it->itemGetName()){
       it->itemUnequip();
			 this->unEquipItem(iName);
			 inv.pickUp(*it);
       target.inv.invContainer.erase(it);
      }
    }
    cout<<"You grabbed "<<iName;
  }
  else{
    cout<<"Cannot loot"<<target.getName();
    if(distanceTo(target.getPosX(),target.getPosY() ) > 1 ){
      if(target.getHealth() > 0)
        cout<<" is still alive, cannot grab his things just yet!";
      else
        cout<<" is too far";
    }
  }
}

//Fucntion:distanceUnit
//passes in another unit and returns the distance from current
//using 'distance between two points' equation
int Unit::distanceTo(const int targetX, const int targetY){
  int dist;
  //distance between 2 points
  dist = sqrt( ( (targetX - this->getPosX())*(targetX - this->getPosX()) )
    +  ( targetY - this->getPosY())*(targetY - this->getPosY()) );
  //because distance cannot be negative
  if(dist< 0)
    return -(dist);
  else
    return dist;
}

//Function:getPos
//neatly displays  x and y position
void Unit::getPos(){
  cout<<posX<<','<<posY;
}


//***********EQUIPMENT*********

//Function:equipItem
//Searches for an item in inventory
//applies stats to unit and
//applies boolean 'equipped' according to item type
void Unit::equipItem(string i){
	cout<<"entering equipitem"<<endl;
	cout<<"searching for "<<i<<endl;
  vector<Item>::iterator it;
  bool didEquip=false;
int j=1;
  for(it=inv.invContainer.begin(); it< inv.invContainer.end() /*|| it->itemGetName() == i*/; it++){
		cout<<it->itemGetName()<<it->itemGetType()<<endl;
		cout<<leftHandEquipped<<rightHandEquipped<<endl;
    if(it->itemGetName() == i){
      if(it->itemGetType() == "Right-Hand" && rightHandEquipped == false){
	rightHandEquipped = true;
	didEquip = true;
      }
      else if(it->itemGetType() == "Left-Hand" && leftHandEquipped == false){
	leftHandEquipped = true;
	didEquip = true;
      }
      else if(it->itemGetType() == "Two-Hands" && leftHandEquipped == false && rightHandEquipped == false ){
	leftHandEquipped = true;
	rightHandEquipped = true;
	didEquip = true;
      }
      else if(it->itemGetType() == "Helmet" && headEquipped == false){
	headEquipped = true;
	didEquip = true;
      }
      else if(it->itemGetType() == "Body-Armour" && torsoEquipped == false){
	torsoEquipped = true;
	didEquip = true;
      }
      else if(it->itemGetType() == "Leggings" && legsEquipped == false){
	legsEquipped = true;
	didEquip = true;
      }
      else if(it->itemGetType() == "Boots" && feetEquipped == false){
	feetEquipped = true;
	didEquip = true;
      }
			cout<<"preforming changes"<<endl;
      if(didEquip == true){
        cout<<i<<" equipped";
	      attack += it->itemGetDamage();
      	range += it->itemGetRange();
        defence += it->itemGetDefence();
        it->itemEquip();
        break;
      }
    }
  }
}

//Function:equipItem
//INVERSE OF "equipItem"
//Searches for an item in inventory
//un-applies stats to unit and
//applies boolean 'equipped' according to item type
void Unit::unEquipItem(string i){
  vector<Item>::iterator it;
  bool didEquip = false;
  for(it=inv.invContainer.begin(); it< inv.invContainer.end(); it++){
    if(it->itemGetName() == i){
      if(it->itemGetType() == "Right-Hand" && rightHandEquipped == true){
	rightHandEquipped = false;
	didEquip = true;
      }
      else if(it->itemGetType() == "Left-Hand" && leftHandEquipped == true){
	leftHandEquipped = false;
	didEquip = true;
      }
      else if(it->itemGetType() == "Two-Hands" && rightHandEquipped == true && leftHandEquipped == true){
	rightHandEquipped = false;
	leftHandEquipped = false;
	didEquip = true;
      }
      else if(it->itemGetType() == "Helmet" && headEquipped == true){
	headEquipped = false;
	didEquip = true;
      }
      else if(it->itemGetType() == "Body-Armour" && torsoEquipped == true){
	torsoEquipped = false;
	didEquip = true;
      }
      else if(it->itemGetType() == "Leggings" && legsEquipped == true){
	legsEquipped = false;
	didEquip = true;
      }
      else if(it->itemGetType() == "Boots" && feetEquipped == true){
	feetEquipped = false;
	didEquip = true;
      }
      if(didEquip == true){
	cout<<i<<" un-equipped";
	attack -= it->itemGetDamage();
  range -= it->itemGetRange();
	defence -= it->itemGetDefence();
	it->itemUnequip();
  break;
      }
      else
	cout<<"Could not un-equip "<<i;
    }
  }
}

//***********FILE************

//Function:loadUnit
//INVERSE OF saveUnit
//receives unit information from external FILE
void Unit::loadUnit(string file){
  ifstream fin;
	string temp ="./saves/" + file;
  fin.open(temp.c_str());
  while(fin.fail()){
    cout<<"invalid player, enter a name>> ";
    cin>>file;
    fin.open(("./saves/" + file).c_str());
  }
  fin>>*this;
  fin.close();
  inv.loadInventory(file);
  cout<<"unit Loaded";
}

//Function:saveUnit
//INVERSE OF loadUnit
//writes unit information to external file
void Unit::saveUnit(string file){
  this->name = file;
  ofstream fout;
  fout.open(("./saves/" + file).c_str());
  fout<<*this;
  fout.close();
  inv.saveInventory(file);
  cout<<"unit saved\n";
}


//***************OPERATORS*******************

//assignment operator for unit
Unit& Unit::operator= (const Unit& i){
  name = i.name;
  health = i.health;
  maxHealth = i.maxHealth;
  stamina = i.stamina;
  attack = i.attack;
  range = i.range;
  defence = i.defence;
  gold = i.gold;
  experience = i.experience;
  maxExperience = i.maxExperience;
  dice = i.dice;
  leftHandEquipped = i.leftHandEquipped;
  rightHandEquipped = i.rightHandEquipped;
  torsoEquipped = i.torsoEquipped;
  legsEquipped = i.legsEquipped;
  feetEquipped = i.feetEquipped;
  posX = i.posX;
  posY = i.posY;
  currentWorld = i.currentWorld;
  inv = i.inv;
  return *this;
}

//IO operators
ostream& operator << (ostream& oStr, const Unit& i){
  oStr<<i.name<<' '<<i.level<<' '<<i.health<<' '<<i.maxHealth<<' '<<i.stamina<<' '<<i.attack<<' '<<i.range<<' '<<i.defence<<' '<<i.gold<<' '<<i.experience<<' '<<i.maxExperience<<' '<<i.dice<<' ';
  oStr<<i.leftHandEquipped<<' '<<i.rightHandEquipped<<' '<<i.headEquipped<<' '<<i.torsoEquipped<<' '<<i.legsEquipped<<' '<<i.feetEquipped<<' ';
  oStr<<i.posX<<' '<<i.posY<<' ';
  oStr<<i.currentWorld<<' ';
  return oStr;
}

istream& operator >> (istream& iStr, Unit& i){
  iStr>>i.name>>i.level>>i.health>>i.maxHealth>>i.stamina>>i.attack>>i.range>>i.defence>>i.gold>>i.experience>>i.maxExperience>>i.dice;
  iStr>>i.leftHandEquipped>>i.rightHandEquipped>>i.headEquipped>>i.torsoEquipped>>i.legsEquipped>>i.feetEquipped;
  iStr>>i.posX>>i.posY;
  iStr>>i.currentWorld;
  return iStr;
}
//************************************************************************
//************************************************************************
//************************INVENTORY FUNCTIONS*****************************
//************************************************************************
//************************************************************************



//Function:displayInv
//prints out every item in inventory
void Unit::displayInv(){
  vector<Item>::iterator it;
  cout<<"===============INVENTORY==============="<<endl;
  cout<<"GOLD:"<<gold<<endl;
  for(it=inv.invContainer.begin(); it< inv.invContainer.end(); it++){
    cout<<"- ";
    it->viewItem();
  }
  cout<<"=======================================";
}

//NOT DONE
void Unit::inventory::pickUp(Item a){
    invContainer.push_back(a);
}
//NOT DONE
void Unit::inventory::dropItem(Item a){
   a.itemUnequip();
}

//***********FILE************
//Function: saveInventory
//similar to save Unit
//prints unit's inventory to file
void Unit::inventory::saveInventory(string unitName){
  Item temp;
  vector<Item>::iterator it;
  ofstream fout;
  //open file at destination
	remove(("./saves/" + unitName +"Inv").c_str());
  fout.open(("./saves/" + unitName +"Inv").c_str());
  for(it=invContainer.begin(); it< invContainer.end(); it++){
    if(it+1 != invContainer.end())
      fout<<*it<<endl;
    else
      fout<<*it;
  }
  fout.close();
}

//Function:loadInventory
//Gets stats individually from file
//creates an item with those stats
//pushes it into Unit's inventory
void Unit::inventory::loadInventory(string unitName){
  Item temp;
  ifstream fin;
  fin.open(("./saves/" + unitName +"Inv").c_str());
  //for each item in file get stats and overwrite temp
  while(!fin.eof()){
    fin>>temp;
    //push into inventory
    pickUp(temp);
  }
  fin.close();
}


bool Unit::inventory::searchWeaponEquipped(){
  vector<Item>::iterator it;

  for(it=invContainer.begin(); it< invContainer.end(); it++){
    if(it->itemGetType() == "Right-Hand" && it->itemGetEquipped() == true){
      return true;
    }
    else if(it->itemGetType() == "Left-Hand" && it->itemGetEquipped() == true){
       return true;
    }
    else if(it->itemGetType() == "Two-Hands" && it->itemGetEquipped() == true){
        return true;
    }
  }
  return false;
}

Item Unit::inventory::getSearch(Item iSearch){
  vector<Item>::iterator it;
  for(it=invContainer.begin(); it< invContainer.end(); it++){
    if (*it == iSearch)
      return *it;
  }
  return *it;
  cout<<"test";
}

Item& Unit::inventory::getItemEquipped(){

    vector<Item>::iterator it= invContainer.begin();
        Item& temp=*it;
    for(it=invContainer.begin(); it< invContainer.end(); it++){

      if(it->itemGetType() == "Right-Hand" && it->itemGetEquipped() == true)
        temp = *it;
      else if(it->itemGetType() == "Left-Hand" && it->itemGetEquipped() == true)
        temp =*it;
      else if(it->itemGetType() == "Two-Hands" && it->itemGetEquipped() == true)
        temp= *it;
  }
  return temp;
}

Unit::inventory& Unit::inventory::operator = (const inventory& i){
 vector<Item>::const_iterator it = i.invContainer.begin();
  for(it=invContainer.begin(); it< invContainer.end(); it++){
    this->pickUp(*it);
  }
}