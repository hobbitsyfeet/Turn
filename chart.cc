
#include <vector>
#include <fstream>
//#include <ifstream>
//#include <ofstream>
#include <iostream>
#include <cmath>
#include "chart.h"

#include <vector>
using namespace std;

Chart::Chart(string ChartName,int ChartWidth, int ChartHeight, bool FoW){
	chartWidth = ChartWidth;
	chartHeight = ChartHeight;
	fogOfWar = FoW;
	worldName = ChartName;
}


void Chart::loadWorld(string name){
	//INITIALISATION
	vector<vector<container> >::iterator row;
	vector<container>::iterator col;
	//type of block to set it as
	container block, block_reset;
	char inChar;
	int x, y, i;
	int posXPortal = 0,posYPortal = 0,numPortal;
	string option ="";
	//END OF INITIALIZATION;
	//set name of loaded world
	//this->worldName = name;

	ifstream fin;
	fin.open(("./maps/" + name + ".txt").c_str());

	//Prevent crash by selecting an existing file
	while(fin.fail()){
		cout<<"invalid file, enter a file>> ";
		cin>>name;
		fin.open(("./maps/" + name + ".txt").c_str());
	}

		cout<<"Loading map..."<<endl;
	this->worldName = name;
	fin>>x>>y;

	//creates 2D vector of size x,y
	world.clear();
	world.resize(x, vector<container>(y));

	fin>>fogOfWar;
	//number or portals in a map
	option="";
	fin>>numPortal;
	//arrays for multiple portals
	int portalx [numPortal];
	int portaly [numPortal];
	string *portalNames = new string[numPortal];

	//setting portal name and coords into arrays
	for(int i = 0; i<numPortal; i++){
		fin>>posXPortal>>posYPortal>>option;
		portalx[i] = posXPortal;
		portaly[i]=posYPortal;
		portalNames[i] = option;
	}
	// MAP LOADS	//
	//->			//
	//   ->			//
	//		->		//
	//			->	//

	//iterates through and sets type
	//start on the left
	x=1;
	//when reach end of row, go to next, top left
	for(row = world.begin(); row < world.end() ; row++){
		//on each row, go through each column left to right
		for(col = row->begin(); col< row->end(); col++){
			//gets type
			fin.ignore();
			fin>>block.geoType;
			if(block.checkAvailable()==true)
				block.occupied=false;
			else
				block.occupied=true;

			//portal
			//the for loop iterates through portal list
			//so no need to care for initialization order (top left to bottom right)
			for(int i = 0; i<numPortal; i++){
				if( (portalx[i] == x) && (portaly[i] == y) ){
					block.link = portalNames[i];
					//dont know why i++ here fixes it but it does...?
					i++;
				}
				else{
					block.link = "";
				}
			}
			block.posX = x;
			block.posY = y;
			//assign the map iterator to
			*col= block;
			block = block_reset;

			//move to next column
			x++;
		}
		//start at first column
		x=1;
		//move down a row
		y--;
	}
	delete [] portalNames;
	fin.close();
	cout<<"Done Loading."<<endl;

}



void Chart::displayWorld(){
	vector<vector<container> >::iterator row;
	vector<container>::iterator col;
	for(row = world.begin(); row < world.end() ; row++){
		for(col = row->begin(); col < row->end(); col++){
			if(col->getGeoType()=='-' || col->getGeoType() =='O')
				cout<<"  ";
			else{
				col->displayType();
				cout<<' ';
			}
		//cout<<col->getOccupance();
		//	cout<<col->getLink();
		}
		cout<<endl;
	}
}

void Chart::displayRange(int centrePosX,int centrePosY, int radius){

	vector<vector<container> >::iterator row;
	vector<container>::iterator col;
	int dist;
	for(row = world.begin(); row < world.end() ; row++){
		for(col = row->begin(); col < row->end(); col++){
 			 dist = sqrt( ( (col->getPosX() - centrePosX)*(col->getPosX() - centrePosX) )
   		 + 	 ( col->getPosY() - centrePosY)*(col->getPosY() - centrePosY) );



  		if(getFogOfWar()){
  			if(dist <= radius){
  			if(centrePosX == col->getPosX() && centrePosY == col->getPosY())
  			cout<<"P ";
  			else{
					if(col->getGeoType()=='-' || col->getGeoType() =='O')
						cout<<' ';
					else
						col->displayType();
					cout<<' ';
				}
			}
				else
					cout<<"- ";
		}
		else{
			if(centrePosX == col->getPosX() && centrePosY == col->getPosY())
  			cout<<"P ";

  			else{
				if(col->getGeoType()=='-' || col->getGeoType() =='O')
					cout<<"  ";
				else{
					col->displayType();
					cout<<' ';
					}
				}
			}
		}
		cout<<endl;
	}
}

bool Chart::canEnter(int x, int y){
	vector<vector <container> >::iterator row = world.end()-y;
	vector<container> ::iterator col = row->begin()+x-1;
	//cout<<col->getPosX()<<','<<col->getPosY()<<endl;
	if(col->getOccupance() == false){
		//cout<<"allowed to enter"<<endl;
		return false;
	}
	else return true;
}

void Chart::setSpawn(char spawnPt, int& x, int&y){
	vector<vector <container> >::iterator row;
	vector<container> ::iterator col;
	for(row = world.begin(); row < world.end(); row++){
		for(col = row->begin(); col< row->end(); col++){
			if(spawnPt == col->getGeoType()){
				x = col->getPosX();
				y = col->getPosY();
				return;
			}
		}
	}
}

void Chart::findPath(int initX,int initY, int finX, int finY){
	//initialize
	vector<vector <container> >::iterator row = world.end()-initY;
	vector<container> ::iterator col = row->begin()+initX-1;
}

void Chart::isPortal(int x,int y,bool& gotLink){
	//cout<<"starting portal search"<<endl;
	vector<vector <container> >::iterator row = world.end()-y;
	vector<container> ::iterator col = row->begin()+x-1;
	//cout<<col->getPosX()<<col->getPosY()<<col->getLink();
	if(col->getLink() != ""){
		gotLink = true;
		this->loadWorld(col->getLink().c_str());
	//	cout<<"going to"<< col->getLink()<<endl;
	}
}

bool Chart::getFogOfWar(){
	return fogOfWar;
}

void Chart::container::displayType(){
	cout<<geoType;
}

char Chart::container::getGeoType(){
	return geoType;
}
bool Chart::container::getOccupance(){
	return occupied;
}
int Chart::container::getPosX(){
	return posX;
}
int Chart::container::getPosY(){
	return posY;
}
string Chart::container::getLink(){
	return link;
}
string Chart::getChartName(){
	return worldName;
}
void Chart::setChartName(string input){
	worldName = input;
}
bool Chart::container::checkAvailable(){
	//if not occupied check if terrain is accessible
	//if(this->getOccupance() == false)
		switch(this->getGeoType()){
			case'!':
			case'=':
			//case'@':
			case'$':
			case'%':
			case'^':
			case'&':
			case'*':
			case'~':
			case'#':
			case'|':
			case'_':
			case'/':
			return false;
				break;
			default:
				return true;
		}
		//else return false;
}
