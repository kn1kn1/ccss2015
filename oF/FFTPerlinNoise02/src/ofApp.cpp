#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofBackground(0);
    ofSetLineWidth(1);
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    myImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
    pixels = myImage.getPixels();
    
//    // FFTのサンプル数(2の累乗)を指定して初期化
//    fft.setup(pow(2.0, 12.0));
    // FFT初期設定
    fft.setup();
    fft.setNumFFTBins(4);
    fft.setNormalize(true);

//    // GUI
//    gui.setup();
//    gui.add(level.setup("Input Level", 500, 0, 5000));
//    gui.loadFromFile("settings.xml");

}

//--------------------------------------------------------------
void ofApp::update(){
    fft.update(); // FFT更新
    
    // 低域、中域、高域の値を取得
    float lowValue = fft.getLowVal();
    float midValue = fft.getMidVal();
    
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            float scaleX = lowValue * 10;
            float scaleY = midValue * 10;
            float noiseX = ofMap(i, 0, width, 0, scaleX);
            float noiseY = ofMap(j, 0, width, 0, scaleY);
            int noiseVal = ofNoise(noiseX, noiseY) * 255;
            pixels[j * width + i] = noiseVal;
        }
    }
    myImage.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // GUI
//    gui.draw();
    
    ofSetColor(127);
    myImage.draw(0, 0);
    
//    float midValue = ofMap(fft.getMidVal(), 0, 1, 0, level);
    float midValue = fft.getMidVal();
//    float h = ofMap(midValue, 0, 1, 0, 255);
//    ofColor col;
//    col.setHsb(h, 128, 128);
//    ofSetColor(col);
    ofSetColor(127 * midValue);
    
    //    int skip = 5 * (ofGetFrameNum() % 10);
    int skip = (40 * midValue) + 40;
    for (int j = 0; j < height; j += skip) {
        for (int i = 0; i < width; i += skip) {
            int val = pixels[j * width + i];
            int rot = ofMap(val, 0, 255, 0, 360);
            ofPushMatrix();
            ofTranslate(i, j);
            ofRotateZ(rot);
            //            ofLine(0, -skip / 2.0, 0, skip / 2.0);
            ofLine(0, -skip * 10.0, 0, skip * 10.0);
            ofPopMatrix();
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}


//#include "ofApp.h"
//
////--------------------------------------------------------------
//void ofApp::setup(){
//    ofSetFrameRate(60);
//    ofSetVerticalSync(true);
//    ofBackground(0);
//    // FFTのサンプル数(2の累乗)を指定して初期化
//    fft.setup(pow(2.0, 12.0));
//}
//
////--------------------------------------------------------------
//void ofApp::update(){
//    fft.update(); // FFT更新
//}
//
////--------------------------------------------------------------
//void ofApp::draw(){
//    // float型の配列にFFT結果を格納
//    vector<float> buffer;
//    buffer = fft.getBins();
//    // グラフに描画
//    ofNoFill();
//    ofSetLineWidth(2.0);
//    ofBeginShape();
//    for (int i = 0; i < buffer.size(); i++) {
//        float x = ofMap(i, 0, buffer.size(), 0, ofGetWidth());
//        float y = ofMap(buffer[i], 0, 1, ofGetHeight(), 0);
//        ofVertex(x, y);
//    }
//    ofEndShape();
//}
//
////--------------------------------------------------------------
//void ofApp::keyPressed(int key){
//
//}
//
////--------------------------------------------------------------
//void ofApp::keyReleased(int key){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseMoved(int x, int y ){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseDragged(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mousePressed(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseReleased(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h){
//
//}
//
////--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg){
//
//}
//
////--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo){ 
//
//}
