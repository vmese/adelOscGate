#include "ofMain.h"
#include "ofApp.h"
#include "displayApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
        /* -------------- one window ---------------*/
//        ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context
//	// this kicks off the running of my app
//	// can be OF_WINDOW or OF_FULLSCREEN
//	// pass in width and height too:
//        ofRunApp( new ofApp());

        /* -------------- two windows --------------*/
        ofGLFWWindowSettings settings;

        settings.width = 1920;
        settings.height = 400;
        settings.setPosition(ofVec2f(480,0));
        settings.resizable = true;
        shared_ptr<ofAppBaseWindow> displayWindow = ofCreateWindow(settings);

        settings.width = 480;
        settings.height = 900;
        settings.setPosition(ofVec2f(0,0));
        settings.resizable = false;
        shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

          shared_ptr<ofApp> mainApp(new ofApp());
          shared_ptr<displayApp> dispApp(new displayApp);
//        displayApp->gui = guiApp;

         ofRunApp(mainWindow, mainApp);
         ofRunApp(displayWindow, dispApp);
         ofRunMainLoop();


}
