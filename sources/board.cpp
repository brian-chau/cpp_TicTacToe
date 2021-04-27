#include "board.h"
#include <algorithm>
#include <iostream>
#include <cstring>

Board::Board(int w, int h, int winning_length)
	: m_width(w)
	, m_height(h)
{
	std::vector<std::string> init(w*h,std::string("-") );
	m_board = init;
}

Board::~Board()
{

}

bool Board::ClearBoard()
{
	std::vector<std::string> init(m_width*m_height,std::string("-") );
	m_board = init;
	return true;
}

void Board::PrintBoard()
{
	for(int i=0; i<m_width; i++)
	{
		for(int j=0; j<m_height; j++)
			std::cout << m_board[m_width * j + i];
		std::cout << std::endl;
	}
}

bool Board::SetLocation(Player* player, int x, int y)
{
	x--, y--;
	
	// If it is within bounds
	if ((x >= 0 && x < m_width) && (y >= 0 && y < m_height))
	{
		// If it isn't an empty space
		if ("-" != m_board[m_width * y + x])
			return false;
		
		// Set if it is an empty space
		m_board[m_width * y + x] = player->GetCharacter();
		return true;		
	}
	
	return false;
}

bool Board::HasMorePlays()
{
	return std::find(m_board.begin(), m_board.end(), "-") != m_board.end();
}

bool Board::IsCellPlayer(int x, int y, std::string character)
{
	x--, y--;

	// If it is out of bounds, then it is obviously not the player
	if (!((x >= 0 && x < m_width) && (y >= 0 && y < m_height)))
		return false;

	// Compare the cell value with the player character
	std::string cell_val = m_board[m_width * y + x];
	return cell_val == character;
}
