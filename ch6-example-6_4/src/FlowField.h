#pragma once

#include "ofMain.h"

class FlowField {
public:
    FlowField();
    FlowField(int);
    ~FlowField();
    void update();
    void display();
    ofVec2f lookup(ofVec2f*);
private:
    int resolution;
    float halfResolution;
    int rows;
    int columns;
    ofVec2f *field;
    void initFieldWithUnidirectionalVectors();
    void initFieldWithRandomVectors();
    void initFieldWithPerlinNoiseVectors();
    void initFieldWithVectorsPointingToTheMiddle();
    ofVec2f *getFieldVector(int, int);
    void setFieldVector(int, int, ofVec2f);
};
