#pragma once

#include "ofMain.h"
#include "ofxGLWarper.h"
#include "ofxBox2d.h"

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
    
        ofxGLWarper warper;
    
        // drawn lines
        vector <ofPolyline>                 lines;
    
        // box2d physics object
        ofxBox2d                            box2d;
    
        // box2d circles
        vector <ofPtr<ofxBox2dCircle> >		circles;
    
        // box2d edges that area created from the drawn lines
        vector <ofPtr<ofxBox2dEdge> >       edges;

		
};
