#ifndef CHART_H
#define CHART_H

//#include "unit.h"
//#include "turn.h"
#include "item.h"
#include <vector>
using namespace std;

class Inventory{
public:
vector<Item> invContainer;

  void loadInventory(string);//
  void saveInventory(string);//

	//functions for inventory
  	void pickUp(Item);//
  	void displayInv();
 	 	void dropItem(Item);
 	 	bool search(const Item);//
 	 	bool searchWeaponEquipped();
 	 	Item& getItemEquipped();
 	 	Item getSearch(Item);


private:

Inventory& operator = (const Inventory&);//

};

#endif