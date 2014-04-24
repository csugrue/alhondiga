#include "ofApp.h"

/*
 call back to remove box2d objects that have gone off screen
*/
static bool removeShapeOffScreen(ofPtr<ofxBox2dBaseShape> shape) {
    if (!ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape.get()->getPosition())) {
        return true;
    }
    return false;
}
 
//--------------------------------------------------------------
void ofApp::setup(){
    
    // setup the warper
    warper.setup(ofGetWidth(),ofGetHeight());
	warper.activate();  // turn on for adjusting
    
    // box2d
	box2d.init();
	box2d.setGravity(0, 30);
	box2d.createGround();
	box2d.setFPS(30.0);
    
    
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // remove offscreen objects
    ofRemove(circles, removeShapeOffScreen);
    
    // add some circles every so often
	if((int)ofRandom(0, 10) == 0) {
		ofPtr<ofxBox2dCircle> c = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
		c.get()->setPhysics(0.2, 0.2, 0.002);
		c.get()->setup(box2d.getWorld(), ofRandom(20, 50), -20, ofRandom(3, 10));
        c.get()->setVelocity(0, 10); // shoot them down!
		circles.push_back(c);
	}
	
    
    // update physics
	box2d.update();
    
    cout << "circles " << circles.size() << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw everything that will be warped between warper.begin() and end()
    warper.begin();
    
    // draw background rectangle in the warped area
    ofFill();
    ofSetColor(80);
    ofRect(0,0,ofGetWidth(),ofGetHeight());

    // draw the circles
	ofFill();
    ofSetHexColor(0xc0dd3b);
    for (int i=0; i<circles.size(); i++) {
		circles[i].get()->draw();
	}
	
	// draw the lines
    ofSetHexColor(0x444342);
	ofNoFill();
	for (int i=0; i<lines.size(); i++) {
		lines[i].draw();
	}
	for (int i=0; i<edges.size(); i++) {
		edges[i].get()->draw();
	}
    
    // draw warper when editing
    if(warper.isActive()){
        ofSetColor(255,0,255);
        warper.draw();
    }
    warper.end();
    
	
    
    ofSetColor(255);
    ofDrawBitmapString("press SPACE to toggle warper enable/disable", 30,30);
    
    string info = "Draw a shape with the mouse\n";
	info += "Press 1 to add some circles\n";
	info += "Press c to clear everything\n";
	
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 45);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == ' '){
        if(warper.isActive()) warper.deactivate();
        else warper.activate();
    }
    
    if(key == '1') {
        ofPtr<ofxBox2dCircle> c = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
		c.get()->setPhysics(1, 0.5, 0.5);
		c.get()->setup(box2d.getWorld(), mouseX, mouseY, 10);
		circles.push_back(c);
	}
	
	if(key == 'c') {
		lines.clear();
		edges.clear();
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
	
    if(!warper.isActive()){
        ofPoint p = warper.fromScreenToWarpCoord(x,y,0);
        lines.back().addVertex(p.x, p.y);
    }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(!warper.isActive()){
        lines.push_back(ofPolyline());
        
        ofPoint p = warper.fromScreenToWarpCoord(x,y,0);
        lines.back().addVertex(p.x, p.y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(!warper.isActive()){
        
        ofPtr <ofxBox2dEdge> edge = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
        lines.back().simplify();
        
        for (int i=0; i<lines.back().size(); i++) {
            edge.get()->addVertex(lines.back()[i]);
        }
        
        edge.get()->create(box2d.getWorld());
        edges.push_back(edge);

    }
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
