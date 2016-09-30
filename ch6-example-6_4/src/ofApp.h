#pragma once

#include "ofMain.h"
#include "FlowField.h"
#include "Vehicle.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
private:
    FlowField flowField = FlowField(20);
    vector<Vehicle> vehicles;
    int vehicleCount = 100;
    Vehicle vehicle;
};
