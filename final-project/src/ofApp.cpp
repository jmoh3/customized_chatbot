#include "ofApp.h"
#include "ofxGui.h"
#include "NLP/Model.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetWindowTitle("Chat");
  ofSetFrameRate(60); // run at 60 fps
  ofSetVerticalSync(true);
  
  // set bg to white
  ofBackground(255);
  
  string filename = "/Users/jackieoh/Desktop/cs126/openFrameworks/apps/myApps/final-project-jmoh3/final-project/data/messages/filtered_threads/themegans_1dhgynipdq/message_1.json";
  string user = "Jackie Oh";
  
  model = new Model(filename, user);
}

//--------------------------------------------------------------
void ofApp::update(){
  
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(200);
  
  ofRectangle messageBar(0, ofGetWindowHeight() - 60, ofGetWindowWidth(), 60);
  ofDrawRectangle(messageBar);
  
  ofRectangle header(0, 0, ofGetWindowWidth(), ofGetWindowHeight() / 10);
  ofDrawRectangle(header);
  
  ofSetColor(255);
  
  ofRectangle messageConsole(10, ofGetWindowHeight() - 40, ofGetWindowWidth() - 20, 30);
  ofDrawRectRounded(messageConsole, 5);
  
  ofSetColor(200);
  ofDrawBitmapString(currentMessage, 15, ofGetWindowHeight() - 25);
  
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  ofSetColor(200);
  if(key == OF_KEY_DEL || key == OF_KEY_BACKSPACE){
    currentMessage = currentMessage.substr(0, currentMessage.length()-1);
  }
  else if(key == OF_KEY_RETURN ){
    ofSetColor(200);
    string response = model->getResponse(currentMessage);
    std::cout << response << std::endl;
    ofDrawBitmapString(response, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    
    currentMessage = "";
  } else {
    currentMessage.append(1, (char)key);
    ofDrawBitmapString(currentMessage, 15, ofGetWindowHeight() - 25);
  }
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
