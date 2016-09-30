#pragma once

#include "ofMain.h"

class Vehicle {
public:
    Vehicle();
    // class constructor with initial location of the vehicle
    Vehicle(float, float);
    void update();
    void display();
    // method which receives the target to seek to.
    void arrive(ofVec2f);
    // method to apply forces to our vehicle
    void applyForce(ofVec2f);
private:
    void drawVehicle();
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
};
