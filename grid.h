#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "pixel.h"

class grid
{

public:	
	grid(int pW, int pH, int pPixelSize);
	~grid();
	void step();
	void drawPixel(int pX, int pY, pixel_type pType);
	void render(sf::RenderTarget& mWindow);

	pixel* getPixel(int x, int y) {
		size_t iterator = getIterator(x, y);
		if (iterator < mValues.size())
			return mValues[iterator];
		else return nullptr;
	}

	pixel* operator[] (int pIndex) {
		if ((size_t)pIndex < mValues.size()) return (mValues[pIndex]);
		else return nullptr;
	}

private:
	int mGridSize;
	int mWidth;
	int mHeight;
	int mPixelSize;

	std::vector<pixel*> mValues;
	std::vector<pixel*> mValues_copy;
	sf::VertexArray mQuads;

private:
	void swapPixels(int pI1, int pI2, std::vector<pixel*>& pValues);
	void setQuadColor(int pX, int pY, sf::Color pC);
	inline int getIterator(int x, int y) { return y * mWidth + x; }
};

