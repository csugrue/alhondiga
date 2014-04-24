#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // enable depth->video image calibration
	kinect.setRegistration(true);
    
	kinect.init();
	kinect.open();		// opens first available kinect
    
    grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
	
    // thresholds good for close range (lower farThreshold to increase range)
	nearThreshold = 255;
	farThreshold = 150;
	bThreshWithOpenCV = true;
	
	ofSetFrameRate(60);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofBackground(100, 100, 100);
	
	kinect.update();
	
	// there is a new frame and we are connected
	if(kinect.isFrameNew()) {
        
        // load grayscale depth image from the kinect source
		grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
		
		// we do two thresholds - one for the far plane and one for the near plane
		// we then do a cvAnd to get the pixels which are a union of the two thresholds
		if(bThreshWithOpenCV) {
			grayThreshNear = grayImage;
			grayThreshFar = grayImage;
			grayThreshNear.threshold(nearThreshold, true);
			grayThreshFar.threshold(farThreshold);
			cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
		} else {
			
			// or we do it ourselves - show people how they can work with the pixels
			unsigned char * pix = grayImage.getPixels();
			
			int numPixels = grayImage.getWidth() * grayImage.getHeight();
			for(int i = 0; i < numPixels; i++) {
				if(pix[i] < nearThreshold && pix[i] > farThreshold) {
					pix[i] = 255;
				} else {
					pix[i] = 0;
				}
			}
		}
		
		// update the cv images
		grayImage.flagImageChanged();
		
		// get contours
        contourFinder.findContours(grayImage, 100, (kinect.width*kinect.height)/2, 4, false, true);
        
        
	}
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw preview
    grayImage.draw(10, 10, 200, 150);
    contourFinder.draw(10, 10, 200, 150);
    
    // draw simplified contours
    float scaleW = ofGetWidth() / (float)kinect.width;
    float scaleH = ofGetHeight() / (float)kinect.height;
    
    for( int i = 0; i < contourFinder.nBlobs; i++){
        ofPolyline contourSimple;
        
        for(int j = 0; j < contourFinder.blobs[i].pts.size(); j++){
            contourSimple.lineTo(contourFinder.blobs[i].pts[j].x*scaleW,contourFinder.blobs[i].pts[j].y*scaleH);
        }
        contourSimple.close();
        
        // draw normal
        ofSetColor(0,255,255);
        contourSimple.draw();
        
        // simplify and draw
        ofSetColor(255);
        contourSimple.simplify(10);
        contourSimple.draw();
    }
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
