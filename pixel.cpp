#include "pixel.h"
pixel::pixel() {
	mId = px_empty;
	mColor = CL_EMPTY;
}

void pixel::setId(pixel_type pType) {
	mId = pType;
	mVelocity = sf::Vector2f(0, 0);

	switch (mId) {
	case(px_empty):		
		mColor = CL_EMPTY;
		break;

	case(px_sand) :
		mColor = CL_SAND;
		break;

	case(px_water):
		mColor = CL_WATER;
		break;
	}
}