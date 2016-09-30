#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(FRAME_RATE);
    ofBackground(240);
    ofSetCircleResolution(50);
    vehicle = new Vehicle(400.f, 100.f);
}

void ofApp::update(){
    // Nice trick to display the current frame rate in the application window.
    // Source: https://gist.github.com/izmhr/faa47662a3df8f4acd91
    stringstream strm;
    strm << "fps: " << (int)ofGetFrameRate();
    ofSetWindowTitle(strm.str());
    // update vehicle
    vehicle->update();
}

void ofApp::draw(){
    // display vehicle
    vehicle->display();
}

void ofApp::keyReleased(int key) {
    if(key == 'w') {
        vehicle->toggleWanderingGraphics();
    } else if(key == 'b') {
        vehicle->toggleBorderDisplay();
    }
}


