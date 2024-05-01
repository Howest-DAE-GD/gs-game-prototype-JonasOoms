#include "pch.h"
#include "IntroScreen.h"
#include "SoundEffect.h"
#include "Texture.h"

IntroScreen::IntroScreen(const Rectf& viewport) :
	m_ViewPort{ viewport },
	m_IntroTimer{0.f}
{
	Bell = new SoundEffect("Bell.wav");
	Bell->SetVolume(4);
}

void IntroScreen::Draw()
{

	if (m_IntroTimer >= 26.f)
	{
		if (DramaticCount == 4)
		{
			Bell->Play(0);
			++DramaticCount;
		}

	}


	else if (m_IntroTimer >= 21.f)
	{
		if (DramaticCount == 3)
		{
			Bell->Play(0);
			++DramaticCount;
		}

		Texture* Text = new Texture("You must kill to be remembered.", "BlithedaleSerif-Regular.otf", 20, Color4f{ 1,1,1,1 });
		Text->Draw(Point2f{ m_ViewPort.width / 2 - Text->GetWidth() / 2 ,m_ViewPort.height / 2 - Text->GetHeight() / 2 });
		delete Text;

	}

	else if (m_IntroTimer >= 16.f)
	{
		if (DramaticCount == 2)
		{
			Bell->Play(0);
			++DramaticCount;
		}

		Texture* Text = new Texture("The idea of your existence depends on your actions.", "BlithedaleSerif-Regular.otf", 20, Color4f{ 1,1,1,1 });
		Text->Draw(Point2f{ m_ViewPort.width / 2 - Text->GetWidth() / 2 ,m_ViewPort.height / 2 - Text->GetHeight() / 2 });
		delete Text;

	}

	else if (m_IntroTimer >= 12.f)
	{
		if (DramaticCount == 1)
		{
			Bell->Play(0);
			++DramaticCount;
		}
		Texture* Text = new Texture("You are cursed to be forgotten.", "BlithedaleSerif-Regular.otf", 20, Color4f{ 1,1,1,1 });
		Text->Draw(Point2f{ m_ViewPort.width / 2 - Text->GetWidth() / 2 ,m_ViewPort.height / 2 - Text->GetHeight() / 2 });
		delete Text;
	}

	else if (m_IntroTimer >= 5.0f)
	{
		if (DramaticCount == 0)
		{
			Bell->Play(0);
			++DramaticCount;
		}
		Texture* Text = new Texture("You are a Wraith.", "BlithedaleSerif-Regular.otf", 20, Color4f{ 1,1,1,1 });
		Text->Draw(Point2f{ m_ViewPort.width / 2 - Text->GetWidth()/2,m_ViewPort.height / 2 - Text->GetHeight()/2});
		delete Text;
	}

	
}

void IntroScreen::Update(float elapsedSec)
{
	m_IntroTimer += elapsedSec;

	if (m_IntroTimer >= 30.f)
	{
		Done = true;
	}
}

void IntroScreen::Skip()
{
	m_IntroTimer = 26.f;
	DramaticCount = 4;
}
