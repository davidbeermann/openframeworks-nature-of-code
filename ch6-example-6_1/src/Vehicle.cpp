#include "Vehicle.h"

Vehicle::Vehicle() : Vehicle(0, 0) {
}

Vehicle::Vehicle(float x, float y) {
    // initialization of private properties.
    location.set(x, y);
    velocity.set(0, 0);
    acceleration.set(0, 0);
    // arbitrary values for speed and force. Try varying these!
    maxSpeed = 4.0f;
    maxForce = 0.1f;
    size = 5.0f;
}

void Vehicle::update() {
    // add acceleration to velocity
    velocity += acceleration;
    // limit velocity to maximum speed
    velocity.limit(maxSpeed);
    // add velocity to location
    location += velocity;
    // reset acceleration vector
    acceleration *= 0;
}

void Vehicle::display() {
    // since the heading() method does not exist in oF, here's a analogous implementation of the logic:
    // formula from here: http://stackoverflow.com/questions/6247153/angle-from-2d-unit-vector
    float theta = ofRadToDeg(atan2(velocity.y, velocity.x)) + 90.f;
    ofPushMatrix();
    ofTranslate(location);
    ofRotate(theta);
    ofSetColor(125);
    ofFill();
    ofSetLineWidth(0);
    ofBeginShape();
    ofVertex(0, -size*2);
    ofVertex(-size, size*2);
    ofVertex(size, size*2);
    ofEndShape(true);
    ofSetColor(33);
    ofNoFill();
    ofSetLineWidth(1);
    ofBeginShape();
    ofVertex(0, -size*2);
    ofVertex(-size, size*2);
    ofVertex(size, size*2);
    ofEndShape(true);
    ofPopMatrix();
}

void Vehicle::seek(ofVec2f target) {
    // calculate the vector for the desired direction towards the target.
    ofVec2f desired = target - location;
    // apply the maximum speed to the vector
    desired.normalize();
    desired *= maxSpeed;
    // calculate the vector for the next step/iteration towards the target (steering force)
    ofVec2f steer = desired - velocity;
    // apply limit in magnitude to steering force
    steer.limit(maxForce);
    // apply the steering force
    applyForce(steer);
}

void Vehicle::applyForce(ofVec2f force) {
    // Newton's second law - divide by mass if wanted
    acceleration += force;
}





