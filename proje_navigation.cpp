#include <iostream>
#include<time.h>
#include<cmath>
using namespace std;

void BuildingNameEnlarge(char *building)
{
	switch (*building)
	{
	case 'S': cout << "School"; break;
	case 'P': cout << "Police Station"; break;
	case 'H': cout << "Hospital"; break;
	case 'U': cout << "User Current Location"; break;
	}
}

void showMap(char map[][20], int size, int *Uxcoord, int *Uycoord, char *Ucurrent)
{
	for (int i = 0; i < size + 1; i++) //map 20x20 but "X|Y 0 1 2 ... 19" is 21 xith x|y
	{
		if (i == 0) { cout << "X|Y "; }  //prints "X|Y 0 1 2 ... 19"
		else
		{
			if (i < 10) { cout << i - 1 << "  "; } //2 digits from 10 to 19
			else { cout << i - 1 << " "; }
		}
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		if (i < 10) { cout << i << "   "; } //digit problem, it writes 0...19 in the line indents   
		else { cout << i << "  "; }

		for (int j = 0; j < size; j++)
		{
			if (i == *Uxcoord && j == *Uycoord) //if we're in User current Loction
			{
				if (map[i][j] == '#') // 1)there is not a building --> print U
				{
					cout << *Ucurrent << "  ";
				}
				else                  // 2)there is a building --> print building
				{
					cout << map[i][j] << "  ";
				}
			}
			else
			{
				cout << map[i][j] << "  ";
			}
		}
		cout << endl;
	}
}

void buildingMapAssigner(char map[][20], int size, char names[], int nameSize, int buildingnumber, int *xcoord, int *ycoord)
{
	srand(time(NULL));
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			map[y][x] = '#';
		}
	}

	for (int i = 0; i < buildingnumber; i++)
	{
		xcoord[i] = rand() % size;
		ycoord[i] = rand() % size;
		int buildingchar = rand() % nameSize; // S, P or H 
		if (map[xcoord[i]][ycoord[i]] == '#')                   // if there is not a case that building conflict
		{
			map[xcoord[i]][ycoord[i]] = names[buildingchar];    // 1)assign the building in that coordinates
		}
		else { i--; }                                           // 2)i= i-1 and assign different rand coordinates and building type
	}
}

void nearestBuilding(char map[][20], int size, int *xcoord, int *ycoord, int buildingnumber)
{
	double existDistance = sqrt(pow(size, 2) + pow(size, 2)); //Max distance for the beginning 20root2
	int nearestOne[2]; //keep the coordinates of nearest
	for (int i = 0; i < buildingnumber; i++)
	{
		double distance = sqrt(pow((xcoord[i] - xcoord[buildingnumber]), 2) + pow((ycoord[i] - ycoord[buildingnumber]), 2));
		if (distance < existDistance && distance != 0)
		{
			existDistance = distance;
			nearestOne[0] = xcoord[i];
			nearestOne[1] = ycoord[i];
		}
	}
	cout << "Nearest building = ";
	BuildingNameEnlarge(&map[nearestOne[0]][nearestOne[1]]);
	cout << endl << "Location: X=" << nearestOne[0] << " Y=" << nearestOne[1];
}

void Go(char map[][20], int size, int &Xcoord, int &Ycoord);
void Info(int *xcoord, int *ycoord, char buildings[], int size);

