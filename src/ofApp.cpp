#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("camshadez");
    camWidth = 480;  // try to grab at this size.
    camHeight = 360;
    //ofSetFrameRate(30);

    fbo.allocate(camWidth, camHeight, GL_RGB);

    zOffset = 0;
    depth = 22; 

    vidGrabber.load("/tmp/target.mp4");
    vidGrabber.play();

    singleTexture.allocate(camWidth, camHeight, GL_RGB);
    frame.allocate(camWidth, camHeight, GL_RGB);
    pframe.allocate(camWidth, camHeight, GL_RGB);
    frameCube.allocate(camWidth, camHeight, depth, GL_RGB);

    //shader.load("", "shader/shader.frag");
    shader.load("shader/shader");
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    zOffset = (zOffset + 1) % depth;
}

//--------------------------------------------------------------
void ofApp::draw(){
    frame.allocate(camWidth, camHeight, GL_RGB);
    frame.begin();
        vidGrabber.draw(0,0);
    frame.end();

    frame.readToPixels(pframe);
    frameCube.loadData(pframe, 1, 0, 0, zOffset);
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
