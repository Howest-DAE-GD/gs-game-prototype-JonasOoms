#pragma once

class SoundEffect;

class IntroScreen
{
public:

	IntroScreen(const Rectf& viewport);

	void Draw();
	void Update(float elapsedSec);
	bool GetDone() { return Done; };
	void Skip();
private:
	float m_IntroTimer;
	Rectf m_ViewPort;

	SoundEffect* Bell;
	int DramaticCount{ 0 };

	bool Done{ false };
};

