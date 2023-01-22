//
// Created by Hunter on 11/24/2020.
//

#ifndef AGARIO_FINAL_H
#define AGARIO_FINAL_H
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>                    // include the SFML Graphics Library
using namespace sf;
class circle{
public:
    void initialize();
    void setRadius(int);
    int getCircleX();
    int getCircleY();
    int getRadius();
    void setUserPos(int);
    void setCircleOff();
    int centerOfCircleX();
    int centerOfCircleY();
    int getCircleOff();
    void changeRadius(int);
    void updateCircle(circle&, RenderWindow&, int, int, Color,int);
private:
    int _xPosition;
    int _yPosition;
    int _x;
    int _r;
    int _circleOff = 0;
    CircleShape shapeCircle1;
};
#endif //AGARIO_FINAL_H
