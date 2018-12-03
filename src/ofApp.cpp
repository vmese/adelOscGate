#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


        loadConfiguration("settings.xml");

        ///setup osc connexion and controls
        printf("setup osc connexion and controls");

        fAngleControl1.setName("Servo 1");
        fAngleControl1.add(fAngleServo1.set("angle",0.5,0.0,1.0));
        fMinMaxControl1.setName("Min/Max Servo 1");
        fMinMaxControl1.add(fMinServo1.set("Min",10,1.0,1024.0));
        fMinMaxControl1.add(fMaxServo1.set("Max",512,1.0,1024.0));

        fAngleControl2.setName("Servo 2" );
        fAngleControl2.add(fAngleServo2.set("angle",0.5,0.0,1.0));
        fMinMaxControl2.setName("Min/Max Servo 2");
        fMinMaxControl2.add(fMinServo2.set("Min",10,1.0,1024.0));
        fMinMaxControl2.add(fMaxServo2.set("Max",512,1.0,1024.0));

        fAngleControl3.setName("Servo 3");
        fAngleControl3.add(fAngleServo3.set("angle",0.5,0.0,1.0));
        fMinMaxControl3.setName("Min/Max Servo 3");
        fMinMaxControl3.add(fMinServo3.set("Min",10,1.0,1024.0));
        fMinMaxControl3.add(fMaxServo3.set("Max",512,1.0,1024.0));

        fAngleControl4.setName("Servo 4");
        fAngleControl4.add(fAngleServo4.set("angle",0.5,0.0,1.0));
        fMinMaxControl4.setName("Min/Max Servo 4");
        fMinMaxControl4.add(fMinServo4.set("Min",10,1.0,1024.0));
        fMinMaxControl4.add(fMaxServo4.set("Max",512,1.0,1024.0));

        fAngleControl5.setName("Servo 5");
        fAngleControl5.add(fAngleServo5.set("angle",0.5,0.0,1.0));
        fMinMaxControl5.setName("Min/Max Servo 5");
        fMinMaxControl5.add(fMinServo5.set("Min",10,1.0,1024.0));
        fMinMaxControl5.add(fMaxServo5.set("Max",512,1.0,1024.0));

        fHeadPositionControl.setName("Head");
        fHeadPositionControl.add(fHeadPositionX.set("X",512,0,1024));
        fHeadPositionControl.add(fHeadPositionY.set("Y",384,0,768));

        fBooleanControls.setName("Controls");
        fBooleanControls.add(fbMotorsEnabled.set("Motors enabled",false));
        fBooleanControls.add(fbDrawCloud.set("Draw Cloud",false));
        fBooleanControls.add(fbFindHead.set("Find head",false));
        fBooleanControls.add(fbTrackHead.set("Track head",false));

        fGlobalControls.add(fAngleControl1);
        fGlobalControls.add(fAngleControl2);
        fGlobalControls.add(fAngleControl3);
        fGlobalControls.add(fAngleControl4);
        fGlobalControls.add(fAngleControl5);
        fGlobalControls.add(fHeadPositionControl);
        fGlobalControls.add(fMinMaxControl1);
        fGlobalControls.add(fMinMaxControl2);
        fGlobalControls.add(fMinMaxControl3);
        fGlobalControls.add(fMinMaxControl4);
        fGlobalControls.add(fMinMaxControl5);
        fGlobalControls.add(fBooleanControls);

        gui.setup(fGlobalControls);

        // by now needs to pass the gui parameter groups since the panel internally creates it's own group
        parametersSync1.setup((ofParameterGroup&)gui.getParameter(),6668,fadelControllerIP,fadelControllerListeningPort);
        parametersSync2.setup((ofParameterGroup&)gui.getParameter(),6666,"localhost",6667);
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
        parametersSync1.update();
        parametersSync2.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

        gui.draw();

}

void ofApp::loadConfiguration(const std::string &fileName)
{
    std::string message;
    if( fXMLReader.loadFile(fileName) ){
        message = fileName + " loaded!";
        ofLogNotice() << message;
    }else{
        message = "unable to load " + fileName + " - check data/ folder";
        ofLogError() << message;
    }

    // find address and port for Osc communication
    std::string adelIP= fXMLReader.getValue("oscParams::adelIP", "");
    int port = fXMLReader.getValue("oscParams::adelListeningPort", 0);

    if (adelIP == "" || port == 0)
    {
        ofLogError() << "no IP address and port found for Osc communication";
    }
    else
    {
        fadelControllerIP = adelIP ;
        fadelControllerListeningPort = port;
    }

    // find servos names
    fServosNames.clear();
    fServosIds.clear();
    fServosMins.clear();
    fServosMax.clear();
    fServosInitialPos.clear();

    int nbServos = fXMLReader.getNumTags("servo");
    if (nbServos>0)
    {
        for(int i = 0; i < nbServos; i++)
        {
              fXMLReader.pushTag("servo", i);
              std::string servoName = fXMLReader.getValue("name","");
              int id = fXMLReader.getValue("id",0);
              int pinNb = fXMLReader.getValue("pinNb",0);
              int pos = fXMLReader.getValue("initialPos",0);
              int min = fXMLReader.getValue("min",0);
              int max = fXMLReader.getValue("max",300);

              ofLogNotice () << "Servo " << servoName << " id : " <<  id << " initial pos " << pos;

              if (servoName!="" && id!=0)
              {
                  ofLogNotice () << "Servo " << servoName << " id : " <<  id << " min : " << min;
                  ofLogNotice () << "Servo " << servoName << " id : " <<  id << " max : " << max;
                  fServosNames.push_back(servoName);
                  fServosIds.push_back(id);
                  fServosMins.push_back(min);
                  fServosMax.push_back(max);
                  printf("initial pos : %i\n",pos);
                  fServosInitialPos.push_back(pos);

              }
              fXMLReader.popTag();
         }

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
