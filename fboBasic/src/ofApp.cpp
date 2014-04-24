#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    fbo.allocate(ofGetWidth(),ofGetHeight());
    
    fbo.begin();
	ofClear(0,0,0);
    fbo.end();
    
    warperA.setup(300,300);
    warperB.setup(300,300);
    warperA.activate();
    warperB.activate();
    
    
    warperB.setCorner(ofxGLWarper::TOP_LEFT, ofPoint(350,0));
    warperB.setCorner(ofxGLWarper::TOP_RIGHT, ofPoint(650,0));
    warperB.setCorner(ofxGLWarper::BOTTOM_LEFT, ofPoint(350,300));
    warperB.setCorner(ofxGLWarper::BOTTOM_RIGHT, ofPoint(650,300));
}

//--------------------------------------------------------------
void ofApp::update(){
    
    fbo.begin();
    ofSetColor(255,0,0);
    ofRect(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(255);
    ofEllipse(300,200,200,200);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTexture tex = fbo.getTextureReference();
    warperA.begin();
    tex.drawSubsection(0, 0, 300, 300, 0, 0);
    ofSetColor(255);
    warperA.draw();

    warperA.end();
    
    warperB.begin();
    tex.drawSubsection(0, 0, 300, 300, 300, 0);
    ofSetColor(255);
    warperB.draw();
    warperB.end();

   
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
