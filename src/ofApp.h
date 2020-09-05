#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_stdlib.h"
#include "IconsFontAwesome5.h"
#include "imgui_helpers.h"
#include "AppTheme.h"

#include "ofxOsc.h"

#include <pwd.h>
#include <unistd.h>

#define PACKAGE                 "FFTStream"
#define	VERSION                 "0.0.1"
#define DESCRIPTION             "Soundfile player FFT extract and send via OSC"
#define DEVELOPER               "Emanuele Mazza"
#define WINDOW_TITLE            "FFTStream 0.0.1"

#define MAIN_FONT               "fonts/Roboto-Regular.ttf"

#define RETINA_MIN_WIDTH        2560
#define RETINA_MIN_HEIGHT       1600

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

    // UTILS
    void            initDataFolderFromBundle();

    // BUNDLE
    std::filesystem::path       userAppPath;
    string                      userHome;


    // GUI
    ofxImGui::Gui               mainGUI;
    AppTheme*                   mainTheme;
    ofRectangle                 playerRect;
    string                      windowTitle;
    string                      currentSoundfile;
    bool                        isRetina;
    float                       scaleFactor;

    // SOUND PLAYER
    ofSoundPlayer               soundfile;
    bool                        isPaused;
    bool                        isLoop;

    static constexpr size_t nBandsToGet = 513;
    std::array<float, nBandsToGet> fftSmoothed{{0}};

    // OSC
    ofxOscSender                sender;
    int                         port;

};
