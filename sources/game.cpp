#include <iostream>
#include "board.h"
#include "player.h"
#include "game.h"
#include <limits>
#include <algorithm>
#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

Game::Game()
	: m_player_index(0)
	, m_winning_length(3)
{
	m_board = new Board(5,5);
	m_board->FindWinningPositions(m_winning_length);

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
		int row(0), col(0);
		bool location_set(false);
		std::cout << m_current_player->GetName() << "'s turn." << std::endl;
		do
		{
			std::cout << "Enter a grid location:" << std::endl;
			bool repeat(false);

			// Safe input for row
			do {
				repeat = false;
				std::cout << "Row: ";
				std::cin  >> row;
				if (std::cin.fail())
				{
					repeat = true;
					system("clear");
					PrintBoard();
					std::cout << "Invalid position: row = " << row << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			} while(repeat);

			// Safe input for column
			do {
				repeat = false;
				std::cout << "Col: ";
				std::cin  >> col;
				if (std::cin.fail())
				{
					repeat = true;
					system("clear");
					PrintBoard();
					std::cout << "Invalid position: col = " << col << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			} while(repeat);

			location_set = m_board->SetLocation(m_current_player, row, col);
			if (!location_set)
			{
				system("clear");
				PrintBoard();
				std::cout << "Invalid position: (" << row << ", " << col << ")" << std::endl;
			}
		} while(!location_set);
		// Check for winners
		game_state = GameState(m_current_player, row, col);

		m_player_index = (m_player_index + 1) % m_player.size();
		system("clear");
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

State Game::GameState(Player * p, int row, int col)
{
	// The 1D index of the 2D board position
	row--,col--;
	int played_position = (row * m_board->m_width) + col;
	std::cout << "Played position: " << played_position << std::endl;
	std::cout << " " << row << " " << col << std::endl;
	bool streak_found(true), streak_contains_position(false);
	
	// Check all possible streaks for a winner
	for(const std::vector<int>& streak : m_board->m_winning_streaks)
	{
		// Check if streak is a possible winning streak
		// by finding the position that the player played
		streak_contains_position = false;
		for(int streak_position : streak)
		{
			if (played_position == streak_position)
			{
				streak_contains_position = true;
				break;
			}
		}
		if (!streak_contains_position)
			continue;

		// Check the streak if it is a winner
		streak_found = true; 
		for(int streak_position : streak)
		{
			if (!m_board->IsCellPlayer(streak_position, p->GetCharacter()))
			{
				streak_found = false;
				break;
			}
		}

		if (streak_found)
		{
			if (p->IsAI())
				return AI_WINS;
			return PLAYER_WINS;
		}
	}

	// Mark it a tie.
	if (!m_board->HasMorePlays())
		return TIE;
	return CONTINUE_PLAYING;
}
