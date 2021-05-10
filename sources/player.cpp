#include "player.h"

Player::Player(std::string name, std::string character, bool isAI)
{
	m_name      = name;
	m_character = character;
	m_isAI      = isAI;
}

Player::~Player()
{

}

std::string Player::GetCharacter()
{
	return m_character;
}

std::string Player::GetName()
{
	return m_name;
}

bool Player::IsAI()
{
	return m_isAI;
}

