#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
class Player{
public:
	 Player(std::string name="Player1", std::string character="X", bool isAI=false);
	~Player();

	std::string                   GetCharacter();
	std::string                   GetName();
	bool                          IsAI();

private:
	std::string                   m_name;
	std::string                   m_character;
	bool                          m_isAI;
	std::vector<std::vector<int>> m_winning_positions;
};


#endif
