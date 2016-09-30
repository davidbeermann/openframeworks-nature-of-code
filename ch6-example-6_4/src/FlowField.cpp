#include "FlowField.h"

FlowField::FlowField() : FlowField(10) {
    // call constructor with a default resolution of 10
}


FlowField::FlowField(int resolution) {
    this->resolution = resolution;
    halfResolution = resolution / 2.f;
    columns = ofGetWidth() / resolution;
    rows = ofGetHeight() / resolution;
    // solution with faster memory access
    // details here: http://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
    field = new ofVec2f[columns * rows];
    // set field vectors
//    initFieldWithUnidirectionalVectors();
//    initFieldWithRandomVectors();
    initFieldWithPerlinNoiseVectors();
//    initFieldWithVectorsPointingToTheMiddle();
}

FlowField::~FlowField() {
    delete[] field;
}

void FlowField::initFieldWithUnidirectionalVectors() {
    for (int c = 0; c < columns; ++c) {
        for (int r = 0; r < rows; ++r) {
            ofVec2f v = ofVec2f(1, 0);
            v.rotate(0.f); // rotate vectors by degree. default is 0.f
            setFieldVector(c, r, v);
        }
    }
}

void FlowField::initFieldWithRandomVectors() {
    for (int c = 0; c < columns; ++c) {
        for (int r = 0; r < rows; ++r) {
            float angle = ofRandom((float) TWO_PI);
            setFieldVector(c, r, ofVec2f(cosf(angle), sinf(angle)));
        }
    }
}

void FlowField::initFieldWithPerlinNoiseVectors() {
    float offInc = 0.05f;
    float xoff = 0;
    for (int c = 0; c < columns; ++c) {
        float yoff = 0;
        for (int r = 0; r < rows; ++r) {
            // Exercise 6.7
            // add third dimension to noise function to animate over time
            float angle = ofMap(ofNoise(xoff, yoff, ofGetElapsedTimef()), 0, 1, 0, TWO_PI);
            setFieldVector(c, r, ofVec2f(cosf(angle), sinf(angle)));
            yoff += offInc;
        }
        xoff += offInc;
    }
}

// Exercise 6.6
void FlowField::initFieldWithVectorsPointingToTheMiddle() {
    ofVec2f center = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    ofVec2f section;
    for (int c = 0; c < columns; ++c) {
        for (int r = 0; r < rows; ++r) {
            section.x = c * resolution + halfResolution;
            section.y = r * resolution + halfResolution;
            section = center - section;
            section.normalize();
            setFieldVector(c, r, section);
        }
    }
}

void FlowField::update() {
    // Exercise 6.7
    initFieldWithPerlinNoiseVectors();
}

void FlowField::display() {
    ofPushStyle();
    ofSetColor(200);
    ofNoFill();
    ofSetLineWidth(1.f);
    ofVec2f *v;
    float theta;
    float l = (resolution - 2) / 2.f;
    for (int c = 0; c < columns; ++c) {
        for (int r = 0; r < rows; ++r) {
            v = getFieldVector(c, r);
            theta = ofRadToDeg(atan2(v->y, v->x));
            ofPushMatrix();
            ofTranslate(c * resolution + halfResolution, r * resolution + halfResolution);
            ofRotate(theta);
            ofDrawLine(-l, 0, l, 0);
            ofDrawLine(l, 0, l - 3, -3);
            ofDrawLine(l, 0, l - 3, 3);
            ofPopMatrix();
        }
    }
    ofPopStyle();
}

ofVec2f FlowField::lookup(ofVec2f *position) {
    int column = (int)(position->x / resolution);
    int row = (int)(position->y / resolution);
    return ofVec2f(*getFieldVector(column,row));
}

ofVec2f *FlowField::getFieldVector(int column, int row) {
    return &field[row * columns + column];
}

void FlowField::setFieldVector(int column, int row, ofVec2f vector) {
    field[row * columns + column].x = vector.x;
    field[row * columns + column].y = vector.y;
}



















