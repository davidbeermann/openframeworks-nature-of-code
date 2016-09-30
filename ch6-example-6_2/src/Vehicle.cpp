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
    drawVehicle();
    ofPopMatrix();
}

void Vehicle::arrive(ofVec2f target) {
    // calculate the vector for the desired direction towards the target.
    ofVec2f desired = target - location;
    // store the length/magnitude of the desired vector
    float d = desired.length();
    // apply the maximum speed to the vector
    desired.normalize();
    // calculate maximum speed based on the distance to the target
    if(d < 100) {
        // linearly map the distance to the target to values between 0 and maximum speed.
        float m = ofMap(d, 0, 100, 0, maxSpeed);
        desired *= m;
    } else {
        desired *= maxSpeed;
    }
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

void Vehicle::drawVehicle() {
    ofPoint p1 = ofPoint(0, -size*2);
    ofPoint p2 = ofPoint(-size, size*2);
    ofPoint p3 = ofPoint(size, size*2);
    ofPushStyle();
    ofSetColor(125);
    ofFill();
    ofSetLineWidth(0);
    ofBeginShape();
    ofVertex(p1);
    ofVertex(p2);
    ofVertex(p3);
    ofEndShape(true);
    ofSetColor(33);
    ofNoFill();
    ofSetLineWidth(1);
    ofBeginShape();
    ofVertex(p1);
    ofVertex(p2);
    ofVertex(p3);
    ofEndShape(true);
    ofPopStyle();
}







