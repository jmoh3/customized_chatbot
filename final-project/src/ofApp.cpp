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
  
  user = "Fiza Goyal";
  
  model = new Model(filename, user);
  
  font.load(OF_TTF_SANS, 12);
  responseFont.load(OF_TTF_SANS, 12);

userIcon.load("/Users/jackieoh/Desktop/cs126/openFrameworks/apps/myApps/final-project-jmoh3/final-project/src/user_icon.png");
  
}

//--------------------------------------------------------------
void ofApp::update(){
  
}

//--------------------------------------------------------------
void ofApp::draw(){
  // draw message bar at bottom
  ofSetColor(kLightGreyHighlight);
  ofRectangle messageBar(0, ofGetWindowHeight() - kMessageBarHeight, ofGetWindowWidth(), kMessageBarHeight);
  ofDrawRectangle(messageBar);
  
  // draw header background
  ofRectangle header(0, 0, ofGetWindowWidth(), ofGetWindowHeight() / 8);
  ofDrawRectangle(header);
  
  ofSetColor(255);
  
  // draw little white strip where message in progress appears
  ofRectangle messageConsole(kOffsetX, ofGetWindowHeight() - kMessageConsoleHeight - kOffsetX, ofGetWindowWidth() - 20, kMessageConsoleHeight);
  ofDrawRectRounded(messageConsole, kMessageConsoleRadius);
  
  ofColor textColor;
  
  // draw message being typed
  ofSetColor(textColor.black);
  font.drawString(currentMessage, kMessageOffsetX, ofGetWindowHeight() - kMessageOffsetY);
  
  // code from https://github.com/armadillu/ofxCenteredTrueTypeFont/blob/master/src/ofxCenteredTrueTypeFont.h
  // draw's user's
  ofRectangle r = font.getStringBoundingBox(user, 0, 0);
  ofVec2f offsetVec( floor(-r.x - r.width * 0.5f), floor(-r.y - r.height * 0.5f) );

  font.drawString(user, ofGetWindowWidth() / 2 + offsetVec.x, ofGetWindowHeight() / 20 + kIconDimension / 2 + offsetVec.y + kMessageOffsetY - 10);
  
  // draw icon
  userIcon.draw(ofGetWindowWidth() / 2 - kIconDimension / 2, ofGetWindowHeight() / 20 - kIconDimension / 2, kIconDimension, kIconDimension);
  
  // draw messages
  drawMessages();
  
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  ofSetColor(200);
  
  // code from https://forum.openframeworks.cc/t/keypressed-and-getting-the-special-keys/5727/2
  if (key == OF_KEY_DEL || key == OF_KEY_BACKSPACE) {
    currentMessage = currentMessage.substr(0, currentMessage.length()-1);
  }
  else if (key == OF_KEY_RETURN) {
    ofColor textColor;
    
    ofSetColor(textColor.black);
    pair<string, string> newMessageToSend("You", currentMessage);
    messageList.push_back(newMessageToSend);
    
    string response = model->getResponse(currentMessage);
    
    pair<string, string> newIncomingMessage(user, response);
    messageList.push_back(newIncomingMessage);
    
    currentMessage = "";
    drawMessages();
    
  } else if (key != OF_KEY_SHIFT) {
    ofColor textColor;
    
    ofSetColor(textColor.black);
    
    currentMessage.append(1, (char)key);
    font.drawString(currentMessage, kMessageOffsetX, ofGetWindowHeight() - kMessageOffsetY);
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
  
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
  
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
  
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
  
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
  
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
  
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
  
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
  
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
  
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) { 
  
}

//--------------------------------------------------------------
void ofApp::drawMessages() {
  int startY = ofGetWindowHeight() / 8;
  int messageHeight = ofGetWindowHeight() / 20;
  int whiteBackground = false;
  
  for (auto it = messageList.begin(); it != messageList.end(); it++) {
    // draw rectangle background
    if (!whiteBackground) {
      ofColor rectColor;
      ofSetColor(rectColor.lightBlue);
      
      ofRectangle messageRect(0, startY, ofGetWindowWidth(), messageHeight);
      ofDrawRectangle(messageRect);
    }
    
    // draw text
    ofColor textColor;
    ofSetColor(textColor.black);
    
    responseFont.drawString(it->first, kMessageOffsetX, startY + kMessageOffsetX);
    
    responseFont.drawString(it->second, kMessageOffsetX * 12, startY + kMessageOffsetX);
    
    startY += messageHeight;
    whiteBackground = !whiteBackground;
  }
}
