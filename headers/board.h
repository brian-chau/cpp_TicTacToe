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

	// Public functions
	bool        ClearBoard();
	void        PrintBoard();

	bool        HasMorePlays();
	bool        SetLocation(Player* player, int x, int y);
	std::string GetPositionChar(int row, int col);
	std::string GetPositionChar(int pos);
	bool        IsCellPlayer(int row, int col, std::string character);
	bool        IsCellPlayer(int position, std::string character);
	void        FindWinningPositions(int winning_length);

	// Public members
	int                           m_width;
	int                           m_height;
	std::vector<std::vector<int>> m_winning_streaks;

private:
	std::vector<std::string>      m_board;

};

#endif
