#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(240);
    for (int i = 0; i < vehicleCount; ++i) {
        vehicles.push_back(Vehicle(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
    }
//    vehicle.setLocation(ofGetWidth()/2, ofGetHeight()/2);
}

//--------------------------------------------------------------
void ofApp::update(){
    // Nice trick to display the current frame rate in the application window.
    // Source: https://gist.github.com/izmhr/faa47662a3df8f4acd91
    stringstream strm;
    strm << "fps: " << (int)ofGetFrameRate();
    ofSetWindowTitle(strm.str());
    // update flow field over time
    flowField.update();
    // update all vehicles
    for (int i = 0; i < vehicleCount; ++i) {
        vehicles[i].follow(&flowField);
        vehicles[i].update();
    }
//    vehicle.follow(&flowField);
//    vehicle.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    flowField.display();
    for (int i = 0; i < vehicleCount; ++i) {
        vehicles[i].display();
    }
//    vehicle.display();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}
