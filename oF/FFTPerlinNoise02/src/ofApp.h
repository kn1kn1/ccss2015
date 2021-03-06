#pragma once

#include "ofMain.h"
#include "ofxEasyFft.h"
#include "ofxProcessFFT.h"
#include "ofxGui.h"

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
    
//    ofxEasyFft fft;    // ofxEasyFftインスタンス
    ProcessFFT fft;         // FFT分析
    ofxPanel gui;           // GUI
    ofxFloatSlider level;   // 入力レベル調整
    int width, height;
    ofImage myImage;
    unsigned char * pixels;
};
