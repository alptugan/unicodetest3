#pragma once

#include "ofMain.h"
#include "stdio.h"
#include "assert.h"

#include "ofMain.h"

#include "ofUTF8.h"
//#include "ofUTF16.h"
#include "ofUnicode.h"
#include "ofTextConverter.h"

#include "ofxTrueTypeFontUC.h"

class testApp : public ofBaseApp{
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
    
    void generateArcText(string sampleStr, int min,int max,float _xoff,float _yoff);
    
    string utf8_substr(const string& str, unsigned int start, unsigned int leng);
    
    ofPoint tangentVector(float t, ofPoint a, ofPoint b, ofPoint c, ofPoint d);
    
    ofxTrueTypeFontUC font;
    
    ofPoint p1, p2, p3;
    ofRectangle rect1, rect2, rect3;
    vector<ofPath> characters;
    
    float charWidth;
    float charHeight;
    float charPctPosAlongPath;
    float curPos;
    float curTextLength;
    float bezierLength;
    float pctPosStartOffset;
    ofPoint startPoint;
    ofPoint endPoint;
    ofPoint pt;
    ofPoint tanPt;
    ofPoint perPt;
    ofPoint cP1;
    ofPoint cP2;
    
    ofFbo fbo;
    
    
    float yoff;
    
    float xPrev;
    float yPrev;
};
