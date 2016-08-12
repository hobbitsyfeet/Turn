#ifndef CHART_H
#define CHART_H

//#include "unit.h"
//#include "turn.h"
#include <vector>
using namespace std;

class Chart{
	private:

		class container{
			friend class Chart;
		public:
			//container();
		//contains
			//bool canEnter(int,int);
			bool checkAvailable();
			bool getOccupance();
			char getGeoType();
			void displayType();
			int getPosX();
			int getPosY();
			string getLink();
		private:
			int posX, posY;
			bool occupied;
			char geoType;
			string link;
	};
	//2D vector
	vector< vector<container> > world;
	string worldName;


	bool fogOfWar;
	int chartWidth;
	int chartHeight;

	string chartName;
	public:

	Chart(string = "Farm_Yard",int=32, int=32, bool=0);
	void displayWorld();
	void loadWorld(string);
	void saveWorld(string);
	bool canEnter(int,int);
	void setSpawn(char, int&, int&);
	void displayRange(int, int,int);

	void isPortal(int,int,bool&);
	void findPath(int,int,int,int);

	bool getFogOfWar();
	bool setFogOfWar();

	string getChartName();
	void setChartName(string);


	//void playWorld();
};

#endif
