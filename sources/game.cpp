#include <iostream>
#include "board.h"
#include "player.h"
#include "game.h"
#include <limits>
#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

Game::Game()
	: m_player_index(0)
	, m_winning_length(3)
{
	m_board   = new Board(5,5);
	m_player.push_back(new Player("Alice", "X", false));
	m_player.push_back(new Player("Bob",   "O", true));

	m_current_player = m_player.at(0);
}

Game::~Game()
{
	if (m_board)
		delete m_board;
	while (m_player.size() > 0)
	{
		Player * p = m_player.at(m_player.size()-1);
		m_player.pop_back();
		delete p;
	}
}

void Game::PrintBoard()
{
	m_board->PrintBoard();
}

void Game::Play()
{
	State game_state(CONTINUE_PLAYING);
	do{
		// Toggle players
		m_current_player = m_player.at(m_player_index);
		
		// Display board
		PrintBoard();

		// Enter a location
		int x(0), y(0);
		bool location_set(false);
		std::cout << m_current_player->GetName() << "'s turn." << std::endl;
		do 
		{
			std::cout << "Enter a grid location:" << std::endl;
			bool repeat(false);
			
			// Safe input for X
			do {
				repeat = false;
				std::cout << "X: ";
				std::cin  >> x;
				if (std::cin.fail())
				{
					repeat = true;
					system("clear");
					PrintBoard();
					std::cout << "Invalid position: x = " << x << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			} while(repeat);
			
			// Safe input for Y
			do {
				repeat = false;
				std::cout << "Y: ";
				std::cin  >> y;
				if (std::cin.fail())
				{
					repeat = true;
					system("clear");
					PrintBoard();
					std::cout << "Invalid position: y = " << y << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			} while(repeat);

			location_set = m_board->SetLocation(m_current_player, x, y);
			if (!location_set)
			{
				system("clear");
				PrintBoard();
				std::cout << "Invalid position: (" << x << ", " << y << ")" << std::endl;
			}
		} while(!location_set);
		
		// Check for winners
		game_state = GameState(m_current_player);

		m_player_index = (m_player_index + 1) % m_player.size();
		//system("clear");
	}while(CONTINUE_PLAYING == game_state);
	switch(game_state)
	{
		case AI_WINS:     std::cout << "AI Wins!"     << std::endl; break;
		case PLAYER_WINS: std::cout << "Player Wins!" << std::endl; break;
		case TIE:         std::cout << "Tie!"         << std::endl; break;
		default:          /* Keep playing. */                       break;
	}
	PrintBoard();
}

State Game::GameState(Player * p)
{
	int row(0), col(0);
	int streak(0);
	
	// Check columns for win
	for(int row_offset=1; row_offset + m_winning_length - 1 <= m_board->m_height; row_offset++)
	{
		for(col=1; col<=m_board->m_width; col++)
		{
			for(row=row_offset; row - row_offset + 1 <= m_winning_length; row++)
			{
				if (m_board->IsCellPlayer(row,col,p->GetCharacter()))
					streak++;
			}
			if (streak == m_winning_length)
			{
				if (p->IsAI())
					return AI_WINS;
				return PLAYER_WINS;
			}
			streak = 0;
		}
	}

	// Check rows for win
	for(int col_offset=1; col_offset + m_winning_length - 1 <= m_board->m_width; col_offset++)
	{
		for(row=1; row<=m_board->m_width; row++)
		{
			for(col=col_offset; col - col_offset + 1 <= m_winning_length; col++)
			{
				if (m_board->IsCellPlayer(row,col,p->GetCharacter()))
					streak++;
			}
			if (streak == m_winning_length)
			{
				if (p->IsAI())
					return AI_WINS;
				return PLAYER_WINS;
			}
			streak = 0;
		}
	}

	// Check down-right diagonals
	for(int row_offset=1; row_offset + m_winning_length - 1 <= m_board->m_height; row_offset++)
	{
		for(int col_offset=1; col_offset + m_winning_length - 1 <= m_board->m_width; col_offset++)
		{
			for(row=row_offset,col = col_offset; col - col_offset + 1 <= m_winning_length && row - row_offset + 1 <= m_winning_length; row++, col++)
			{
				if (m_board->IsCellPlayer(row,col,p->GetCharacter()))
					streak++;
			}
			if (streak == m_winning_length)
			{
				if (p->IsAI())
					return AI_WINS;
				return PLAYER_WINS;
			}
			streak = 0;
		}
	}
	
	// Check up-left diagonals
	for(int row_offset=m_board->m_height; row_offset - m_winning_length + 1 >=0; row_offset--)
	{
		for(int col_offset=1; col_offset + m_winning_length - 1 <= m_board->m_width; col_offset++)
		{
			for(row=row_offset,col = col_offset; col - col_offset + 1 <= m_winning_length && row_offset - row + 1 <= m_winning_length; row--, col++)
			{
				if (m_board->IsCellPlayer(row,col,p->GetCharacter()))
					streak++;
			}
			if (streak == m_winning_length)
			{
				if (p->IsAI())
					return AI_WINS;
				return PLAYER_WINS;
			}
			streak = 0;
		}
	}

	// Draw
	if (!m_board->HasMorePlays())
		return TIE;
	return CONTINUE_PLAYING;
}
