#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
        ofBackground(255, 255, 255);

        loadConfiguration("settings.xml");

        ///setup osc connexion and controls
        printf("setup osc connexion and controls");

        fAbletonConnectionControls.setName("Ableton");
        fAbletonConnectionControls.add(fbConnectToAbleton.set("On/Off",false));
        fbConnectToAbleton.addListener(this,&ofApp::connectToAbleton);

        fAbletonControls.setName("Ableton");
        fAbletonControls.add(fAbletonParam1.set("servo1",0.5,0.0,1.0));
        fAbletonControls.add(fAbletonParam2.set("servo2",0.5,0.0,1.0));
        fAbletonControls.add(fAbletonParam3.set("servo3",0.5,0.0,1.0));
        fAbletonControls.add(fAbletonParam4.set("servo4",0.5,0.0,1.0));
        fAbletonControls.add(fAbletonParam5.set("servo5",0.5,0.0,1.0));

        fAngleControl1.setName("Servo 1");
        fAngleControl1.add(fAngleServo1.set("angle",0.5,0.0,1.0));
        fMinMaxControl1.setName("Min/Max Servo 1");
        fMinMaxControl1.add(fMinServo1.set("Min",fServosMins[0],1.0,1024.0));
        fMinMaxControl1.add(fMaxServo1.set("Max",fServosMax[0],1.0,1024.0));
        fMinMaxControl1.add(fSpeedServo1.set("Speed",40,40,512));

        fAngleControl2.setName("Servo 2" );
        fAngleControl2.add(fAngleServo2.set("angle",0.5,0.0,1.0));
        fMinMaxControl2.setName("Min/Max Servo 2");
        fMinMaxControl2.add(fMinServo2.set("Min",fServosMins[1],1.0,1024.0));
        fMinMaxControl2.add(fMaxServo2.set("Max",fServosMax[1],1.0,1024.0));
        fMinMaxControl2.add(fServo2Temp.set("Temp",0,20,100));

        fAngleControl3.setName("Servo 3");
        fAngleControl3.add(fAngleServo3.set("angle",0.5,0.0,1.0));
        fMinMaxControl3.setName("Min/Max Servo 3");
        fMinMaxControl3.add(fMinServo3.set("Min",fServosMins[2],1.0,1024.0));
        fMinMaxControl3.add(fMaxServo3.set("Max",fServosMax[2],1.0,1024.0));
        fMinMaxControl3.add(fServo3Temp.set("Temp",0,20,100));

        fAngleControl4.setName("Servo 4");
        fAngleControl4.add(fAngleServo4.set("angle",0.5,0.0,1.0));
        fMinMaxControl4.setName("Min/Max Servo 4");
        fMinMaxControl4.add(fMinServo4.set("Min",fServosMins[3],1.0,1024.0));
        fMinMaxControl4.add(fMaxServo4.set("Max",fServosMax[3],1.0,1024.0));

        fAngleControl5.setName("Servo 5");
        fAngleControl5.add(fAngleServo5.set("angle",0.5,0.0,1.0));
        fMinMaxControl5.setName("Min/Max Servo 5");
        fMinMaxControl5.add(fMinServo5.set("Min",fServosMins[4],1.0,1024.0));
        fMinMaxControl5.add(fMaxServo5.set("Max",fServosMax[4],1.0,1024.0));

        fHeadPositionControl.setName("Head");
        fHeadPositionControl.add(fHeadPositionX.set("X",512,0,1024));
        fHeadPositionControl.add(fHeadPositionY.set("Y",384,0,768));

        fLedsControl.setName("Leds");
        fLedsControl.add(fRComponentLedValue.set("R",255,0,255));
        fLedsControl.add(fVComponentLedValue.set("V",255,0,255));
        fLedsControl.add(fBComponentLedValue.set("B",255,0,255));
        fLedsControl.add(fBrightnessLedValue.set("Brightness",10,0,255));
        fLedsControl.add(fbEnableExpression.set("Expression On/Off",false));
        fLedsControl.add(fLedExpressionValue.set("Expression type",1,1,2));

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
        fGlobalControls.add(fLedsControl);
        fGlobalControls.add(fAbletonConnectionControls);


        gui.setup(fGlobalControls);

        //midi
        // print input ports to console
        midiIn.listInPorts();
        // open port by number (you may need to change this)
        midiIn.openPort(1);
        //midiIn.openPort("IAC Pure Data In");	// by name
        //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
        // don't ignore sysex, timing, & active sense messages,
        // these are ignored by default
        midiIn.ignoreTypes(false, false, false);
        // add ofApp as a listener
        midiIn.addListener(this);
        // print received messages to the console
        midiIn.setVerbose(true);
        midiMessagesCount = 0;
        lastMidiVal = -1;
        maxMidiPitch = 0;
        minMidiPitch = 0 ;
        midiControl1Enabled = false;
        midiControl2Enabled = false;
        midiControl3Enabled = false;
        midiControl4Enabled = false;
        midiControl5Enabled = false;

        //sound
        //fSoundPlayer.load("sounds/move.mp3");
        // by now needs to pass the gui parameter groups since the panel internally creates it's own group
        parametersSync1.setup((ofParameterGroup&)gui.getParameter(),6668,fadelControllerIP,fadelControllerListeningPort);
        parametersSync2.setup((ofParameterGroup&)gui.getParameter(),6666,"localhost",6667);
        //parametersSync4.setup((ofParameterGroup&)gui.getParameter(),6669,"192.168.2.6",6669);
        //parametersSync3.setup(fAbletonControls,6670,fAbletonIP,fAbletonListeningPort);
        //parametersSync3.setup(fAngleControl4,6670,fAbletonIP,fAbletonListeningPort);
	ofSetVerticalSync(true);


}

