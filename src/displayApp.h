#pragma once

#include "ofMain.h"
#include "ofApp.h"

#define kAudioInputBufferSize 512

class displayApp : public ofBaseApp{

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		shared_ptr<ofApp> app;
                void audioIn(float * input, int bufferSize, int nChannels);

                //audio input parameters
                vector <float> audioInLeft;
                vector <float> audioInRight;
                int 	audioInputBufferCount;
                int 	audioInDrawCounter;
                float audioInSmoothedVol;
                float audioInScaledVol;
                ofSoundStream soundStream;
};
