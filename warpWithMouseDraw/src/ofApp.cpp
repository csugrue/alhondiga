#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    warper.setup(ofGetWidth(),ofGetHeight()); //initializates ofxGLWarper
	warper.activate();// this allows ofxGLWarper to automatically listen to the mouse and keyboard input and updates automatically it's matrixes.
	
    ofSetVerticalSync(true);
    
    ofBackground(20, 20, 20);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    warper.begin();
    
    ofSetColor(80);
    ofFill();
    ofRect(0,0,ofGetWidth(),ofGetHeight());
    
    ofSetColor(255,0,255);
    for(int i = 0; i < pts.size(); i++){
        ofEllipse(pts[i].x, pts[i].y, 4, 4);
    }
    
    ofNoFill();
    ofBeginShape();
        for(int i = 0; i < pts.size(); i++){
            ofVertex(pts[i].x,pts[i].y);
        }
    ofEndShape();
    
    warper.end();
	
    ofSetLineWidth(3);
    if(warper.isActive()) warper.draw();
    ofSetLineWidth(1);
    
    ofSetColor(255);
    ofDrawBitmapString("press SPACE to toggle warper enable/disable", 30,30);
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        if(warper.isActive()) warper.deactivate();
        else warper.activate();
    }
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
    if(!warper.isActive()){
        ofPoint p = warper.fromScreenToWarpCoord(x,y,0);
        pts.push_back(p);
    }
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
