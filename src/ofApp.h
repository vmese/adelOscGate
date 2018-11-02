#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"
#include "ofParameterGroup.h"
#include "ofParameter.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
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

		void loadConfiguration(const std::string &fileName);

                ofxOscParameterSync parametersSync1;
                ofxOscParameterSync parametersSync2;

                //Control Params
                ofParameterGroup fGlobalControls;
                ofParameterGroup fAngleControl1;
                ofParameterGroup fMinMaxControl1;
                ofParameterGroup fAngleControl2;
                ofParameterGroup fMinMaxControl2;
                ofParameterGroup fAngleControl3;
                ofParameterGroup fMinMaxControl3;
                ofParameterGroup fAngleControl4;
                ofParameterGroup fMinMaxControl4;
                ofParameterGroup fAngleControl5;
                ofParameterGroup fMinMaxControl5;
                ofParameterGroup fBooleanControls;

                ofParameterGroup fHeadPositionControl;

                ofParameter <float> fAngleServo1;
                ofParameter <int> fMinServo1;
                ofParameter <int> fMaxServo1;
                ofParameter <float> fAngleServo2;
                ofParameter <int> fMinServo2;
                ofParameter <int> fMaxServo2;
                ofParameter <float> fAngleServo3;
                ofParameter <int> fMinServo3;
                ofParameter <int> fMaxServo3;
                ofParameter <float> fAngleServo4;
                ofParameter <int> fMinServo4;
                ofParameter <int> fMaxServo4;
                ofParameter <float> fAngleServo5;
                ofParameter <int> fMinServo5;
                ofParameter <int> fMaxServo5;

                ofParameter <int> fHeadPositionX;
                ofParameter <int> fHeadPositionY;

                ofParameter <bool> fTorqueControl;
                ofParameter <bool> fMotorsEnabled;

                ofxPanel gui;

		// Servos params
        	ofxXmlSettings fXMLReader;
        	std::vector<std::string> fServosNames;
        	std::vector<int> fServosPins;
        	std::vector<int> fServosIds;
        	std::vector<int> fServosMins;
        	std::vector<int> fServosMax;
        	std::vector<int> fServosInitialPos;

                std::string fadelControllerIP;
                int fadelControllerListeningPort;


};