int main()
{
	const int size = 20;
	char map[size][size];

	const int Bsize = 4;
	char building_names[Bsize] = { 'H', 'P', 'S', 'U' }; //If you want to add any building please be careful and add it BEFORE U in the building_names!!! (because in line 133)

	int howManyBuilding;
	cout << "Enter the number of the buildings: ";
	cin >> howManyBuilding;
	while (true)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "You have entered a character, please enter a number!" << endl;
			cin >> howManyBuilding;
		}
		else if (howManyBuilding > (size*size))
		{
			cout << "There can be " << size * size << " buildings maximum, please enter less!" << endl;
			cin >> howManyBuilding;
		}
		else if (howManyBuilding <= 0)
		{
			cout << "There can't be minus or no number of building, please enter a positive number!" << endl;
			cin >> howManyBuilding;
		}
		else { break; };
	}

	int *coord_x = new int[howManyBuilding + 1]; //building coordinates
	int *coord_y = new int[howManyBuilding + 1]; //with +1 keep the U coordinates
	coord_x[howManyBuilding] = size / 2; //assign U in the middle of the map
	coord_y[howManyBuilding] = size / 2;

	buildingMapAssigner(map, size, building_names, Bsize - 1, howManyBuilding, coord_x, coord_y); //Bsize-1 because ı dont want to randomly assign U in map and its the last element of buildingnames
																							//If you add any building please be careful and add it BEFORE U in the building_names, U should be the last!!!		
																							//I dont assign U in the map anytime
	showMap(map, size, &coord_x[howManyBuilding], &coord_y[howManyBuilding], &building_names[Bsize - 1]);
	cout << "-------------------------" << endl;
	if (map[coord_x[howManyBuilding]][coord_y[howManyBuilding]] != '#') //we're in building by chance
	{
		cout << "You're in ";
		BuildingNameEnlarge(&map[coord_x[howManyBuilding]][coord_y[howManyBuilding]]);
		cout << endl << "-------------------------" << endl;
	}

	int options;
	cout << "CMP1001 Navigation system v1.0" << endl;
	do
	{
		cout << "1 - Print Map" << endl << "2 - Find Nearest Building" << endl << "3 - Go" << endl << "4 - Info" << endl << "5 - Close Navigation system" << endl << "Enter Your Input: ";
		cin >> options;
		cout << "-------------------------" << endl;
		
		if (options == 1)
		{
			cout << "Option 1-----------------" << endl;
			showMap(map, size, &coord_x[howManyBuilding], &coord_y[howManyBuilding], &building_names[Bsize - 1]);
		}
		else if (options == 2)
		{
			cout << "Option 2-----------------" << endl;
			nearestBuilding(map, size, coord_x, coord_y, howManyBuilding);
		}
		else if (options == 3)
		{
			cout << "Option 3-----------------" << endl;
			Go(map, size, coord_x[howManyBuilding], coord_y[howManyBuilding]);
			if (map[coord_x[howManyBuilding]][coord_y[howManyBuilding]] == '#')
			{
				showMap(map, size, &coord_x[howManyBuilding], &coord_y[howManyBuilding], &building_names[Bsize - 1]);
			}
			else
			{
				cout << "You reached ";
				BuildingNameEnlarge(&map[coord_x[howManyBuilding]][coord_y[howManyBuilding]]);
				cout << endl << "-------------------------" << endl;
				showMap(map, size, &coord_x[howManyBuilding], &coord_y[howManyBuilding], &building_names[Bsize - 1]);
			}
		}
		else if (options == 4)
		{
			cout << "Option 4-----------------" << endl;
			Info(&coord_x[howManyBuilding], &coord_y[howManyBuilding], building_names, Bsize);
		}
		else if (options == 5)
		{
			cout << "Option 5-----------------" << endl << "Goodbye";
			break;
		}
		else
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "You have entered a character, please enter a number!" << endl;
			}
			else
			cout << "Wrong input! Please enter number 1 to 5" << endl;
		}
		cout << endl << "-------------------------" << endl;

	} while (true);

	delete[] coord_x;
	delete[] coord_y;

	return 0;
}

void Go(char map[][20], int size, int &Xcoord, int &Ycoord)
{
	int flag = 0;
	int directionNumber, stepNumber;

	cout << "[Current Location : (" << Xcoord << "," << Ycoord << ")]" << endl;

	do
	{
		if (flag != 0)
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "You have entered a character, please enter a number!" << endl;
			}
			else
			{
				cout << "You entered invalid input! Please enter numbers 1, 2, 3 or 4!" << endl;
			}	
		}
		cout << "Which way you want to go : UP(1) / RIGHT(2) / DOWN(3) / LEFT(4)" << endl;
		cin >> directionNumber;
		flag++;
	} while (directionNumber < 1 || directionNumber > 4);
	flag = 0;

	do
	{
		if (flag != 0)
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "You have entered a character, please enter a number!" << endl;
			}
			else if (stepNumber <= 0)
			{
				cout << "You can't enter a minus value!" << endl;
			}
			else
			{
				if (directionNumber == 1)
				{
					if (stepNumber <= Xcoord)
					{
						Xcoord = Xcoord - stepNumber;
						break;
					}
					else
					{
						cout << "You entered invalid input! You can go UP just " << Xcoord << " steps!" << endl;
					}
				}
				else if (directionNumber == 2)
				{
					int maxstep = (size - 1) - Ycoord;
					if (stepNumber <= maxstep)
					{
						Ycoord = Ycoord + stepNumber;
						break;
					}
					else
					{
						cout << "You entered invalid input! You can go RIGHT just " << maxstep << " steps!" << endl;
					}
				}
				else if (directionNumber == 3)
				{
					int maxstep = (size - 1) - Xcoord;
					if (stepNumber <= maxstep)
					{
						Xcoord = Xcoord + stepNumber;
						break;
					}
					else
					{
						cout << "You entered invalid input! You can go DOWN just " << maxstep << " steps!" << endl;
					}
				}
				else
				{
					if (stepNumber <= Ycoord)
					{
						Ycoord = Ycoord - stepNumber;
						break;
					}
					else
					{
						cout << "You entered invalid input! You can go LEFT just " << Ycoord << " steps!" << endl;
					}
				}
			}
		}
		cout << "Please enter number of steps : " << endl;
		cin >> stepNumber;
		flag++;
	} while (true);

	cout << endl << "-------------------------" << endl;
}


void Info(int *xcoord, int *ycoord, char buildings[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << buildings[i] << " = ";
		BuildingNameEnlarge(&buildings[i]);
		cout << endl;
	}
	cout << "[Current Location : (" << *xcoord << "," << *ycoord << ")]";
}