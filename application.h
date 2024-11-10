#pragma once
#include <SFML/Graphics.hpp>
#include "grid.h"

class application
{

public:	
	application();

	void run();
	void end();

	inline bool is_running() { return mWindow.isOpen(); }

private:
	const int gridWidth = 50;
	const int gridHeight = 50;
	const int pixelSize = 20;

	//time management
	sf::Clock clock;
	sf::Time timeSinceLastFrame{ sf::Time::Zero };
	sf::Time timePerFrame;
	const float loopRate{ 60 };

	sf::RenderWindow mWindow;	
	sf::Mouse mouse;
	grid mGrid;

	bool isHoldingMouseL =  false;
	bool isHoldingMouseR = false;

private:
	void render();
};

