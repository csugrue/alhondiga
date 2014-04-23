#include "ofApp.h"

static bool removeShapeOffScreen(ofPtr<ofxBox2dBaseShape> shape) {
    if (!ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape.get()->getPosition())) {
        return true;
    }
    return false;
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    // enable depth->video image calibration
	kinect.setRegistration(true);
    
	kinect.init();
	//kinect.init(true); // shows infrared instead of RGB video image
	//kinect.init(false, false); // disable video image (faster fps)
	
	kinect.open();		// opens first available kinect
    
    grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
	
	nearThreshold = 230;
	farThreshold = 70;
	bThreshWithOpenCV = true;
    
    
    // box2d
	box2d.init();
	box2d.setGravity(0, 30);
	box2d.createGround();
	box2d.setFPS(30.0);
    
	
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
		
		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
        
        contourFinder.findContours(grayImage, 100, (kinect.width*kinect.height)/2, 4, false, true);
        
        
	}
    
    
    // remove offscreen objects
    ofRemove(circles, removeShapeOffScreen);
    
    // add some circles every so often
	if((int)ofRandom(0, 10) == 0) {
		ofPtr<ofxBox2dCircle> c = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
		c.get()->setPhysics(0.2, 0.2, 0.002);
		c.get()->setup(box2d.getWorld(), ofRandom(20, ofGetWidth()-50), -20, ofRandom(3, 10));
        c.get()->setVelocity(0, 10); // shoot them down!
		circles.push_back(c);
	}
	
    
    // update physics
	box2d.update();
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw preview
    grayImage.draw(10, 10, 200, 150);
    contourFinder.draw(10, 10, 200, 150);
    
    // draw simplified contours
    float scaleW = ofGetWidth() / (float)kinect.width;
    float scaleH = ofGetHeight() / (float)kinect.height;
    
    edges.clear();
    for( int i = 0; i < contourFinder.nBlobs; i++){
        ofPolyline contourSimple;
        
        for(int j = 0; j < contourFinder.blobs[i].pts.size(); j++){
            contourSimple.lineTo(contourFinder.blobs[i].pts[j].x*scaleW,contourFinder.blobs[i].pts[j].y*scaleH);
        }
        contourSimple.close();
        contourSimple.simplify(3);
        contourSimple.draw();
        
        
        ofPtr <ofxBox2dEdge> edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
        
        for (int i=0; i<contourSimple.size(); i++) {
            edge.get()->addVertex(contourSimple[i]);
        }
        
        edge.get()->create(box2d.getWorld());
        edges.push_back(edge);

    }
    
    
    // draw the circles
	ofFill();
    ofSetHexColor(0xc0dd3b);
    for (int i=0; i<circles.size(); i++) {
		circles[i].get()->draw();
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
