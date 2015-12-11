#pragma once

#include <vector>
#include <map>
#include "ExceptionFile.h"


class Eight_Puzzle_Map {
private:
	int x_zero;
	int y_zero;
	int tab[3][3];
public:
	int number_of_randomize;
	Eight_Puzzle_Map();
	Eight_Puzzle_Map(std::vector<int>&);
	void randomize_tab();
	bool isRandoming_Working() const;
	bool isAlready_In_Tab(int &arg) const;
	void swap(int x, int y);
	int manhatan_distance();
	void local_swap();
	void find_smallest_in_mmap(std::multimap<int, char>& map_container);
	friend std::ostream& operator<<(std::ostream& s, const Eight_Puzzle_Map& map);
};