#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "player.h"
#include <vector>

class Board
{
public:
	            Board(int w=3,int h=3, int winning_length = 3);
	           ~Board();
	bool        ClearBoard();
	void        PrintBoard();

	bool        HasMorePlays();
	bool        SetLocation(Player* player, int x, int y);
	int         GetLocation(int x, int y);
	bool        IsCellPlayer(int row, int col, std::string character);
	int         m_width;
	int         m_height;

private:
	std::vector<std::string> m_board;

};

#endif
