/*
 *  Connect-4, a terminal GUI with a min-max AI for the classic board game of the same name.
 *  Copyright (C) 2022 ZuperZeus
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
using namespace std;
class Board
{
	private:
		int boardArr[6][7];//0=empty; 1=p1; 2=p2
		vector< vector<int> > board;
	public:
		Board();
		Board(vector< vector<int> > arr);
		int drop(int sel, int player);
		bool canDrop(int sel);
		int checkWin();
		vector< vector<int> > getWin();
		//int eval(int diff, string line);
		vector< vector<int> > getBoard();
};
#endif
