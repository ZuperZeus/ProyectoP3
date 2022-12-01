/*
 *	Connect-4, a terminal GUI with a min-max AI for the classic board game of the same name.
 *	Copyright (C) 2022 ZuperZeus
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.	If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <stdlib.h>
#include <algorithm>
#include "Board.h"

using namespace std;
Board::Board()
{
	board.resize(6);
	for(int i=0;i<6;i++)
	{
		board[i].resize(7);
		for(int j=0;j<7;j++)
		{
			boardArr[i][j]=0;
			board[i][j]=0;
		}
	}
}
Board::Board(vector< vector<int> > arr)
{
	board=arr;
	for(int i=0;i<6;i++)
		for(int j=0;j<7;j++)
			board[i][j]=arr[i][j];
}
int Board::drop(int sel, int player)
{
	int cont=0;
	while(cont<6&&board[cont][sel]==0) cont++;
	cont--;
	if(cont==-1) return -1;
	else board[cont][sel]=player;
	return cont;
}
bool Board::canDrop(int sel)
{
	return board[0][sel]==0;
}
int Board::checkWin()
{
	vector< vector<int> > arr=getWin();
	if (arr[0].size() == 0)
		return 0;
	else
		return board[arr[1][0]][arr[0][0]];
}
int compare(pair<int,int> a,pair<int,int> b)
{
	return a.second<b.second;
}/*
int Board::eval(int diff, string line)
{
	srand(time(NULL));
	GameSolver::Connect4::Solver solver;
	bool weak = false;
	string opening_book = "txt/7x6.book";
	vector<int> scores;
	solver.loadBook(opening_book);
	GameSolver::Connect4::Position P;
	if(P.play(line) == line.size()) {
		scores = solver.analyze(P, weak);
	}
	vector< pair<int,int> > pairv(7);
	for(int i = 0; i < 7; i++) pairv[i]=std::make_pair(i,scores[i]);
	sort(pairv.begin(),pairv.end(),compare);
		if(rand()%10<=diff)
				return pairv[6].first;
		else// if(canDrop(x))
			return rand()%7;
	return -1;
}*/
//returns 2xn array with win conditions
vector< vector<int> > Board::getWin()
{
	vector< vector<int> > winvec(2, vector<int>(0));
	int cont1=0;
	int cont2=0;
	// #
	// #
	// #
	for (int i = 0; i<6; i++)
	{
		for(int j=0;j<7;j++)
		{
			if(board[i][j]==1)
			{
				if(cont2>=4) return winvec;
				else if(cont2!=0){winvec[0].resize(0);winvec[1].resize(0);}
				winvec[0].push_back(j);
				winvec[1].push_back(i);
				cont1++;
				cont2=0;
			}
			else if(board[i][j]==2)
			{
				if(cont1>=4) return winvec;
				else if(cont1!=0){winvec[0].resize(0);winvec[1].resize(0);}
				winvec[0].push_back(j);
				winvec[1].push_back(i);
				cont2++;
				cont1=0;
			}
			else
			{
				if(cont1>=4||cont2>=4) return winvec;
				winvec[0].resize(0);
				winvec[1].resize(0);
				cont1=0;
				cont2=0;
			}
		}
		if(cont1>=4||cont2>=4) return winvec;
		winvec[0].resize(0);
		winvec[1].resize(0);
		cont1=0;
		cont2=0;
	}
	//
	// ###
	//
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(board[j][i]==1)
			{
				if(cont2>=4) return winvec;
				else if(cont2!=0){winvec[0].resize(0);winvec[1].resize(0);}
				winvec[0].push_back(i);
				winvec[1].push_back(j);
				cont1++;
				cont2=0;
			}
			else if(board[j][i]==2)
			{
				if(cont1>=4) return winvec;
				else if(cont1!=0){winvec[0].resize(0);winvec[1].resize(0);}
				winvec[0].push_back(i);
				winvec[1].push_back(j);
				cont2++;
				cont1=0;
			}
			else
			{
				if(cont1>=4||cont2>=4) return winvec;
				winvec[0].resize(0);
				winvec[1].resize(0);
				cont1=0;
				cont2=0;
			}
		}
		if(cont1>=4||cont2>=4) return winvec;
		winvec[0].resize(0);
		winvec[1].resize(0);
		cont1=0;
		cont2=0;
	}
	//   #	
	//  #
	// #
	for(int i=0;i<14;i++)
	{
		for (int j = 0; j<6; j++)
		if(i-j<7&&i-j>=0)
		{
			if(board[j][i-j]==1)
			{
				if(cont2>=4) return winvec;
				else if(cont2!=0){winvec[0].resize(0);winvec[1].resize(0);}
				winvec[0].push_back(i-j);
				winvec[1].push_back(j);
				cont1++;
				cont2=0;
			}
			else if(board[j][i-j]==2)
			{
				if(cont1>=4) return winvec;
				else if(cont1!=0){winvec[0].resize(0);winvec[1].resize(0);}
				winvec[0].push_back(i-j);
				winvec[1].push_back(j);
				cont2++;
				cont1=0;
			}
			else
			{
				if(cont1>=4||cont2>=4) return winvec;
				winvec[0].resize(0);
				winvec[1].resize(0);
				cont1=0;
				cont2=0;
			}
		}
		if(cont1>=4||cont2>=4) return winvec;
		winvec[0].resize(0);
		winvec[1].resize(0);
		cont1=0;
		cont2=0;
	}
	// #	
	//  #
	//   #
	for(int i=-6;i<7;i++)
	{
		for(int j=0;j<6;j++)
		if(i+j<7&&i+j>=0)
		{
			if(board[j][i+j]==1)
			{
				if(cont2>=4) return winvec;
				else if(cont2!=0){winvec[0].resize(0);winvec[1].resize(0);}
				winvec[0].push_back(i+j);
				winvec[1].push_back(j);
				cont1++;
				cont2=0;
			}
			else if(board[j][i+j]==2)
			{
				if(cont1>=4) return winvec;
				else if(cont1!=0){winvec[0].resize(0);winvec[1].resize(0);}
				winvec[0].push_back(i+j);
				winvec[1].push_back(j);
				cont2++;
				cont1=0;
			}
			else
			{
				if(cont1>=4||cont2>=4) return winvec;
				winvec[0].resize(0);
				winvec[1].resize(0);
				cont1=0;
				cont2=0;
			}
		}
		if(cont1>=4||cont2>=4) return winvec;
		winvec[0].resize(0);
		winvec[1].resize(0);
		cont1=0;
		cont2=0;
	}
	return winvec;
}
vector< vector<int> > Board::getBoard()
{
	vector< vector<int> > temp;
	temp.resize(7);
	for(int i=0;i<7;i++)
	{
		temp[i].resize(6);
		for(int j=0;j<6;j++)
		{
			temp[i][j]=board[j][i];
		}
	}
	return temp;
}
