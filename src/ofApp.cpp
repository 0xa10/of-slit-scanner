#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("camshadez");
    camWidth = 640;  // try to grab at this size.
    camHeight = 480;
    //ofSetWindowShape(camWidth, camHeight);
    ofSetFrameRate(60);

    //get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();

    for(size_t i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable) {
            //log the device
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        } else {
            //log the device and note it as unavailable
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }

    fbo.allocate(camWidth, camHeight, GL_RGB);

    zOffset = 0;
    depth = 128; 

    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(camWidth, camHeight);

    frameCube.allocate(camWidth, camHeight, depth, GL_RGB);

    //shader.load("", "shader/shader.frag");
    shader.load("shader/shader");
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    frameCube.loadData(vidGrabber.getPixels(), 1, 0, 0, zOffset);
    zOffset = (zOffset + 1) % depth;
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
        shader.begin();
            shader.setUniform1f("u_time", ofGetElapsedTimef());
            shader.setUniform2f("u_resolution", camWidth, camHeight);
            shader.setUniform1f("u_depth", depth);
            shader.setUniform1f("u_zoffset", zOffset);
            // 3d texture somehow is bound already...
            ofDrawRectangle(0,0, camWidth, camHeight);
        shader.end();
    fbo.end();

    fbo.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
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

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
