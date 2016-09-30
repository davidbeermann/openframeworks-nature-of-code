#pragma once

#include "ofMain.h"

class FlowField {
public:
    FlowField();
    ~FlowField();
    void initWithImage(ofImage);
    void update();
    void display();
private:
    int gridSize;
    float halfGridSize;
    int rows;
    int columns;
    int fieldSize;
    ofVec2f *field = nullptr;
};
