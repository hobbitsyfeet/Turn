#include "inventory.h"
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
//Function:displayInv
//prints out every item in Inventory
void Inventory::displayInv(){
  vector<Item>::iterator it;
  cout<<"===============Inventory==============="<<endl;
  for(it= invContainer.begin(); it< invContainer.end(); it++){
    cout<<"- ";
    it->viewItem();
  }
  cout<<"=======================================";
}

//NOT DONE
void Inventory::pickUp(Item a){
    invContainer.push_back(a);
}
//NOT DONE
void Inventory::dropItem(Item a){
   a.itemUnequip();
}

//***********FILE************
//Function: saveInventory
//similar to save Unit
//prints unit's Inventory to file
void Inventory::saveInventory(string unitName){
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
//pushes it into Unit's Inventory
void Inventory::loadInventory(string unitName){
  Item temp;
  ifstream fin;
  fin.open(("./saves/" + unitName +"Inv").c_str());
  //for each item in file get stats and overwrite temp
  while(!fin.eof()){
    fin>>temp;
    //push into Inventory
    pickUp(temp);
  }
  fin.close();
}


bool Inventory::searchWeaponEquipped(){
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

Item Inventory::getSearch(Item iSearch){
  vector<Item>::iterator it;
  for(it=invContainer.begin(); it< invContainer.end(); it++){
    if (*it == iSearch)
      return *it;
  }
  return *it;
  cout<<"test";
}

Item& Inventory::getItemEquipped(){

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

void Inventory::sortInv(){

}

Inventory& Inventory::operator= (const Inventory& i){
  invContainer = i.invContainer;
  return *this;
}
