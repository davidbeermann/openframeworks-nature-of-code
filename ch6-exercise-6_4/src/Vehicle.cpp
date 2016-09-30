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
    // set initial angle for walking direction
    angle = ofDegToRad((float)PI * 2.f);
    // the greater the offset, the more jittery the wandering motion.
    // try changing the value for 15.f to see differences.
    angleOffset = (float)PI / 15.f;
    polarRadius = 20.f;
    // show wandering gfx initially
    showWanderingGfx = true;
}

void Vehicle::update() {
    // keep wandering within window frame
    if(location.y < 0 || location.y > ofGetHeight()){
        location.y = location.y > ofGetHeight() ? 0 : ofGetHeight();
    }
    if(location.x < 0 || location.x > ofGetWidth()){
        location.x = location.x > ofGetWidth() ? 0 : ofGetWidth();
    }
    // add acceleration to velocity
    velocity += acceleration;
    // limit velocity to maximum speed
    velocity.limit(maxSpeed);
    // add velocity to location
    location += velocity;
    // reset acceleration vector
    acceleration *= 0;
    // add offset to current angle for next step
    angle += ofRandom(-angleOffset, angleOffset);
    // calculate vector, which acts as anchor point for the calculation of the polar coordinates
    // which then becomes the vector for the desired velocity.
    polarAnchor = velocity.getNormalized();
    polarAnchor *= size * 2 + polarRadius * 2;
    polarAnchor += location;
    // calculate the vector of the polar coordinates which affects the desired velocity.
    polarTarget.x = polarAnchor.x + cosf(angle) * polarRadius;
    polarTarget.y = polarAnchor.y + sinf(angle) * polarRadius;
    // go wander...
    wander(polarTarget);
}

void Vehicle::display() {
    ofPushMatrix();
    // draw wandering graphics BEFORE transforming the canvas
    if(showWanderingGfx) {
        drawWanderingGraphics();
    }
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

void Vehicle::wander(ofVec2f target) {
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

void Vehicle::drawWanderingGraphics() {
    ofPushStyle();
    ofSetColor(33);
    ofNoFill();
    ofSetLineWidth(1);
    ofDrawLine(location , polarAnchor);
    ofDrawCircle(polarAnchor, polarRadius);
    ofDrawLine(polarAnchor, polarTarget);
    ofSetColor(33);
    ofFill();
    ofSetLineWidth(0);
    ofDrawCircle(polarTarget, 3);
    ofPopStyle();
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

void Vehicle::toggleWanderingGraphics() {
    showWanderingGfx = !showWanderingGfx;
}














