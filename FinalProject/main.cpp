// Hunter Adam
// 12/8/2020
// Agario simulator
// CSCI 261 section A
#include <iostream>
#include "final.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <unistd.h>
using namespace sf;
using namespace std;


int main() {
    // start of game instructions
    cout << "The game will start in 15 seconds" << endl;
    cout << "Please maximize the window when you enter in order to see the full map. " << endl;
    cout << "The object of the game is to eat the circles smaller than you while avoiding the circles that are bigger."
         << endl;
    cout << "To move up, down, left or right, use the arrow keys" << endl;
    cout << "To move diagonally, use the letters Q, E, A, and D. " << endl;
    // allow for user to read instructions
    sleep(1);
    // check to see if the file is open. If it is not open, open it.
    int firstTime = 0;
    ifstream fileIn;
    fileIn.open("scoreSheet.txt");
    if (fileIn.fail()) {
        ofstream fileOut;
        fileOut.open("scoreSheet.txt");
        if (fileOut.fail()) {
            cout << "error" << endl;
            return -1;
        }
        firstTime = 1;
        fileOut << 0 << endl << 0;
        fileOut.close();
        fileIn.open("scoreSheet.txt");
    }
    int numEaten = 0;
    // create 10 different circles all stored in a vector
    vector<circle>circles(10);
    circle userCircle;
    int direction = 0;
    int randNum;
    //radius of circles
    const vector<int> radius {8,11,15,20,27,37,52,72,100,140};
    // the circle colors
    Color colorOne(255,0,0);
    Color colorTwo(0,0,255);
    Color colorThree(0,255,0);
    Color colorFour(255,100,0);
    Color colorFive(255,105,180);
    Color colorSix(128,0,128);
    Color colorSeven(255,255,0);
    Color colorEight(128,0,0);
    Color colorNine(0, 255, 255);
    Color colorTen(34,139,34);
    // put the colors into a vector
    const vector<Color>colors {colorOne,colorTwo,colorThree,colorFour,colorFive,colorSix,colorSeven,colorEight,colorNine,colorTen};
    const int userRadius = 10;
    // create window
    RenderWindow window(VideoMode(3500, 1800), "SFML Example Window");
    srand(time(0));
    rand();
    // set the radius of the user
    userCircle.setRadius(userRadius);
    // initialize the user circle
    userCircle.initialize();
    // initialize the circles positions
    for (int i = 0; i<10;i++){
        circles.at(i).initialize();
    }
    // set the framerate of the window
    window.setFramerateLimit(100);
    rand();
    // start loop counter
    int clock = 0;
    while (window.isOpen()) {
        // random number that changes the direction of the circles
        randNum = rand() % 200;
        window.clear(Color::Black);
        // user circle
        CircleShape shapeUserCircle;
        shapeUserCircle.setPosition(userCircle.getCircleX(), userCircle.getCircleY());
        shapeUserCircle.setRadius(userCircle.getRadius());
        shapeUserCircle.setFillColor(Color::White);
        window.draw(shapeUserCircle);
        // change the circles' positions
        for (int i = 0; i<10;i++){
            if (circles.at(i).getCircleOff() == 0) {
                circles.at(i).updateCircle(circles.at(i), window, radius.at(i), randNum, colors.at(i),i+1);
            }
        }
        // update the center of the circle
        userCircle.centerOfCircleX();
        userCircle.centerOfCircleY();
        // check for user circle touching other circles
        for (int i = 0; i<10;i++){
            if ((abs(circles.at(i).centerOfCircleX() - userCircle.centerOfCircleX()) < userCircle.getRadius()) &&
                (abs(circles.at(i).centerOfCircleY() - userCircle.centerOfCircleY()) < userCircle.getRadius())) {
                if (userCircle.getRadius() > circles.at(i).getRadius()) {
                    userCircle.changeRadius(circles.at(i).getRadius());
                    circles.at(i).setCircleOff();
                    numEaten++;
                }
            }
            if ((abs(circles.at(i).centerOfCircleX() - userCircle.centerOfCircleX()) < circles.at(i).getRadius()) &&
                (abs(circles.at(i).centerOfCircleY() - userCircle.centerOfCircleY()) < circles.at(i).getRadius())) {
                if (userCircle.getRadius() < circles.at(i).getRadius()) {
                    sleep(1);
                    window.close();
                }
            }
        }
        clock++;
        window.display();
        Event event;
        // events for user to move circle and to close window
        while (window.pollEvent(event)) {      // ask the window if any events occurred
            if (event.type == Event::Closed) { // if event type is a closed event
                // i.e. they clicked the X on the window
                window.close();                 // then close our window
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Right) {
                    direction = 1;
                    userCircle.setUserPos(direction);
                }
                if (event.key.code == Keyboard::Left) {
                    direction = 2;
                    userCircle.setUserPos(direction);
                }
                if (event.key.code == Keyboard::Down) {
                    direction = 3;
                    userCircle.setUserPos(direction);
                }
                if (event.key.code == Keyboard::Up) {
                    direction = 4;
                    userCircle.setUserPos(direction);
                }
                if (event.key.code == Keyboard::Q) {
                    direction = 5;
                    userCircle.setUserPos(direction);
                }
                if (event.key.code == Keyboard::E) {
                    direction = 6;
                    userCircle.setUserPos(direction);
                }
                if (event.key.code == Keyboard::A) {
                    direction = 7;
                    userCircle.setUserPos(direction);
                }
                if (event.key.code == Keyboard::D) {
                    direction = 8;
                    userCircle.setUserPos(direction);
                }
            }
        }
    }
    // record in other file
    int numEatenRecord;
    fileIn >> numEatenRecord;
    int clockRecord;
    fileIn >> clockRecord;
    fileIn.close();
    ofstream fileOut;
    fileOut.open("scoreSheet.txt");

    if (firstTime == 1){
        fileOut << numEaten << endl;
        fileOut << clock;
        cout << "The new record is " << numEaten << " circles eaten in " << clock << " loops" << endl;
    }
    else if (numEatenRecord < numEaten) {
        fileOut << numEaten << endl;
        fileOut << clock;
        cout << "You just broke the record of " << numEatenRecord << " circles eaten in " << clockRecord << " loops" << endl
             << "The new record is " << numEaten << " circles eaten in " << clock << " loops" << endl;
    }else if (numEaten == numEatenRecord) {
        if (clockRecord > clock) {
            fileOut << numEatenRecord << endl;
            fileOut << clock;
            cout << "You just broke the record of " << numEatenRecord << " circles eaten in " << clockRecord << " loops" << endl
                 << "The new record is " << numEaten << " circles eaten in " << clock << " loops" << endl;
        }else if (clock > clockRecord){
            fileOut << numEatenRecord << endl;
            fileOut << clockRecord;
            cout << "You did not beat the record of " << numEatenRecord << " circles eaten in " << clockRecord << " loops" << endl
            << "Your score was " << numEaten << " circles eaten in " << clock << " loops" << endl;
        }
    }else{
        fileOut << numEatenRecord << endl;
        fileOut << clockRecord;
        cout << "You did not beat the record of " << numEatenRecord << " circles eaten in " << clockRecord << " loops" << endl
             << "Your score was " << numEaten << " circles eaten in " << clock << " loops" << endl;
    }
    return 0;
}

