#include "testApp.h"
int nEncoderStrings = 9;
string encoderStrings[] = {
    "költészet",
    "poetry",
    "thơ",
    "詩",
    "ポエトリー",
    "поезия",
    "ಕಾವ್ಯ",
    "கவிதை",
    "أشعار"
};
//--------------------------------------------------------------
void testApp::setup(){
    
    font.loadFont("mono.ttf", 24, true, true);
    
    sampleString = "Çalıkuşu Iğdır Üzerİne Öğürdü ve çılgınca bağırdı";
    
    
    //sampleString = "I wish";
    
    p1 = ofPoint(100, 100);
    p2 = ofPoint(200, 300);
    p3 = ofPoint(300, 400);
    
    rect1 = font.getStringBoundingBox(sampleString, p1.x, p1.y);
    rect2 = font.getStringBoundingBox(sampleString, p2.x, p2.y);
    rect3 = font.getStringBoundingBox(sampleString, p3.x, p3.y);
    
    characters = font.getStringAsPoints(sampleString);
    
    //cout << font.stringWidth("Ç") << endl;
    
    for (int i=0; i < sampleString.length(); i++) {
        string currentChar  = sampleString.substr(i,1);
        //cout << ofToString(i) +"  "+currentChar << endl;
    }
    curTextLength = sampleString.length();
    bezierLength = 400;

    
    sampleString = ofUTF8::toUpper(sampleString);
    cout << "  To: " << sampleString << endl;
    
    string str = string("ni hao");
    string ni_hao = string("ÇAlışkuşu");
  
    cout << utf8_substr(ni_hao,1,0) << endl;
    cout << utf8_substr(ni_hao,0,2) << endl;
    cout << utf8_substr(ni_hao,2,2) << endl;
    
}

string testApp::utf8_substr(const string& str, unsigned int start, unsigned int leng)
{
    if (leng==0) { return ""; }
    unsigned int c, i, ix, q, min=string::npos, max=string::npos;
    for (q=0, i=0, ix=str.length(); i < ix; i++, q++)
    {
        if (q==start){ min=i; }
        if (q<=start+leng || leng==string::npos){ max=i; }
        
        c = (unsigned char) str[i];
        if      (c>=0   && c<=127) i+=0;
        else if ((c & 0xE0) == 0xC0) i+=1;
        else if ((c & 0xF0) == 0xE0) i+=2;
        else if ((c & 0xF8) == 0xF0) i+=3;
        //else if (($c & 0xFC) == 0xF8) i+=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
        //else if (($c & 0xFE) == 0xFC) i+=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
        else return "";//invalid utf8
    }
    if (q<=start+leng || leng==string::npos){ max=i; }
    if (min==string::npos || max==string::npos) { return ""; }
    return str.substr(min,max);
}

string utf8_substr2(const string &str,int start, int length=INT_MAX)
{
    int i,ix,j,realstart,reallength;
    if (length==0) return "";
    if (start<0 || length <0)
    {
        //find j=utf8_strlen(str);
        for(j=0,i=0,ix=str.length(); i<ix; i+=1, j++)
        {
            unsigned char c= str[i];
            if      (c>=0   && c<=127) i+=0;
            else if (c>=192 && c<=223) i+=1;
            else if (c>=224 && c<=239) i+=2;
            else if (c>=240 && c<=247) i+=3;
            else if (c>=248 && c<=255) return "";//invalid utf8
        }
        if (length !=INT_MAX && j+length-start<=0) return "";
        if (start  < 0 ) start+=j;
        if (length < 0 ) length=j+length-start;
    }
    
    j=0,realstart=0,reallength=0;
    for(i=0,ix=str.length(); i<ix; i+=1, j++)
    {
        if (j==start) { realstart=i; }
        if (j>=start && (length==INT_MAX || j<=start+length)) { reallength=i-realstart; }
        unsigned char c= str[i];
        if      (c>=0   && c<=127) i+=0;
        else if (c>=192 && c<=223) i+=1;
        else if (c>=224 && c<=239) i+=2;
        else if (c>=240 && c<=247) i+=3;
        else if (c>=248 && c<=255) return "";//invalid utf8
    }
    if (j==start) { realstart=i; }
    if (j>=start && (length==INT_MAX || j<=start+length)) { reallength=i-realstart; }
    
    return str.substr(realstart,reallength);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    
	ofSetColor(225);
    
    string fpsStr = "frame rate: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(fpsStr, 10, 10);
    
    
    int i = 0;
    int totalLen = 0;
	float xoff = 0;
    
	for (float x = 0; x <= ofGetWidth(); x += 20) {
        
		
        // Calculate a y value according to noise, map to
        float y = ofMap(ofNoise(xoff, yoff), 0, 1, 200,300); // Option #1: 2D Noise
        // float y = map(noise(xoff), 0, 1, 200,300);    // Option #2: 1D Noise
        
        // Set the vertex
        //ofCircle(x, y,5);
        if(x >0){
             ofLine(xPrev,yPrev,x,y);
            
            if(i < sampleString.length()){
                
                string currentChar = utf8_substr2(sampleString,i,1);
                
                
                //cout << currentChar << endl;
                
                totalLen = totalLen+font.getStringBoundingBox(currentChar, 0, 0).width;
                
                ofVec2f tanVec = ofVec2f(xPrev,yPrev) - ofVec2f(x,y);
                
                float yDiff = tanVec.y;
                float xDiff = tanVec.x;
                
                float arcTan = ofRadToDeg(atan(yDiff / xDiff));
                
                ofPushMatrix();
                
                ofTranslate(x,y);
                ofRotateZ(arcTan);
                //ofScale(0.8,0.8,1);
                font.drawStringAsShapes(currentChar, -font.getStringBoundingBox(currentChar, 0, 0).width*0.5, 0);
                //ofScale(-0.8,-0.8,1);
                /*ofRotateZ(-arcTan);
                ofTranslate(-x,-y);*/
                ofPopMatrix();
            }
            
            i++;
            
        }
        
        
        xPrev = x;
        yPrev = y;
        // Increment x dimension for noise
        xoff += ofMap(mouseX, 0, ofGetWidth(), 0,0.1);
        //xoff += 0.008;
	}
	// increment y dimension for noise
	yoff += ofMap(mouseY, 0, ofGetHeight(), 0,0.01);
	//yoff += 0.00001;
    
    curTextLength = 0;

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
