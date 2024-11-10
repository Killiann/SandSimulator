#include "grid.h"

sf::Color CL_EMPTY = sf::Color::Black;
sf::Color CL_SAND = sf::Color::Yellow;
sf::Color CL_WATER = sf::Color::Blue;

grid::grid(int pW, int pH, int pPixelSize) : mWidth(pW), mHeight(pH), mPixelSize(pPixelSize), rng(dev()), rndSand(0,4){	
	mGridSize = mWidth * mHeight;
	
	mQuads.setPrimitiveType(sf::Quads);
	mQuads.resize(mGridSize * 4);	
	mValues.reserve(mGridSize);

	for (size_t i = 0; i < mGridSize; i++) {
		mValues.emplace_back(new pixel());
	}

	//set quads
	for (size_t y = 0; y < mHeight; y++) {
		for (size_t x = 0; x < mWidth; x++) {
			sf::Vertex* quadNew = &mQuads[getIterator(x, y) * 4];

			quadNew[0].position = sf::Vector2f(x * mPixelSize, y * mPixelSize);
			quadNew[1].position = sf::Vector2f(x * mPixelSize + mPixelSize, y * mPixelSize);
			quadNew[2].position = sf::Vector2f(x * mPixelSize + mPixelSize, y * mPixelSize + mPixelSize);
			quadNew[3].position = sf::Vector2f(x * mPixelSize, y * mPixelSize + mPixelSize);

			quadNew[0].color = CL_EMPTY;
			quadNew[1].color = CL_EMPTY;
			quadNew[2].color = CL_EMPTY;
			quadNew[3].color = CL_EMPTY;
		}
	}
}

grid::~grid() {
	for (size_t i = 0; i < mGridSize; i++) {
		delete(mValues[i]);
	}
}

void grid::step() {
	mValues_copy = mValues;

	for (size_t y = 0; y < mHeight; y++) {
		for (size_t x = 0; x < mWidth; x++) {
			pixel px = (*this->getPixel(x, y));

			switch (px.getId()) {
			case(px_sand): {
				//sand update
				pixel* px_under = this->getPixel(x, y + 1);

				if (px_under != nullptr && px_under->getId() == px_empty) {
					swapPixels(getIterator(x, y), getIterator(x, y + 1), mValues_copy);					
					continue;
				}
				
				pixel* px_underL = this->getPixel(x - 1, y + 1);
				if (px_underL != nullptr && px_underL->getId() == px_empty) {
					swapPixels(getIterator(x, y), getIterator(x - 1, y + 1), mValues_copy);
					continue;
				}

				pixel* px_underR = this->getPixel(x + 1, y + 1);
				if (px_underR != nullptr && px_underR->getId() == px_empty) {
					swapPixels(getIterator(x, y), getIterator(x + 1, y + 1), mValues_copy);
					continue;
				}			
			}
						 break;
			case(px_water):
				//water update

				break;
			}
		}
	}

	mValues = mValues_copy;
}

void grid::swapPixels(int pI1, int pI2, std::vector<pixel*>& pValues) {	
	pixel* px1 = (pValues[pI1]);
	pixel* px2 = (pValues[pI2]);

	pValues[pI1] = px2;
	pValues[pI2] = px1;

	sf::Color color1;
	sf::Color color2;
	sf::Vertex* quad1 = &mQuads[pI1 * 4];
	color1 = quad1[0].color;

	sf::Vertex* quad2 = &mQuads[pI2 * 4];
	color2 = quad2[0].color;

	quad1[0].color = color2;
	quad1[1].color = color2;
	quad1[2].color = color2;
	quad1[3].color = color2;

	quad2[0].color = color1;
	quad2[1].color = color1;
	quad2[2].color = color1;
	quad2[3].color = color1;
}

void grid::drawPixel(int pX, int pY, pixel_type pType) {
	//update values
	this->getPixel(pX, pY)->setId(pType);

	//update vertex array
	sf::Vertex* quadNew = &mQuads[getIterator(pX, pY) * 4];

	switch (pType) {
	case(px_empty):  
		setQuadColor(pX, pY, CL_EMPTY);
		break;
	case(px_sand):
		setQuadColor(pX, pY, getSandColor());
		break;
	case(px_water):
		setQuadColor(pX, pY, CL_WATER);
		break;
	}	
}

void grid::setQuadColor(int pX, int pY, sf::Color pC) {
	sf::Vertex* quadNew = &mQuads[getIterator(pX, pY) * 4];
	quadNew[0].color = pC;
	quadNew[1].color = pC;
	quadNew[2].color = pC;
	quadNew[3].color = pC;
}

//void updateVertexPixel(int pI, )

void grid::render(sf::RenderTarget& mWindow) {
	mWindow.draw(mQuads);
}

sf::Color grid::getSandColor() {
	int r = rndSand(rng);
	switch (r) {
	case(0): return sf::Color(217, 187, 132, 255); break;
	case(1): return sf::Color(242, 214, 179, 255); break;
	case(2): return sf::Color(191, 135, 86, 255); break;
	case(3): return sf::Color(217, 179, 145, 255); break;
	case(4): return sf::Color(166, 96, 56, 255); break;
	}
}