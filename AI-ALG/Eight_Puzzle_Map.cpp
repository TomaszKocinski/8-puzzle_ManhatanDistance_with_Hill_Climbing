#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include "Eight_Puzzle_Map.h"

using namespace std;
Eight_Puzzle_Map::Eight_Puzzle_Map() {
	number_of_randomize = 0;
	randomize_tab();
}
Eight_Puzzle_Map::Eight_Puzzle_Map(std::vector<int> &arg) {
	number_of_randomize = 0;
	vector<int>::iterator ite = arg.begin();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tab[i][j] = *ite++;
			if (tab[i][j] == 0) {
				x_zero = i;
				y_zero = j;
			}
		}
	}
}
void Eight_Puzzle_Map::randomize_tab() {
	number_of_randomize++;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tab[i][j] = -1;
		}
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 8);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int temp = dis(gen);
			if (isAlready_In_Tab(temp)) {
				j--;
				continue;
			}
			if (temp == 0) {
				x_zero = i;
				y_zero = j;
			}
			tab[i][j] = temp;
		}
	}
}
bool Eight_Puzzle_Map::isRandoming_Working() const {

	vector<int> temp_vec = { 0,1,2,3,4,5,6,7,8 };
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (tab[i][j] != -1)
				temp_vec.erase(temp_vec.begin() + tab[i][j]);
		}
	}
	return temp_vec.empty();
}
bool Eight_Puzzle_Map::isAlready_In_Tab(int &arg) const {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (tab[i][j] == arg) {
				return true;
			}

		}
	}
	return false;
}
ostream& operator<<(ostream& s, const Eight_Puzzle_Map& map) {
	s << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (map.tab[i][j] != 0)
				s << map.tab[i][j];
			else {
				s << " ";
			}
		}
		s << endl;
	}
	return s ;
}
void Eight_Puzzle_Map::swap(int x, int y) {
	if (x < 0 || x > 2) {
		cout << "swap - error, out of bound x:" << x << endl;
	}
	if (y < 0 || y > 2) {
		cout << "swap - error, out of bound y:" << y << endl;
	}

	if (abs(x - x_zero) + abs(y - y_zero) != 1) {
		cout << "error swap - distance not 1  :" << x << y << endl;
	}
	else {
		int temp = tab[x_zero][y_zero];
		tab[x_zero][y_zero] = tab[x][y];
		tab[x][y] = temp;
		x_zero = x;
		y_zero = y;
	}
}
int Eight_Puzzle_Map::manhatan_distance() {
	int distance = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int val_from_tab = tab[i][j];
			if (val_from_tab == 0) continue;
			int win_x = (val_from_tab % 3) - 1;
			int win_y = val_from_tab / 3;
			if (win_x == -1) {
				win_x = 2;
				win_y--;
			}
			distance += abs(i - win_y) + abs(j - win_x);
		}
	}

	return distance;
}
void Eight_Puzzle_Map::local_swap() {
	multimap<int, char> map_cont;
	int temp;

	if (x_zero == 0 && y_zero == 0) {
		swap(x_zero + 1, y_zero);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'E'));
		swap(0, 0);

		swap(x_zero, y_zero + 1);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'S'));
		swap(0, 0);
	}
	else if (x_zero == 1 && y_zero == 0) {
		swap(x_zero - 1, y_zero);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'W'));
		swap(1, 0);

		swap(x_zero + 1, y_zero);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'E'));
		swap(1, 0);

		swap(x_zero, y_zero + 1);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'S'));
		swap(1, 0);
	}

	else if (x_zero == 2 && y_zero == 0) {
		swap(x_zero - 1, y_zero);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'W'));
		swap(2, 0);

		swap(x_zero, y_zero + 1);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'S'));
		swap(2, 0);
	}
	else if (x_zero == 0 && y_zero == 1) {
		swap(x_zero, y_zero - 1);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'N'));
		swap(0, 1);

		swap(x_zero + 1, y_zero);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'E'));
		swap(0, 1);

		swap(x_zero, y_zero + 1);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'S'));
		swap(0, 1);
	}
	else if (x_zero == 1 && y_zero == 1) {

		swap(x_zero - 1, y_zero);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'W'));
		swap(1, 1);

		swap(x_zero, y_zero - 1);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'N'));
		swap(1, 1);

		swap(x_zero + 1, y_zero);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'E'));
		swap(1, 1);

		swap(x_zero, y_zero + 1);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'S'));
		swap(1, 1);

	}
	else if (x_zero == 2 && y_zero == 1) {

		swap(x_zero - 1, y_zero);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'W'));
		swap(2, 1);

		swap(x_zero, y_zero - 1);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'N'));
		swap(2, 1);

		swap(x_zero, y_zero + 1);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'S'));
		swap(2, 1);
	}
	else if (x_zero == 0 && y_zero == 2) {
		swap(x_zero, y_zero - 1);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'N'));
		swap(0, 2);

		swap(x_zero + 1, y_zero);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'E'));
		swap(0, 2);
	}
	else if (x_zero == 1 && y_zero == 2) {
		swap(x_zero - 1, y_zero);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'W'));
		swap(1, 2);

		swap(x_zero, y_zero - 1);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'N'));
		swap(1, 2);

		swap(x_zero + 1, y_zero);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'E'));
		swap(1, 2);
	}

	else if (x_zero == 2 && y_zero == 2) {
		swap(x_zero - 1, y_zero);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'W'));
		swap(2, 2);

		swap(x_zero, y_zero - 1);
		temp = manhatan_distance();
		map_cont.insert(pair<int, char>(temp, 'N'));
		swap(2, 2);

	}
	find_smallest_in_mmap(map_cont);
}
void Eight_Puzzle_Map::find_smallest_in_mmap(multimap<int, char>& map_container) {

	for (int i = 0; i < 100; i++) {
		int count_of_elements;
		count_of_elements = map_container.count(i);
		if (count_of_elements == 0) continue;
		if (count_of_elements == 1) break;
		if (count_of_elements > 1) throw MoreThanOneLocalMin();
	}
	char direction = map_container.begin()->second;
	if (direction == 'W') {
		swap(x_zero - 1, y_zero);
	}
	if (direction == 'N')
	{
		swap(x_zero, y_zero - 1);
	}
	if (direction == 'E')
	{
		swap(x_zero + 1, y_zero);
	}
	if (direction == 'S')
	{
		swap(x_zero, y_zero + 1);
	}

}