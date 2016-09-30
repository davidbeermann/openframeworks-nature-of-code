#pragma once

#include "ofMain.h"

class Vehicle {
public:
    Vehicle();
    // class constructor with initial location of the vehicle
    Vehicle(float, float);
    void update();
    void display();
    // method to apply forces to our vehicle
    void applyForce(ofVec2f);
    // function to show/hide wandering calculation graphics
    void toggleWanderingGraphics();
    // function to show/hide windows borders
    void toggleBorderDisplay();
private:
    void drawBorders();
    void drawWanderingGraphics();
    void drawVehicle();
    // method which receives the target to seek to.
    void wander(ofVec2f);
    // method to calculate steering force in order not to hit the window borders.
    void repelFromBorder(ofVec2f);
    // since this example's context is the 2D space
    // I chose the vector class accordingly.
    ofVec2f location;
    ofVec2f velocity;
    ofVec2f acceleration;
    // maximum speed for the desired velocity.
    float maxSpeed;
    // limit to the magnitude of the steering force.
    // creates a characteristic steering ability.
    float maxForce;
    // size of the vehicle
    float size;
    // the current angle for the calculation of the polar coordinates
    float angle;
    // the fixed maximum offset by which the angle can change on each iteration
    float angleOffset;
    // the radius for the calculation of the polar coordinates
    float polarRadius;
    // vectors storing the position of the origin for the polar coordinates
    // and the final target, which affect the desired velocity.
    ofVec2f polarAnchor;
    ofVec2f polarTarget;
    // state of the display of the wandering graphics.
    bool showWanderingGfx;
    // state whether to show window borders
    bool showWindowBorders;
    // definition of window borders
    float borderWidth;
    ofRectangle borderRect;
};
