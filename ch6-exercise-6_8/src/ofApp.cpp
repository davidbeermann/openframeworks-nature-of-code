#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    // load image pixel data
    image.load(ofToDataPath("kinect-depth.jpg"));

    // convert the image into low resolution gray scale image
    // ------------------------------------------------------
    // calculate low res image size
    int sizeW = (int) image.getWidth() / resolution;
    int sizeH = (int) image.getHeight() / resolution;
    ofLog() << "low res image size -> " << sizeW << "x" << sizeH;
    // allocate memory for image
    lowRes.allocate(sizeW, sizeH, OF_IMAGE_GRAYSCALE);
    // set gray scale colors based on average brightness
    int i = 0;
    int startX, startY;
    float brightness = 0.f;
    while (i < lowRes.getPixels().size()) {
        // calculate start coordinates on full res image
        startX = (i % sizeW) * resolution;
        startY = (i / sizeW) * resolution;
//        ofLog() << i << ":" << startX << "x" << startY;
        // calculate average brightness over full res image quadrant
        for (int y = 0; y < resolution; ++y) {
            for (int x = 0; x < resolution; ++x) {
                brightness += image.getPixels().getColor(startX + x, startY + y).getBrightness();
            }
        }
        brightness /= resolution * resolution;
        // set correct low res gray scale color based on brightness
        lowRes.getPixels().setColor(i, ofColor(brightness));
        // reset brightness
        brightness = 0.f;
        // go on to next low res pixel
        ++i;
    }
    // IMPORTANT: update low res image after changes to pixels
    lowRes.update();

    // initialize flow field with image
    flowField.initWithImage(lowRes);

////    ofPixels lowResPixels = lowRes.getPixels();
//    int i = 0;
//    while ( i < lowRes.getPixels().size() ) {
//        lowRes.getPixels().setColor(i, ofFloatColor((i%(int)lowRes.getWidth())/lowRes.getWidth())); //abs(sin( float(i) / 18.f)) * 255.f; // make some op-art
//        i++;
//    }
////    lowRes.setFromPixels(lowResPixels);
//    lowRes.update();
//
//
//
//    // convert image colors into gray scale colors
////    ofFloatColor rgb, gray;
////    float sumBrightness = 0.f, averageBrightness = 0.f;
////    for (int r = 0; r < sizeH; ++r) {
////        for (int c = 0; c < sizeW; ++c) {
//            for (int yy = 0; yy < resolution; ++yy) {
//                for (int xx = 0; xx < resolution; ++xx) {
//                    image.getPixels().setColor(xx, yy, ofColor(255,0,0));
////                    rgb = image.getColor(c + i, r + j);
////                    sumBrightness += rgb.getBrightness();
//                }
//            }
//            image.update();
////            averageBrightness = sumBrightness / (resolution * resolution);
////            gray.set(averageBrightness);
////            gray.set(0.5, 1.0);
////            lowRes.setColor(r+c, ofFloatColor(0.5f, 1.0f));
////            sumBrightness = 0.f;
////        }
////    }
////    lowRes.update();
}

//--------------------------------------------------------------
void ofApp::update() {


}

//--------------------------------------------------------------
void ofApp::draw() {
    image.draw(0, 0);
//    lowRes.draw(0, 0);
    lowRes.draw(0, 0, ofGetWidth(), ofGetHeight());
    flowField.display();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
