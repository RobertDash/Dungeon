#include <iostream>
#include "windows.h"
#include <ctime>
#include <string>
#include <cstdlib>

using namespace std;

const int Rows = 10;
const int Cols = 10;
const int trap = 3;
const int monster = 3;
const int monstermove = 3;
int step = 0;

int monsterPositions[monster][2];
int trapPosition[trap][2];
int userPosition[2];
int treasurePosition[2];
bool isGameEnd = false;

void printDungeon(char map[Rows][Cols]);
void monstermovement(char map[Rows][Cols]);
void playermovement (char map[Rows][Cols], char userInput);

int main()
{
	srand(time(NULL));

	char map[Rows][Cols];
	char userInput;
	for (int x=0; x<Rows; x++)
	{
		for (int y=0; y<Cols; y++)
		{
			map[x][y] = '.';
		}
	}
	cout<<"You are agent 'G', 'X' marks the spot."<<endl;
	cout<<"Beware of 'M'onsters and 'T'raps."<<endl;
	cout<<"WASD input for movement."<<endl;
	for(int i=0; i<monster; i++)
	{
	RandomizeMonsters:
		int x=rand()%Rows;
		int y=rand()%Cols;
		while(x+monstermove>Rows || x-monstermove<0)
		{
			x=rand()%Rows;
		}
		while(y+monstermove>Cols || y-monstermove<0)
		{
			y = rand()%Cols;
		}
		if(map[x][y] == 'M' || map [x+1][y] == 'M' || map [x-1][y] == 'M' || map [x][y+1] == 'M' || map [x][y-1] == 'M')
		{
			goto RandomizeMonsters;
		}
		map[x][y] = 'M';
		monsterPositions[i][0] = x;
		monsterPositions[i][1] = y;
	}
	for(int i=0; i<trap; i++)
	{
		RandomizeTraps:
			int xTrap = rand()%Rows;
			int yTrap = rand()%Cols;
					if (map[xTrap][yTrap] == 'M')
					{
						xTrap = rand()%Rows;
						yTrap = rand()%Cols;
					}
			trapPosition[i][0]=xTrap;
			trapPosition[i][1]=yTrap;
			map[xTrap][yTrap] = 'T';
	}
	int xTar = rand()%Cols;
	do
	{
		xTar = rand()%Cols;
	}while(map[0][xTar] == '0' || map[0][xTar] == 'M' || map[0][xTar] == 'T');
	map[0][xTar] = 'G';
	userPosition[0] = 0;
	userPosition[1] = xTar;
	do
	{
		xTar = rand()%Cols;
	}while(map[Rows-1][xTar] == '0' ||	map[Rows-1][xTar] == 'M' ||	map[Rows-1][xTar] == 'G' ||	map[Rows-1][xTar] == 'T');
	map[Rows-1][xTar] = 'X';
	treasurePosition[0] = Rows-1;
	treasurePosition[1] = xTar;
	printDungeon(map);
	
	while (isGameEnd == false)
	{
		for(int i=0; i<trap; i++)
		{
			map[trapPosition[i][0]][trapPosition[i][1]];
		}
		monstermovement(map);
		playermovement(map,userInput);
		if(map[treasurePosition[0]][treasurePosition[1]] == 'G')
		{
			map[treasurePosition[0]][treasurePosition[1]] = 'Y';
			cout<<"You found the treasure!"<<endl;
			isGameEnd = true;
		}
		printDungeon(map);
	}
	system("PAUSE");
	return 0;
}
void monstermovement (char map[Rows][Cols])
{
	if (step<=2 && step >=0)
	{
		for(int i=0; i<monster; i++)
		{
			if(monsterPositions[i][1]+1<Cols)
			{
				monsterPositions[i][1]++;
				map[monsterPositions[i][0]][monsterPositions[i][1]-1]='.';
				map[monsterPositions[i][0]][monsterPositions[i][1]]='M';
			}
		}
	}
	
	else if(step<=5 && step>=3)
	{
		for(int i=0; i<monster; i++)
		{
			if(monsterPositions[i][1]-1>0)
			{
				monsterPositions[i][1]--;
				map[monsterPositions[i][0]][monsterPositions[i][1]+1]='.';
				map[monsterPositions[i][0]][monsterPositions[i][1]]='M';
			}
		}
	}
	step++;
	if(step>5)
	{
		step =0;
	}
}
void playermovement(char map[Rows][Cols], char userInput)
{
	PlayerMove:
		cout<<"Please give a direction input"<<endl;
		cin>>userInput;
		cout<<endl;
		cout << string(10, '\n');
		//! blank previous placement
		map[userPosition[0]][userPosition[1]] = '.';
		//! Up
		if(userInput == 'W' || userInput == 'w')
		{
			if (userPosition[0]-1<0)
			{
				map[userPosition[0]][userPosition[1]]= 'G';
				cout<<"You are hitting a wall. Please try again."<<endl;
				goto PlayerMove;
			}
			else if(map[userPosition[0]-1][userPosition[1]]=='T')
			{
				map[userPosition[0]-1][userPosition[1]]= '*';
			cout<<"You got trapped, when it is obviously there."<<endl;
				isGameEnd = true;
			}
			else if(map[userPosition[0]-1][userPosition[1]]=='M')
			{
				map[userPosition[0]-1][userPosition[1]]= '*';
				cout<<"You ran into a monster, it is obviously there."<<endl;
				isGameEnd = true;
			}
			else if(userPosition[0]-1>=0)
			{
				map[userPosition[0]][userPosition[1]] = '.';
				userPosition[0]--;
				map[userPosition[0]][userPosition[1]] = 'G';
			}
		}
		else if(userInput == 'S' || userInput == 's')
		{
			if (userPosition[0]+1>9)
			{
				map[userPosition[0]][userPosition[1]]= 'G';
				cout<<"You are hitting a wall. Please try again."<<endl;
				goto PlayerMove;
			}
			else if(map[userPosition[0]+1][userPosition[1]]=='T')
			{
				map[userPosition[0]+1][userPosition[1]]= '*';
				cout<<"You got trapped, when it is obviously there."<<endl;
				isGameEnd = true;
			}
			else if(map[userPosition[0]+1][userPosition[1]]=='M')
			{
				map[userPosition[0]+1][userPosition[1]]= '*';
					cout<<"You ran into a monster, it is obviously there."<<endl;
				isGameEnd = true;
			}
			else if(userPosition[0]+1<=10)
			{
				map[userPosition[0]][userPosition[1]] = '.';
				userPosition[0]++;
				map[userPosition[0]][userPosition[1]] = 'G';
			}
		}
		else if(userInput == 'A' || userInput == 'a')
		{
			if (userPosition[1]-1<0)
			{
				map[userPosition[0]][userPosition[1]]= 'G';
				cout<<"You are hitting a wall. Please try again."<<endl;
				goto PlayerMove;
			}
			else if(map[userPosition[0]][userPosition[1]-1]=='T')				{
				map[userPosition[0]][userPosition[1]-1]= '*';
				cout<<"You got trapped, when it is obviously there."<<endl;
				isGameEnd = true;
			}
			else if(map[userPosition[0]][userPosition[1]-1]=='M')
			{
				map[userPosition[0]][userPosition[1]-1]= '*';
				cout<<"You ran into a monster, it is obviously there."<<endl;
				isGameEnd = true;
			}
			else if(userPosition[1]-1>=0)
			{
				map[userPosition[0]][userPosition[1]] = '.';
				userPosition[1]--;
				map[userPosition[0]][userPosition[1]] = 'G';
			}
		}
		else if(userInput == 'D' || userInput == 'd')
		{
			if (userPosition[1]+1>9)
			{
				map[userPosition[0]][userPosition[1]]= 'G';
				cout<<"You are hitting a wall. Please try again."<<endl;
				goto PlayerMove;
			}
			else if(map[userPosition[0]][userPosition[1]+1]=='T')
			{
				map[userPosition[0]][userPosition[1]+1]= '*';
				cout<<"You got trapped, when it is obviously there."<<endl;
				isGameEnd = true;
			}
			else if(map[userPosition[0]][userPosition[1]+1]=='M')
			{
				map[userPosition[0]][userPosition[1]+1]= '*';
				cout<<"You ran into a monster, it is obviously there."<<endl;
				isGameEnd = true;
			}
			else if(userPosition[1]+1<=10)
			{
				map[userPosition[0]][userPosition[1]] = '.';
				userPosition[1]++;
				map[userPosition[0]][userPosition[1]] = 'G';
			}
		}
}
void printDungeon(char map[Rows][Cols])
{
	cout << string(2, '\n');
	cout<<"Map"<<endl;
	for(int x=0; x<Rows; x++)
	{
		for(int y=0; y<Cols; y++)
		{
			cout<<map[x][y];
		}
		cout<<endl;
	}
}
