#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createGround();
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
    
    dotImage.loadImage("dot2.png");
}

//--------------------------------------------------------------
void ofApp::update(){
	box2d.update();
    ofRemove(customParticles, ofxBox2dBaseShape::shouldRemoveOffScreen);

}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i=0; i<customParticles.size(); i++) {
		customParticles[i].get()->draw(dotImage);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'z') {
        
		customParticles.push_back(ofPtr<CustomParticle>(new CustomParticle));
        CustomParticle * p = customParticles.back().get();
		float r = ofRandom(10, 30);		// a random radius 4px - 20px
		p->setPhysics(0.4, 0.53, 0.31);
		p->setup(box2d.getWorld(), mouseX, mouseY, r);
		p->color.r = ofRandom(20, 100);
		p->color.g = 0;
		p->color.b = ofRandom(150, 255);
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
