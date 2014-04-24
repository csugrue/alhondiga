#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    x = 0;
    
    // cargar imagen
    catImage.loadImage("cat.jpg");
    
    // init camera
    camera.initGrabber(320, 240);
}

//--------------------------------------------------------------
void ofApp::update(){
    x = x + 0.5;
    
    // update camera con nuevos datos
    camera.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    camera.draw(x,0);
    
    catImage.draw(x,0,catImage.width*.5,catImage.height*.5);
    
    ofCircle(x,0,20);
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