void ofApp::newMidiMessage(ofxMidiMessage& msg) {

        // add the latest message to the message queue
        midiMessages.push_back(msg);

        // remove any old messages if we have too many
        while(midiMessages.size() > maxMessages) {
                midiMessages.erase(midiMessages.begin());
        }
}

void ofApp::connectToAbleton(bool &state)
{
    if (state==true)
    {
        fbConnectToAbleton = true;
        parametersSync3.setup(fAbletonControls,6670,fAbletonIP,fAbletonListeningPort);
        printf("Connection to Ableton\n");

    }
    else
    {
        fbConnectToAbleton = false;
        printf("Disconnection from Ableton\n");
        fbConnectToAbleton = false;
    }
}

void ofApp::exit() {

        // clean up
        midiIn.closePort();
        midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::update(){

        //fBrightnessLedValue = audioInScaledVol * 255.0 ;

//        if (fAngleServo2<0.7 && fAngleServo3>0.5)
//        {
//            fMaxServo3 = fServosMins[2]+1;
//        }
//        else
//        {
//            fMaxServo3 = fServosMax[2];
//        }

//        if (fAngleServo3>0.5)
//        {
//            fMinServo2 = fServosMax[1]-1;
//        }
//        else
//        {
//            fMinServo2 = fServosMins[1];
//        }

        parametersSync1.update();
        parametersSync2.update();
        //parametersSync4.update();

        if (fbConnectToAbleton == true)
        {
            fAbletonParam1 = fBrightnessLedValue;
            //fAbletonParam2 = fAngleServo2;
            //fAbletonParam3 = fAngleServo3;
            //fAbletonParam4 = fAngleServo4;
            //fAbletonParam5 = fAngleServo5;
            parametersSync3.update();
        }
}

//--------------------------------------------------------------
void ofApp::draw(){

        /* --------- Main window  --------------------- */

        gui.draw();

        // midi


        for(unsigned int i = 0; i < midiMessages.size(); ++i)
        {
                ofxMidiMessage &midiMsg = midiMessages[i];
                //ofxMidiMessage::getStatusString(midiMsg.status);
                double deltaT = midiMsg.deltatime;

                if(midiMsg.status == MIDI_NOTE_ON)
                {
                   int channel = midiMsg.pitch;
                   if (channel == 49) //base
                   {
                       midiControl1Enabled = true;
                   }
                   if (channel == 48) //bras bas
                   {
                       midiControl2Enabled = true;
                   }
                   if (channel == 50) //bras haut
                   {
                       midiControl3Enabled = true;
                   }
                   if (channel == 52) // inclinaison tete
                   {
                       midiControl4Enabled = true;
                   }
                   if (channel == 53) // rotation tete
                   {
                       midiControl5Enabled = true;
                   }

                    //midiControlNb = midiMsg.
                }

                if(midiMsg.status == MIDI_NOTE_OFF)
                {
                   //printf("midi note off - pitch=%i\n",midiMsg.pitch);
                   int channel = midiMsg.pitch;
                   if (channel == 49) //base
                   {
                       midiControl1Enabled = false;
                   }
                   if (channel == 48) //bras bas
                   {
                       midiControl2Enabled = false;
                   }
                   if (channel == 50) //bras haut
                   {
                       midiControl3Enabled = false;
                   }
                   if (channel == 52) // inclinaison tete
                   {
                       midiControl4Enabled = false;
                   }
                   if (channel == 53) // rotation tete
                   {
                       midiControl5Enabled = false;
                   }
                    //midiControlNb = midiMsg.
                }

                if(midiMsg.status == MIDI_PITCH_BEND)
                {
                    int pitch = midiMsg.value-8192;
                    printf("pitch = %i\n",pitch);
                    float newAngle;
                    if (pitch>0 && pitch >maxMidiPitch)
                    {
                        maxMidiPitch = pitch;
                        minMidiPitch = 0;
                        printf("max pitch = %i\n",maxMidiPitch);
                        if(midiControl1Enabled == true)
                        {
                            newAngle = ofMap(maxMidiPitch,0,8192,fAngleServo1,1);
                            if (newAngle>fAngleServo1)
                            {
                                fAngleServo1.set(newAngle);
                            }
                        }
                        if(midiControl2Enabled == true)
                        {
                            newAngle = ofMap(maxMidiPitch,0,8192,fAngleServo2,1);
                            if (newAngle>fAngleServo2)
                            {
                                fAngleServo2.set(newAngle);
                            }
                        }
                        if(midiControl3Enabled == true)
                        {
                            newAngle = ofMap(maxMidiPitch,0,8192,fAngleServo3,1);
                            if (newAngle>fAngleServo3)
                            {
                                fAngleServo3.set(newAngle);
                            }
                        }
                        if(midiControl4Enabled == true)
                        {
                            newAngle = ofMap(maxMidiPitch,0,8192,fAngleServo4,1);
                            if (newAngle>fAngleServo4)
                            {
                                fAngleServo4.set(newAngle);
                            }
                        }
                        if(midiControl5Enabled == true)
                        {
                            newAngle = ofMap(maxMidiPitch,0,8192,fAngleServo5,1);
                            if (newAngle>fAngleServo5)
                            {
                                fAngleServo5.set(newAngle);
                            }
                        }
                    }
                    if (pitch<0 && pitch <minMidiPitch)
                    {
                        minMidiPitch = pitch;
                        maxMidiPitch = 0;

                        printf("min pitch = %i\n",maxMidiPitch);
                        if(midiControl1Enabled == true)
                        {
                            newAngle = ofMap(minMidiPitch,-8192,0,0,fAngleServo1);
                            if (newAngle<fAngleServo1)
                            {
                                fAngleServo1.set(newAngle);
                            }
                        }
                        if(midiControl2Enabled == true)
                        {
                            newAngle = ofMap(minMidiPitch,-8192,0,0,fAngleServo2);
                            if (newAngle<fAngleServo2)
                            {
                                fAngleServo2.set(newAngle);
                            }
                        }
                        if(midiControl3Enabled == true)
                        {
                            newAngle = ofMap(minMidiPitch,-8192,0,0,fAngleServo3);
                            if (newAngle<fAngleServo3)
                            {
                                fAngleServo3.set(newAngle);
                            }
                        }
                        if(midiControl4Enabled == true)
                        {
                            newAngle = ofMap(minMidiPitch,-8192,0,0,fAngleServo4);
                            if (newAngle<fAngleServo4)
                            {
                                fAngleServo4.set(newAngle);
                            }
                        }
                        if(midiControl5Enabled == true)
                        {
                            newAngle = ofMap(minMidiPitch,-8192,0,0,fAngleServo5);
                            if (newAngle<fAngleServo5)
                            {
                                fAngleServo5.set(newAngle);
                            }
                        }
                    }

                    //printf("min pitch = %i\n",minMidiPitch);
                }


//                if(midiMsg.status == MIDI_CONTROL_CHANGE )
//                {
//                    int val = midiMsg.value;

//                    if (val!=lastMidiVal)
//                    {
//                        if (midiMessagesCount<2)
//                        {
//                            //printf("channel : %i - control : %i - val : %i\n",midiMsg.channel, midiMsg.control,val);
//                            //printf("push %i\n",val);
//                            midiVals.push_back(val);
//                            midiMessagesCount ++;
//                        }
//                        else
//                        {
//                            int delta = midiVals[1]-midiVals[0];
//                            float inc = ofMap(delta,-10,10,-0.1,0.1);
//                            printf("delta %i\n",delta);
//                            midiMessagesCount = 0;
//                            midiVals.clear();
//                            float currentAngle = fAngleServo2.get();
//                            if (delta>0)
//                            {
//                                currentAngle +=inc;
//                                if (currentAngle>=1.0)
//                                {
//                                    currentAngle = 1.0;
//                                }
//                            }
//                            else
//                            {

//                                currentAngle +=inc;
//                                if (currentAngle<=0.0)
//                                {
//                                    currentAngle = 0.0;
//                                }

//                            }
//                            fAngleServo2.set(currentAngle);
//                        }
//                        lastMidiVal = val;
//                    }
//                }
        }

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
    std::string adelIP= fXMLReader.getValue("oscParams1::adelIP", "");
    int port = fXMLReader.getValue("oscParams1::adelListeningPort", 0);


    ofLogNotice() << "adel IP = " << adelIP ;
    ofLogNotice() << "adel port =" << port;

    if (adelIP == "" || port == 0)
    {
        ofLogError() << "no IP address and port found for Osc communication";
    }
    else
    {
        fadelControllerIP = adelIP ;
        fadelControllerListeningPort = port;
    }

    std::string abletonIP = fXMLReader.getValue("oscParams2::abletonIP", "");
    port = fXMLReader.getValue("oscParams2::abletonListeningPort", 0);

    ofLogNotice() << "IP = " << abletonIP ;
    ofLogNotice() << "port =" << port;

    if (abletonIP == "" || port == 0)
    {
        ofLogError() << "no IP address and port found for Osc communication with ableton";
    }
    else
    {
        fAbletonIP = abletonIP ;
        fAbletonListeningPort = port;
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

    switch (key)
    {
        case '0' :
        {
            fBrightnessLedValue = 0;
            break;
        }
        case '1' :
        {
            fBrightnessLedValue = 255;
            break;
        }
        case 'r' :
        {
             goToRest();
             break;
        }
        case 's' :
        {
            standUp();
            break;
        }

        case OF_KEY_DOWN :
            {
                printf("key down pressed\n");
                {
                    float currentVal = fAngleServo4;
                    currentVal -=0.01;
                    if (currentVal<=0.0)
                    {
                        currentVal = 0.0;
                    }
                    fAngleServo4.set(currentVal);
                }
            }
            break;

        case OF_KEY_UP :
            {

                float currentVal = fAngleServo4;
                currentVal +=0.01;
                if (currentVal>=1.0)
                {
                    currentVal = 1.0;
                }
                fAngleServo4.set(currentVal);
            }
            break;

        case OF_KEY_LEFT :
            {
                float currentVal1 = fAngleServo5;
                float currentVal2 = fAngleServo1;
                currentVal1 -=0.01;
                if (currentVal1<=0.0)
                {
                    currentVal1 = 0.0;
                    currentVal2 += 0.05;
                    if(currentVal2>=1.0)
                    {
                        currentVal2=1.0;
                    }
                }

                fAngleServo1.set(currentVal2);
                fAngleServo5.set(currentVal1);
            }
            break;

        case OF_KEY_RIGHT :
            {

                    float currentVal1 = fAngleServo5;
                    float currentVal2 = fAngleServo1;
                    currentVal1 +=0.01;
                    if (currentVal1>=1.0)
                    {
                        currentVal1 = 1.0;
                        currentVal2 -= 0.05;
                        if(currentVal2<=0.0)
                        {
                            currentVal2=0.0;
                        }
                    }
                    fAngleServo1.set(currentVal2);
                    fAngleServo5.set(currentVal1);
            }
        break;

        case '4' :
            {

                fRComponentLedValue = 255;
                fVComponentLedValue = 0;
                fBComponentLedValue = 0;
                fBrightnessLedValue = ofRandom(10,255);

            }
        break;

        case '5' :
            {

                fRComponentLedValue = 0;
                fVComponentLedValue = 255;
                fBComponentLedValue = 0;
                fBrightnessLedValue = ofRandom(10,255);
            }
        break;

        case '6' :
        {

            fRComponentLedValue = 0;
            fVComponentLedValue = 0;
            fBComponentLedValue = 255;
            fBrightnessLedValue = ofRandom(10,255);
        }
        break;

        case '-' :
            {
                float currentVal1 = fAngleServo2.get();
                float currentVal2 = fAngleServo3.get();
                currentVal1 -=0.005;
                currentVal2 -=0.005;
                if (currentVal1<=0.0)
                {
                    currentVal1 = 0.0;
                }
                if (currentVal2<=0.0)
                {
                    currentVal2 = 0.0;
                }
                fAngleServo2.set(currentVal1);
                fAngleServo3.set(currentVal2);
            }
        break;

    case '+' :
        {
            float currentVal1 = fAngleServo2.get();
            float currentVal2 = fAngleServo3.get();
            currentVal1 +=0.005;
            currentVal2 +=0.005;
            if (currentVal1>=1.0)
            {
                currentVal1 = 1.0;
            }
            if (currentVal2>=1.0)
            {
                currentVal2 = 1.0;
            }
            fAngleServo2.set(currentVal1);
            fAngleServo3.set(currentVal2);
        }
    break;

    case 'a' :
        {
            bool status = fbMotorsEnabled;
            fbMotorsEnabled = !status;
        }
    break;

        default :
            break;
    }

}

void ofApp::standUp()
{
     //fAngleServo1.set(0.5);
     fAngleServo2.set(1.0);
     fAngleServo3.set(1.0);
     fAngleServo4.set(0.0);
     fAngleServo5.set(0.5);


}

void ofApp::goToRest()
{

    fAngleServo1.set(0.5);
    fAngleServo3.set(0.0);
    fAngleServo2.set(0.0);
    fAngleServo4.set(0.0);
    fAngleServo5.set(0.5);
    fbTrackHead = false;
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
