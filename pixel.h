#pragma once
#include <SFML/Graphics.hpp>

enum pixel_type
{
	px_empty,
	px_sand,
	px_water
};

class pixel
{
public:
	sf::Color CL_EMPTY = sf::Color::Black;
	sf::Color CL_SAND = sf::Color::Yellow;
	sf::Color CL_WATER = sf::Color::Blue;

public:	
	pixel();

	inline const pixel_type& getId() { return mId; }
	inline const sf::Color& getColor() { return mColor; }
	inline const sf::Vector2f& getVelocity(){ return mVelocity; }

	inline void setColor(sf::Color pColor) { mColor = pColor; }
	inline void setVelocity(sf::Vector2f pVelocity) { mVelocity = pVelocity; }

	void setId(pixel_type pType);
protected:	

	pixel_type mId;
	sf::Vector2f mVelocity;
	sf::Color mColor;

	//float lifeTime;
	//bool hasBeenUpdated;
};

