//przykaldowe dane do uruchomienia programu: "i 1 2 3 4 8 7 6 5" 
#include<iostream>
#include "Eight_Puzzle_Map.h"
using namespace std;
int main(void) {
	char choice;
	cout << "8-puzzle solver, hill climbing algorithm, random (r) or input by user (i)" << endl;
	cin >> choice;
	Eight_Puzzle_Map* Map_of_8_puzzle=NULL;
	if(choice=='i'){
		int temp_tab[3][3];
		vector<int> temp_vec;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int temp;
				cout << "Input a number (0,8) to field " << i + 1 <<":"<< j + 1 << endl;
				cin >> temp;
				if (temp < 0 || temp >8) {
					j--;
					continue;
				}
				temp_tab[i][j] = temp;
				temp_vec.push_back(temp_tab[i][j]);
			}
		}
		Map_of_8_puzzle = new Eight_Puzzle_Map(temp_vec);
	}
	else{
		Map_of_8_puzzle = new Eight_Puzzle_Map();
	}
	while (Map_of_8_puzzle->manhatan_distance() != 0) {
		try {
			cout << *Map_of_8_puzzle;
			Map_of_8_puzzle->local_swap();
		}
		catch (MoreThanOneLocalMin &e) {
			std::cout <<"Exepction: "<< e.what() << ", randomizing puzzle" <<std::endl;
			Map_of_8_puzzle->randomize_tab();
			continue;
		}
	}
	cout << *Map_of_8_puzzle;
	cout << "number of exepctions caught (number of puzzle randoming): " << Map_of_8_puzzle->number_of_randomize << endl;
	delete Map_of_8_puzzle;
	return 0;
}