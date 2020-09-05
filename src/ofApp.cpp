#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ///////////////////////////////////////////
    // OF Stuff
    ofSetFrameRate(60);
    ofSetEscapeQuitsApp(false);
    ofSetVerticalSync(false);

    initDataFolderFromBundle();
    ///////////////////////////////////////////

    // RETINA FIX
    isRetina = false;
    scaleFactor = 1.0f;
    if(ofGetScreenWidth() >= RETINA_MIN_WIDTH && ofGetScreenHeight() >= RETINA_MIN_HEIGHT){ // RETINA SCREEN
        ofSetWindowShape(800*2,320*2);
        isRetina = true;
        scaleFactor = 2.0f;
    }

    // GUI
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;

    ofFile fileToRead1(ofToDataPath(MAIN_FONT));
    string absPath1 = fileToRead1.getAbsolutePath();
    if(isRetina){
        io.Fonts->AddFontFromFileTTF(absPath1.c_str(),24.0f);
    }else{
        io.Fonts->AddFontFromFileTTF(absPath1.c_str(),14.0f);
    }

    // merge in icons from Font Awesome
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
    if(isRetina){
        io.Fonts->AddFontFromFileTTF( FONT_ICON_FILE_NAME_FAS, 22.0f, &icons_config, icons_ranges );
    }else{
        io.Fonts->AddFontFromFileTTF( FONT_ICON_FILE_NAME_FAS, 14.0f, &icons_config, icons_ranges );
    }

    ImFont* defaultfont = io.Fonts->Fonts[io.Fonts->Fonts.Size - 1];
    io.FontDefault = defaultfont;

    mainTheme = new AppTheme();
    mainGUI.setup();
    mainGUI.setTheme(mainTheme);
    if(isRetina){
        mainTheme->fixForRetinaScreen();
    }
    playerRect.set(0,0,ofGetWindowWidth(),40*scaleFactor);

    currentSoundfile    = "";
    isPaused            = false;
    isLoop              = false;

    // OSC
    sender.setup("localhost", 9173);
}

