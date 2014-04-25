#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    fbo.allocate(ofGetWidth(),ofGetHeight());
    
    fbo.begin();
	ofClear(0,0,0);
    fbo.end();
    
    warper.setup(300,300);
    warper.activate();
    
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
    
    warper.begin();
        tex.drawSubsection(0, 0, 300, 300, 0, 0);
        ofSetColor(255);
        warper.draw();
    warper.end();
    
    
   
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
