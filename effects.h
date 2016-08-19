#ifndef ABILITIES_H
#define ABILITIES_H


#include "item.h"
#include "unit.h"


class Ablility{
 public:

  string getName();
  string getDescription();

  int getLevel();
  int setLevel();

  char getType();
  //previous tree(maybe)

  void affectItem(*f(),Item&);
  void affectUnit(*f(),Unit&);

  void damageMultiplier();
  void


  void
 private:
  //information
  string name;
  string description;

  //multiplier
  int level;

  //passive or active
  char passivness;
  int activeLength;

};

#endif
