#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

// ------------------------------------------------- a simple extended box2d circle
class CustomParticle : public ofxBox2dCircle {
	
public:
	CustomParticle() {
	}
	ofColor color;
	void draw(ofImage & img) {
		float radius = getRadius();
		
		ofSetRectMode(OF_RECTMODE_CENTER);
        ofPushMatrix();
		ofTranslate(getPosition().x, getPosition().y);
		ofRotate(getRotation());
		ofSetColor(color.r, color.g, color.b);
		ofFill();
		//ofCircle(0, 0, radius);
		img.draw(0,0,radius*2,radius*2);
		ofPopMatrix();
        ofSetRectMode(OF_RECTMODE_CORNER);

	}
};


// -------------------------------------------------

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxBox2d                                box2d;			  //	the box2d world
        vector		<ofPtr<CustomParticle> >    customParticles;  //	this is a custom particle the extends a cirlce
    
        ofImage dotImage;
};



