#ifndef TURN_H
#define TURN_H

#include "unit.h"
#include "chart.h"
//#include "item.h"

class Turn{
	//friend class Chart;
 public:
  void run(string);
 private:
	void attackTarget();
	void lootTarget();
	void movePlayer(Unit&, Chart&);
	void welcomeBanner(string);
 	Unit player;
 	//Not pointer because Unit will not be Loaded during turn.
 	//only access and modify stats saved in file, then loaded up for next unit.
  Unit target;
};


#endif
