#pragma once

#include "ofMain.h"
#include "Vehicle.h"

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	void keyReleased(int);
private:
    const int FRAME_RATE = 60;
	Vehicle* vehicle;
};
