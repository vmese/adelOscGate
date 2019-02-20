#include "displayApp.h"

//--------------------------------------------------------------
void displayApp::setup(){
        ofBackground(0);
	ofSetCircleResolution(200);

        //setup audio input

        soundStream.printDeviceList();

        //if you want to set a different device id
        //soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.

        audioInLeft.assign(kAudioInputBufferSize, 0.0);
        audioInRight.assign(kAudioInputBufferSize, 0.0);

        audioInputBufferCount	= 0;
        audioInDrawCounter		= 0;
        audioInSmoothedVol     = 0.0;
        audioInScaledVol		= 0.0;

        soundStream.setup(this, 0, 2, 44100, kAudioInputBufferSize, 4);

}

//--------------------------------------------------------------
void displayApp::update(){
    //lets scale the vol up to a 0-1 range
    audioInScaledVol = ofMap(audioInSmoothedVol, 0.0, 0.17, 0.0, 1.0, true);

}

//--------------------------------------------------------------
void displayApp::draw(){

    /* --------- Second window -------------------- */
    //secondWindow.begin();

    // draw audio inputs
    ofSetColor(0);
    //ofDrawBitmapString("AUDIO INPUT EXAMPLE", 32, 32);
    //ofDrawBitmapString("press 's' to unpause the audio\n'e' to pause the audio", 31, 92);

    ofNoFill();

    // draw the left channel:

    ofPushStyle();
    ofPushMatrix();
            //ofTranslate(200, 170, 0);

//		ofSetColor(225);
//		ofDrawBitmapString("Left Channel", 4, 18);

//		ofSetLineWidth(1);
//		ofDrawRectangle(0, 0, 512, 200);

            //ofSetColor(245, 58, 135);
            ofSetColor(255, 255, 255);
            ofSetLineWidth(audioInScaledVol*20.0);

                    int ratio = 1920/kAudioInputBufferSize;
                    ofBeginShape();
                    for (unsigned int i = 0; i < audioInLeft.size(); i++){
                            ofVertex(i*ratio, 100 -(0.5*audioInLeft[i]*180.0f));
                    }
                    ofEndShape(false);

    ofPopMatrix();
    ofPopStyle();


    // draw the right channel:
//    ofPushStyle();
//    ofPushMatrix();
//            ofTranslate(0, 200, 0);

////		ofSetColor(225);
////		ofDrawBitmapString("Right Channel", 4, 18);

////		ofSetLineWidth(1);
////		ofDrawRectangle(0, 0, 512, 200);

//            //ofSetColor(245, 58, 135);
//            ofSetColor(255, 255, 255);
//            ofSetLineWidth(audioInScaledVol*20.0);

//                    ofBeginShape();
//                    for (unsigned int i = 0; i < audioInRight.size(); i++){
//                            ofVertex(i*ratio, 100 -audioInRight[i]*180.0f);
//                    }
//                    ofEndShape(false);
//     ofPopMatrix();
//     ofPopStyle();

    // draw the average volume:
//        ofPushStyle();
//                ofPushMatrix();
//                ofTranslate(565, 170, 0);

//                ofSetColor(225);
//                ofDrawBitmapString("Scaled average vol (0-100): " + ofToString(audioInScaledVol * 100.0, 0), 4, 18);
//                ofDrawRectangle(0, 0, 400, 400);

//                ofSetColor(245, 58, 135);
//                ofFill();
//                ofDrawCircle(200, 200, audioInScaledVol * 190.0f);

            //lets draw the volume history as a graph
//                ofBeginShape();
//                for (unsigned int i = 0; i < volHistory.size(); i++){
//                        if( i == 0 ) ofVertex(i, 400);

//                        ofVertex(i, 400 - volHistory[i] * 70);

//                        if( i == volHistory.size() -1 ) ofVertex(i, 400);
//                }
//                ofEndShape(false);
//
//                ofPopMatrix();
//        ofPopStyle();

    audioInDrawCounter++;

    //ofSetColor(225);
    //string reportString = "buffers received: "+ofToString(audioInputBufferCount)+"\ndraw routines called: "+ofToString(audioInDrawCounter)+"\nticks: " + ofToString(soundStream.getTickCount());
    //ofDrawBitmapString(reportString, 32, 589);

    //secondWindow.end();
    //secondWindow.show();
}

void displayApp::audioIn(float * input, int bufferSize, int nChannels)
{

        float curVol = 0.0;

        // samples are "interleaved"
        int numCounted = 0;

        //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
        for (int i = 0; i < bufferSize; i++){
                audioInLeft[i]	= input[i*2]*0.5;
                audioInRight[i]	= input[i*2+1]*0.5;

                curVol += audioInLeft[i] * audioInLeft[i];
                curVol += audioInRight[i] * audioInRight[i];
                numCounted+=2;
        }

        //this is how we get the mean of rms :)
        curVol /= (float)numCounted;

        // this is how we get the root of rms :)
        curVol = sqrt( curVol );

        audioInSmoothedVol *= 0.93;
        audioInSmoothedVol += 0.07 * curVol;

        audioInputBufferCount++;

}
//--------------------------------------------------------------
void displayApp::keyPressed(int key){

}

//--------------------------------------------------------------
void displayApp::keyReleased(int key){

}

//--------------------------------------------------------------
void displayApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void displayApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void displayApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void displayApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void displayApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void displayApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void displayApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void displayApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void displayApp::dragEvent(ofDragInfo dragInfo){

}
