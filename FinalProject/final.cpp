#include <SFML/Graphics.hpp>
#include "final.h"
#include <iostream>
#include <cmath>
using namespace sf;
using namespace std;
// Randomize the starting position of all the circles
void circle::initialize(){
    int x = rand()%3500+1;
    int y = rand()%1800+1;
    _xPosition = x;
    _yPosition = y;
}
// Getter function for x position
int circle::getCircleX(){
    return _xPosition;
}
// Getter function for y position
int circle::getCircleY(){
    return _yPosition;
}
// Set the radius
void circle::setRadius(int radius){
    _r = radius;
}
// Get the radius
int circle::getRadius(){
    return _r;
}
// Set the position of the user
void circle::setUserPos(int direction){
    if (direction == 1)
        _xPosition += 5;
    else if (direction == 2){
        _xPosition-=5;
    }
    else if (direction == 3){
        _yPosition+=5;
    }
    else if (direction == 4){
        _yPosition-=5;
    }
    else if (direction == 5){
        _xPosition-=5;
        _yPosition-=5;
    }
    else if (direction == 6){
        _xPosition+=5;
        _yPosition-=5;
    }
    else if (direction == 7){
        _xPosition-=5;
        _yPosition+=5;
    }
    else if (direction == 8){
        _xPosition+=5;
        _yPosition+=5;
    }
    if (_xPosition >3500)
        _xPosition-=5;
    if (_xPosition < 0)
        _xPosition+=5;
    if (_yPosition > 1800)
        _yPosition-=5;
    if (_yPosition < 0)
        _yPosition+=5;
}
// set the circle to a position off the map and stop running their movement
void circle::setCircleOff(){
    _circleOff = 1;
    _xPosition = 4000;
    _yPosition = 4000;
}
// Get the x position of the center of the circle
int circle::centerOfCircleX(){
    return _xPosition + _r;;
}
// Get the y position of the center of the circle
int circle::centerOfCircleY(){
    return _yPosition + _r;;
}
// returns the number that puts the circles off the screen
int circle::getCircleOff(){
    return _circleOff;
}
// change the user radius after eating a circle
void circle::changeRadius(int radius){
    int area = 3.14 * radius * radius;
    int newArea = 3.14 * _r * _r;
    int newestArea = area + newArea;
    int newRadius = sqrt(newestArea/3.14);
    _r = newRadius;
}
// move the circles
void circle::updateCircle(circle& circle1, RenderWindow& window, int radius1, int RandNum, Color color, int i){
    _r = radius1;
    // randum number to say when the circle should change directions
    if (RandNum == i){
        // randum distance
        int randDistance = rand()%8;
        _x = randDistance;
        int newRand = 1;
        // move the circles by 1 in a certain direction
        if (_x == 0)
            _xPosition+=newRand;
        else if (_x == 1)
            _xPosition+=-newRand;
        else if (_x == 2)
            _yPosition+=newRand;
        else if (_x == 3)
            _yPosition+=-newRand;
        else if (_x == 4){
            _xPosition+=newRand;
            _yPosition+=newRand;
        }else if (_x == 5){
            _xPosition+=newRand;
            _yPosition+=-newRand;
        }else if (_x == 6){
            _xPosition+=-newRand;
            _yPosition+=newRand;
        }else if (randDistance == 7){
            _xPosition+=-newRand;
            _yPosition+=-newRand;
        }
        if (_xPosition >= 3500-_r)
            _xPosition-=1;
        else if (_xPosition <= 0)
            _xPosition+=1;
        if (_yPosition >= 1800-_r)
            _yPosition-=1;
        else if (_yPosition <= 0)
            _yPosition+=1;
        // draw the circle
        shapeCircle1.setPosition(_xPosition, _yPosition);
        shapeCircle1.setRadius(_r);
        shapeCircle1.setFillColor(color);
        window.draw(shapeCircle1);
    }else {
        // same as before but this keeps movement in the same direction
        _r = radius1;
        int newRand = 1;
        if (_x == 0)
            _xPosition+=newRand;
        else if (_x == 1)
            _xPosition+=-newRand;
        else if (_x == 2)
            _yPosition+=newRand;
        else if (_x == 3)
            _yPosition+=-newRand;
        else if (_x == 4){
            _xPosition+=newRand;
            _yPosition+=newRand;
        }else if (_x == 5){
            _xPosition+=newRand;
            _yPosition+=-newRand;
        }else if (_x == 6){
            _xPosition+=-newRand;
            _yPosition+=newRand;
        }else if (_x == 7){
            _xPosition+=-newRand;
            _yPosition+=-newRand;
        }
        if (_xPosition >= 3500-(_r*2)) {
            _xPosition -= 1;
            _x = rand()%8;
        }
        else if (_xPosition <= 0) {
            _xPosition += 1;
            _x = rand()%8;
        }
        if (_yPosition >= 1800-(_r*2)) {
            _yPosition -= 1;
            _x = rand()%8;
        }
        else if (_yPosition <= 0) {
            _yPosition += 1;
            _x = rand()%8;
        }
        shapeCircle1.setPosition(_xPosition, _yPosition);
        shapeCircle1.setRadius(_r);
        shapeCircle1.setFillColor(color);
        window.draw(shapeCircle1);
    }
}