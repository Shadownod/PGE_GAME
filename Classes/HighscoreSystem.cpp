#include "HighscoreSystem.h"

HighscoreSystem::HighscoreSystem()
{
	m_Score = 0;
}

HighscoreSystem::~HighscoreSystem()
{

}

void HighscoreSystem::AddScore(int _score)
{
	m_Score += _score;
}

void HighscoreSystem::DeductScore(int _score)
{
	m_Score -= _score
}

int HighscoreSystem::GetScore()
{
	return m_Score;
}
