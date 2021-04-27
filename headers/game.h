#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"
#include <vector>

enum State { CONTINUE_PLAYING = 0, AI_WINS, PLAYER_WINS, TIE };
class Game{

public:
	                     Game();
	                    ~Game();
	void                 Play();
	void                 PrintBoard();
	State                GameState(Player* p);

private:
	std::vector<Player*> m_player;
	Board  *             m_board;
	Player *             m_current_player;
	int                  m_player_index;
	int                  m_winning_length;
};

#endif
