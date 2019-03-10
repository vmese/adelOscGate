#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"
#include "ofParameterGroup.h"
#include "ofParameter.h"
#include "ofxXmlSettings.h"
#include "ofApp.h"
#include "ofxMidi.h"

#define PROJECTOR_RESOLUTION_X 640 //1920 //640
#define PROJECTOR_RESOLUTION_Y 480 //1080 //480

class ofApp : public ofBaseApp, public ofxMidiListener{

	public:
		void setup();
		void update();
		void draw();
                void exit();

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
                void standUp();
                void goToRest();

		void loadConfiguration(const std::string &fileName);

                void connectToAbleton(bool &state);

                ofxOscParameterSync parametersSync1;
                ofxOscParameterSync parametersSync2;
                ofxOscParameterSync parametersSync3;

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
                ofParameter <int> fSpeedServo1;

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
                ofParameter <int> fServo2Temp;
                ofParameter <int> fServo3Temp;

                ofParameter <int> fHeadPositionX;
                ofParameter <int> fHeadPositionY;

                ofParameter <bool> fTorqueControl;
                ofParameter <bool> fbMotorsEnabled;
                ofParameter <bool> fbDrawCloud;
                ofParameter <bool> fbFindHead;
                ofParameter <bool> fbTrackHead;

                ofParameterGroup fLedsControl;
                ofParameter <int> fRComponentLedValue;
                ofParameter <int> fVComponentLedValue;
                ofParameter <int> fBComponentLedValue;
                ofParameter <int> fBrightnessLedValue;
                ofParameter <bool> fbEnableExpression;
                ofParameter <int> fLedExpressionValue;

                ofxPanel gui;
                //shared_ptr<GuiApp> gui;

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

                ofParameterGroup fAbletonControls;
                ofParameterGroup fAbletonConnectionControls;
                ofParameter<float> fAbletonParam1;
                ofParameter<float> fAbletonParam2;
                ofParameter<float> fAbletonParam3;
                ofParameter<float> fAbletonParam4;
                ofParameter<float> fAbletonParam5;
                ofParameter <bool> fbConnectToAbleton;
                std::string fAbletonIP;
                int fAbletonListeningPort;

                //midi
                void newMidiMessage(ofxMidiMessage& eventArgs);

                ofxMidiIn midiIn;
                std::vector<ofxMidiMessage> midiMessages;
                std::size_t maxMessages = 5; //< max number of messages to keep track of
                int midiMessagesCount;
                std::vector<int> midiVals;
                int lastMidiVal;
                int minMidiPitch, maxMidiPitch;
                bool midiControl1Enabled,midiControl2Enabled,midiControl3Enabled,midiControl4Enabled,midiControl5Enabled;

};
