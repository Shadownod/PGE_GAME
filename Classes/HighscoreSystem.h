#ifndef HIGHSCORESYSTEM_H
#define HIGHSCORESYSTEM_H

HighscoreSystem* instance;

class HighscoreSystem
{
public:
	static HighscoreSystem* getInstance()
	{
		if (instance == nullptr)
			instance = new HighscoreSystem();
		return instance;
	}

	~HighscoreSystem();

	void AddScore(int _score);
	void DeductScore(int _score);
	int GetScore();

private:
	HighscoreSystem();

	static HighscoreSystem* instance;

	int m_Score;
};

#endif // !HIGHSCORE_H
