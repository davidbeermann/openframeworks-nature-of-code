#include "Vehicle.h"

Vehicle::Vehicle() : Vehicle(0, 0) {
}

Vehicle::Vehicle(float x, float y) {
    // initialization of private properties.
    location.set(x, y);
    velocity.set(0, 0);
    acceleration.set(0, 0);
    // arbitrary values for speed and force. Try varying these!
    maxSpeed = 2.0f;
    maxForce = 0.1f;
    size = 5.0f;
}

void Vehicle::setLocation(ofVec2f l) {
    location.set(l);
}

void Vehicle::setLocation(float x, float y) {
    location.set(x, y);
}

void Vehicle::update() {
    if(location.x < 0) {
        location.x = ofGetWidth();
    } else if(location.x > ofGetWidth()) {
        location.x = 0;
    }
    if(location.y < 0) {
        location.y = ofGetHeight();
    } else if(location.y > ofGetHeight()) {
        location.y = 0;
    }
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
    ofPushMatrix();
    // transform canvas
    ofTranslate(location);
    // since the heading() method does not exist in oF, here's a analogous implementation of the logic:
    // formula from here: http://stackoverflow.com/questions/6247153/angle-from-2d-unit-vector
    float theta = ofRadToDeg(atan2(velocity.y, velocity.x)) + 90.f;
    ofRotate(theta);
    // draw vehicle
    drawVehicle();
    ofPopMatrix();
}

void Vehicle::follow(FlowField* field) {
    // get the field vector corresponding the vehicle's location
    ofVec2f desired = field->lookup(&location);
    desired.normalize();
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
    // calculate corner points of vehicle
    ofPoint p1 = ofPoint(0, -size*2);
    ofPoint p2 = ofPoint(-size, size*2);
    ofPoint p3 = ofPoint(size, size*2);
    // start new style
    ofPushStyle();
    // draw vehicle
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
    // remove style
    ofPopStyle();
}




























