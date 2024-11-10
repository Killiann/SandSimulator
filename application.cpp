#include "application.h"

application::application() : 
    mWindow(sf::VideoMode(gridWidth * pixelSize, gridHeight * pixelSize), "Sand Simulation"),
    mGrid(gridWidth, gridHeight, pixelSize) {
    timePerFrame = sf::seconds(1.f / loopRate);
}

void application::run() {

    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();

        //user input
        switch (event.type)
        {
        case(sf::Event::MouseButtonPressed):
            if (event.mouseButton.button == sf::Mouse::Left)
                if (!isHoldingMouseL) isHoldingMouseL = true;
            if (event.mouseButton.button == sf::Mouse::Right)
                if (!isHoldingMouseR) isHoldingMouseR = true;
            break;

        case(sf::Event::MouseButtonReleased):
            if (event.mouseButton.button == sf::Mouse::Left)
                if (isHoldingMouseL)
                    isHoldingMouseL = false;
            if (event.mouseButton.button == sf::Mouse::Right)
                if (isHoldingMouseR)
                    isHoldingMouseR = false;               
            break;
        }
    }    

    timeSinceLastFrame += clock.restart();
    if (timeSinceLastFrame > timePerFrame) {
        timeSinceLastFrame -= timePerFrame;

        //drawing update
        if (isHoldingMouseL) {
            sf::Vector2i mousePos = mouse.getPosition(mWindow);

            //if mouse is in bounds of grid
            if (mousePos.x > 0 &&
                mousePos.x < (gridWidth * pixelSize) &&
                mousePos.y > 0 &&
                mousePos.y < gridHeight * pixelSize) {

                mGrid.drawPixel(mousePos.x / pixelSize, mousePos.y / pixelSize, px_sand);
            }
        }

        if (isHoldingMouseR) {
            sf::Vector2i mousePos = mouse.getPosition(mWindow);

            //if mouse is in bounds of grid
            if (mousePos.x > 0 &&
                mousePos.x < (gridWidth * pixelSize) &&
                mousePos.y > 0 &&
                mousePos.y < gridHeight * pixelSize) {

                mGrid.drawPixel(mousePos.x / pixelSize, mousePos.y / pixelSize, px_water);
            }
        }

        mGrid.step();
    }

    render();
}

void application::render() {
    mWindow.clear();
    mGrid.render(mWindow);
    mWindow.display();
}

void application::end() {

}