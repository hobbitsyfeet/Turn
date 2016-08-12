//*********************
//main
//control for the program
//*********************

//#include "menu.h"
#include "turn.h"
#include "chart.h"
#include "unit.h"
#include "inventory.h"
#include <iostream>
#include <fstream>
#include <iomanip>

void welcome(string);
string getPlayer();
using namespace std;


int main(){

	//took out because worlds are now player-dependent so no need to go here
 	// Chart worlds;
  Turn playerTurn;
  string option;
  int numPlayers, i;//initialize i for importance to keep value from for loop

  //start
  welcome("banners/banner.txt");
  cout<<"How many players?";
  cin>>numPlayers;

  	//clear screen<< turn
    cout << "\x1B[2J\x1B[H";
	welcome("banners/banner.txt");

  //create array of number of players
  string playerList[numPlayers];

  //place players into array
  for( i = 0;  i< numPlayers; i++){
  	cout<<"player"<<(i+1)<<',';
  	playerList[i] = getPlayer();
  }

  //clear screen<< turn
 	cout << "\x1B[2J\x1B[H";
	welcome("banners/banner.txt");

  //cout<<entering run
	do{
   		for( i = 0;  i< numPlayers; i++)
		  		playerTurn.run(playerList[i]);
	  		if(numPlayers != 1){
				cout<<"continue?\n";
				cin>>option;
			}
	}
	while(option == "yes");

cout<<"Good Bye!";
return 0;
}


string getPlayer(){
	Unit tempPlayer;
	string option="";

	// create a new or load an already created player
	while (option != "load" && option !="new" ){
	cout<<"new or load>>"<<endl;
	cin>>option;
	if(option != "load" && option !="new" )
		cout<<"try again:\n";
	}

	// new player writes file and uses it
	if(option == "new"){
		cout<<"who? >>";
		cin>> option;
		tempPlayer.setName(option);
		//writes files to load later
		tempPlayer.saveUnit(option);
	}
	//uses an already existing file
	else if(option == "load"){
		cout<<"who? >>";
		cin >> option;
	}
	return option;
}


void welcome(string input){
char block;
ifstream fin;
fin.open(input.c_str());
	while(!fin.eof()){
	fin>>block;
		if(block == '!')
			cout<<'\xDC';
		else if(block == '#')
			cout<<'\xDB';
		else if (block == '@')
			cout<<'\xB2';
		else if(block == '-')
			cout<<' ';
		else if(block == '^')
			cout<<'\xB1';
		else if(block =='%')
			cout<<'\xB0';
		else if(block == '$')
			cout<<'\xDF';
		else if(block ==',')
			cout<<'\xB3';
		else if (block == 'e')
			cout<<'\n';
	}
}
