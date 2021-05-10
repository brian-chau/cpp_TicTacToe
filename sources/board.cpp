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
	for(int row=0; row<m_height; row++)
	{
		for(int col=0; col<m_width; col++)
			std::cout << m_board[m_width * row + col];
		std::cout << std::endl;
	}
}

// Converts a 2D index into a 1D index to be stored
bool Board::SetLocation(Player* player, int row, int col)
{
	row--, col--;

	// If it is within bounds
	if ((col >= 0 && col < m_width) && (row >= 0 && row < m_height))
	{
		// If it isn't an empty space
		if ("-" != m_board[m_width * row + col])
			return false;

		// Set if it is an empty space
		m_board[m_width * row + col] = player->GetCharacter();
		return true;
	}

	return false;
}

std::string Board::GetPositionChar(int row, int col)
{
	return m_board[m_width * row + col];
}

std::string Board::GetPositionChar(int pos)
{
	return m_board[pos];
}

bool Board::HasMorePlays()
{
	return std::find(m_board.begin(), m_board.end(), "-") != m_board.end();
}

bool Board::IsCellPlayer(int row, int col, std::string character)
{
	row--, col--;

	// If it is out of bounds, then it is obviously not the player
	if (!((col >= 0 && col < m_width) && (row >= 0 && row < m_height)))
		return false;

	// Compare the cell value with the player character
	std::string cell_val = m_board[m_width * row + col];
	return cell_val == character;
}

bool Board::IsCellPlayer(int position, std::string character)
{
	if (!(0 <= position && position < m_width * m_height))
		return false;
	std::string cell_val = m_board[position];
	return cell_val == character;
}

void Board::FindWinningPositions(int winning_length)
{
	int row(0), col(0);

	// This will contain a singular index that contains both rows and columns
	std::vector<int> winning_indexes;
	m_winning_streaks.clear();

	// Check columns for win
	for(int row_offset=0; row_offset + winning_length - 1 <= m_height; row_offset++)
	{
		for(col=0; col<=m_width; col++)
		{
			for(row=row_offset; row - row_offset + 1 <= winning_length; row++)
			{
				winning_indexes.push_back(row * m_width + col);
			}
			m_winning_streaks.push_back(winning_indexes);
			winning_indexes.clear();
		}
	}

	winning_indexes.clear();
	// Check rows for win
	for(int col_offset=0; col_offset + winning_length - 1 <= m_width; col_offset++)
	{
		for(row=0; row<=m_width; row++)
		{
			for(col=col_offset; col - col_offset + 1 <= winning_length; col++)
			{
				winning_indexes.push_back(row * m_width + col);
			}
			m_winning_streaks.push_back(winning_indexes);
			winning_indexes.clear();
		}
	}

	winning_indexes.clear();
	// Check down-right diagonals
	for(int row_offset=0; row_offset + winning_length - 1 <= m_height; row_offset++)
	{
		for(int col_offset=0; col_offset + winning_length - 1 <= m_width; col_offset++)
		{
			for(row=row_offset,col = col_offset; col - col_offset + 1 <= winning_length && row - row_offset + 1 <= winning_length; row++, col++)
			{
				winning_indexes.push_back(row * m_width + col);
			}
			m_winning_streaks.push_back(winning_indexes);
			winning_indexes.clear();
		}
	}

	winning_indexes.clear();
	// Check up-left diagonals
	for(int row_offset=m_height; row_offset - winning_length + 1 >=0; row_offset--)
	{
		for(int col_offset=1; col_offset + winning_length - 1 <= m_width; col_offset++)
		{
			for(row=row_offset,col = col_offset; col - col_offset + 1 <= winning_length && row_offset - row + 1 <= winning_length; row--, col++)
			{
				winning_indexes.push_back(row * m_width + col);
			}
			m_winning_streaks.push_back(winning_indexes);
			winning_indexes.clear();
		}
	}

//	for (const std::vector<int> & streak : m_winning_streaks)
//	{
//		for (int pos : streak)
//		{
//			std::cout << pos << ",";
//		}
//		std::cout << std::endl;
//	}
}