//--------------------------------------------------------------
void ofApp::update(){
    windowTitle = currentSoundfile+" - "+WINDOW_TITLE;
    ofSetWindowTitle(windowTitle);

    // update the sound playing system:
    ofSoundUpdate();

    // grab the fft, and put in into a "smoothed" array,
    // by taking maximums, as peaks and then smoothing downward
    float * val = ofSoundGetSpectrum(nBandsToGet);		// request 513 values for fft
    for (int i = 0;i < nBandsToGet; i++){

        // let the smoothed value sink to zero:
        fftSmoothed[i] *= 0.9f;

        // take the max, either the smoothed or the incoming:
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
    }

    if(soundfile.isPlaying()){
        ofxOscMessage m;
        m.setAddress("/FFTStreamDATA");
        for (int i = 0;i < nBandsToGet; i++){
            m.addFloatArg(fftSmoothed[i]);
        }
        sender.sendMessage(m,false);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(30,30,30);

    if(currentSoundfile != ""){
        ofSetColor(255);
        ofDrawBitmapString("Loaded file:\n"+currentSoundfile,20,120);

        // draw the fft resutls:
        ofSetColor(255,255,120,255);

        float bandwidth = ofGetWindowWidth() * 1.0f / nBandsToGet;
        for (int i = 0;i < nBandsToGet; i++){
            // (we use negative height here, because we want to flip them
            // because the top corner is 0,0)
            ofDrawRectangle(i*bandwidth,ofGetWindowHeight(),bandwidth,-(fftSmoothed[i] * (ofGetWindowHeight()-(100*scaleFactor))));
        }
    }

    // GUI
    mainGUI.begin();

    {
        ImGui::SetNextWindowSize(ImVec2(playerRect.width,playerRect.height), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(playerRect.x,playerRect.y), ImGuiCond_Always);
        if (!ImGui::Begin("Player",nullptr,ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoDecoration))
        {
            ImGui::End();
            return;
        }

        ImGui::Dummy(ImVec2(1,14*scaleFactor));

        ImGui::PushStyleColor(ImGuiCol_Button, VHS_BLUE);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, VHS_BLUE_OVER);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, VHS_BLUE_OVER);
        if(ImGui::Button(ICON_FA_PLAY,ImVec2(56*this->scaleFactor,24*this->scaleFactor))){
            if(isPaused){
                soundfile.setPaused(false);
                isPaused = false;
            }else{
                soundfile.play();
            }

        }
        ImGui::SameLine();
        if(ImGui::Button(ICON_FA_STOP,ImVec2(56*this->scaleFactor,24*this->scaleFactor))){
            soundfile.stop();
        }
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Button, VHS_YELLOW);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, VHS_YELLOW_OVER);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, VHS_YELLOW_OVER);
        if(ImGui::Button(ICON_FA_PAUSE,ImVec2(56*this->scaleFactor,24*this->scaleFactor))){
            isPaused = !isPaused;
            if(isPaused){
                soundfile.setPaused(true);
            }else{
                soundfile.setPaused(false);
            }

        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine();ImGui::Dummy(ImVec2(20*scaleFactor,1));ImGui::SameLine();

        if(ImGui::Checkbox("LOOP " ICON_FA_REDO,&isLoop)){
            soundfile.setLoop(isLoop);
        }

        ImGui::End();
    }

    mainGUI.end();

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
void ofApp::windowResized(int w, int h){
    playerRect.set(0,0,ofGetWindowWidth(),40*scaleFactor);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    if( dragInfo.files.size() == 1 ){
        ofFile file (dragInfo.files[0]);
        if (file.exists()){
            string fileExtension = ofToUpper(file.getExtension());
            if(fileExtension == "WAV" || fileExtension == "AIF" || fileExtension == "AIFF" || fileExtension == "MP3"){
                currentSoundfile = file.getAbsolutePath();
                soundfile.load(currentSoundfile);
                soundfile.stop();
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::initDataFolderFromBundle(){

    string _bundleDataPath;

    CFURLRef appUrl = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    CFStringRef appPath = CFURLCopyFileSystemPath(appUrl, kCFURLPOSIXPathStyle);

    const CFIndex kCStringSize = 128;
    char temporaryCString[kCStringSize];
    bzero(temporaryCString,kCStringSize);
    CFStringGetCString(appPath, temporaryCString, kCStringSize, kCFStringEncodingUTF8);
    std::string *appPathStr = new std::string(temporaryCString);
    CFRelease(appUrl);
    CFRelease(appPath);

    CFURLRef resourceUrl = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
    CFStringRef resourcePath = CFURLCopyFileSystemPath(resourceUrl, kCFURLPOSIXPathStyle);

    bzero(temporaryCString,kCStringSize);
    CFStringGetCString(resourcePath, temporaryCString, kCStringSize, kCFStringEncodingUTF8);
    std::string *resourcePathStr = new std::string(temporaryCString);
    CFRelease(resourcePath);
    CFRelease(resourceUrl);

    _bundleDataPath = *appPathStr + "/" + *resourcePathStr + "/"; // the absolute path to the resources folder

    const char *homeDir = getenv("HOME");

    if(!homeDir){
        struct passwd* pwd;
        pwd = getpwuid(getuid());
        if (pwd){
            homeDir = pwd->pw_dir;
        }
    }

    string _AppDataPath(homeDir);
    userHome = _AppDataPath;

    _AppDataPath += "/Documents/FFTStream/data";

    std::filesystem::path tempPath(_AppDataPath.c_str());

    userAppPath = tempPath;

    ofDirectory appDir;

    // data directory
    if(!appDir.doesDirectoryExist(userAppPath)){
        appDir.createDirectory(userAppPath,true,true);

        std::filesystem::path dataPath(_bundleDataPath.c_str());

        ofDirectory dataDir(dataPath);
        dataDir.copyTo(userAppPath,true,true);
    }else{
        string relfilepath = _AppDataPath+"/release.txt";
        std::filesystem::path releasePath(relfilepath.c_str());
        ofFile relFile(releasePath);

        if(relFile.exists()){
            string actualRel = relFile.readToBuffer().getText();

            if(VERSION != actualRel){
                std::filesystem::path dataPath(_bundleDataPath.c_str());

                ofDirectory dataDir(dataPath);
                dataDir.copyTo(userAppPath,true,true);
            }
        }
    }

    ofSetDataPathRoot(userAppPath); // tell OF to look for resources here

}
