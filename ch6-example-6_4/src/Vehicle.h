#pragma once

#include "ofMain.h"
#include "FlowField.h"

class Vehicle {
public:
    Vehicle();
    // class constructor with initial location of the vehicle
    Vehicle(float, float);
    void setLocation(ofVec2f);
    void setLocation(float, float);
    void update();
    void display();
    // method to follow the flow fields vectors
    void follow(FlowField*);
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
