#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
	ofSetCircleResolution(80);
	ofBackground(54, 54, 54);
	
	int bufferSize = 256;
    
    // 0 output channels,
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);	
	
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    
	
}

//--------------------------------------------------------------
void ofApp::update(){
	
    //lets scale the vol up to a 0-1 range
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 500.0, true);
    
	
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(245, 58, 135);
    ofFill();
    ofCircle(ofGetWidth()/2, ofGetHeight()/2, scaledVol);

}
//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
	
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
		
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
    cout << "numcounted" << numCounted << endl;
    
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	
	// make smooth vol a blend of previous and current
    smoothedVol *= 0.99;
	smoothedVol += 0.01 * curVol;
	// smoothedVol = .9*smoothedVol + .1*curVol;
	//smoothedVol = curVol;
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
