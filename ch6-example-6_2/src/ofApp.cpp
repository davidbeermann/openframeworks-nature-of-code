#include "ofApp.h"

void ofApp::setup(){
    ofSetFrameRate(FRAME_RATE);
    ofBackground(240);
    ofSetCircleResolution(50);
    vehicle = new Vehicle(400.f, 100.f);
}

void ofApp::update(){
    vehicle->arrive(target);
    vehicle->update();
    // Nice trick to display the current frame rate in the application window.
    // Source: https://gist.github.com/izmhr/faa47662a3df8f4acd91
    stringstream strm;
    strm << "fps: " << (int)ofGetFrameRate();
    ofSetWindowTitle(strm.str());
}

void ofApp::draw(){
    drawTarget();
    vehicle->display();
}

void ofApp::mouseMoved(int x, int y ){
    target.set(x, y);
}

void ofApp::drawTarget() {
    ofPushStyle();
    ofSetColor(200);
    ofFill();
    ofSetLineWidth(0);
    ofDrawCircle(target, 20);
    ofSetColor(33);
    ofNoFill();
    ofSetLineWidth(2);
    ofDrawCircle(target, 20);
    ofPopStyle();
}

