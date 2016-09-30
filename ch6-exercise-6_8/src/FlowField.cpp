#include "FlowField.h"

FlowField::FlowField() {
}

FlowField::~FlowField() {
    if (field != nullptr) {
        delete[] field;
        field = nullptr;
    }
}

void FlowField::initWithImage(ofImage img) {
    this->gridSize = (int) (ofGetWidth() / img.getWidth());
    halfGridSize = gridSize / 2;
    columns = (int) img.getWidth();
    rows = (int) img.getHeight();

    fieldSize = img.getPixels().size();
    field = new ofVec2f[fieldSize];

    int i = 0;
    float angle;
    while (i < img.getPixels().size()) {
        angle = ofMap(img.getPixels().getColor(i).getBrightness(), 0, 255, 0, TWO_PI);
        field[i].x = cosf(angle);
        field[i].y = sinf(angle);
        ++i;
    }
}

void FlowField::update() {
}

void FlowField::display() {
    if (field != nullptr) {
        ofPushStyle();
        ofSetColor(200, 0, 0);
        ofNoFill();
        ofSetLineWidth(1.f);

        float l = (gridSize - 2) / 2.f, theta;
        int i = 0, c, r;
        while (i < fieldSize) {
            c = i % columns;
            r = i / columns;
            theta = ofRadToDeg(atan2(field[i].y, field[i].x));

            ofPushMatrix();
            ofTranslate(c * gridSize + halfGridSize, r * gridSize + halfGridSize);
            ofRotate(theta);
            ofDrawLine(-l, 0, l, 0);
            ofDrawLine(l, 0, l - 3, -3);
            ofDrawLine(l, 0, l - 3, 3);
            ofPopMatrix();

            ++i;
        }

        ofPopStyle();
    }
}





















