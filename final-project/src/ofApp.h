#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "NLP/Model.h"

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
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
  
private:
  void drawMessages();
  
  const int kBackgroundColorWhite = 255;
  const int kLightGreyHighlight = 200;
  
  int headerHeight;
  int messageConsoleHeight;
  
  const int kMessageBarHeight = 60;
  const int kMessageConsoleHeight = 30;
  
  const int kOffsetX = 10;
  const int kMessageOffsetX = 15;
  const int kMessageOffsetY = 25;
  
  const int kMessageConsoleRadius = 5;
  
  const int kIconDimension = 50;

  string user;
  
  vector<pair<string,string>> messageList;
  string currentMessage;
  
  ofTrueTypeFont font;
  ofTrueTypeFont responseFont;
  
  Model* model;
  ofxGuiGroup messagesView;
  
  ofImage userIcon;
  
  ofColor color;
  
};
