#include "testApp.h"
int nEncoderStrings = 9;
string sampleString [] = {"Ben okumayı sevİyorum","Daha çok arkadaş edİnİyoruz","TenefÜste arkadaşlarla vakit geçİrmeyİ sevİyorum",
    "Daha bÜyÜk sınıflar İsterdİm", "okulun daha bÜyÜk olmasını İsterdİm","bazen çok yoruluyoruz, hasta oluyoruz, yİne de okula gİdİyoruz",
    "tenefÜste arkadaşlarla vakİt geçİrmeyİ sevİyorum","çocuklara hayatlarında lazım olacak bİlgİ","ben en son dersİ çok sevİyorum",
"yenİ bİlgİler öğrenİyoruz","çocuklara hayatlarında lazım olacak bİlgİ","sen okumayı sevİyor musun?",
"sınavlarımızın bİttİğİ ve eğlenme vaktİmİzİn geldİğİ yaz ayları hoşuma gİdİyor","ben okulda olmayı sevİyorum, okumayı sevmİyorum","eğİtİm sİstemİ değİşmİyor, bu böyle gİdecek, katlanacağım"};
//--------------------------------------------------------------
void testApp::setup(){
    
    font.loadFont("mono.ttf", 24, true, true);
    
    
    //sampleString = "I wish";
    //characters = font.getStringAsPoints(sampleString);
    
    //cout << font.stringWidth("Ç") << endl;
    
    for (int j = 0; j < 15; j++) {
        for (int i=0; i < sampleString[j].length(); i++) {
            string currentChar  = sampleString[j].substr(i,1);
            //cout << ofToString(i) +"  "+currentChar << endl;
            
        }
        sampleString[j] = ofUTF8::toUpper(sampleString[j]);
    }
    
    bezierLength = 400;

    
   
    //cout << "  To: " << sampleString << endl;
    
    string str = string("ni hao");
    string ni_hao = string("ÇAlışkuşu");
  
    /*cout << utf8_substr(ni_hao,1,0) << endl;
    cout << utf8_substr(ni_hao,0,2) << endl;
    cout << utf8_substr(ni_hao,2,2) << endl;
    */
    
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
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
    fbo.begin();
    //
    
    //ofClear(0, 0, 0, 0);
    
    //
    
    for (int i = 0; i < 15; i++) {
        generateArcText(sampleString[i],0,400,i*30,20*(i));
        generateArcText(sampleString[i],0,400,i*40,40*(i));
    }
    
    fbo.end();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    
    ofBackground(0);
    fbo.draw(0, 0);
    
    string fpsStr = "frame rate: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(fpsStr, 10, 10);
    
         /*
    */
   

}

void testApp::generateArcText(string sampleStr, int min,int max, float _xoff, float _yoff) {
    
    int i = 0;
    int totalLen = 0;
    float xoff = _xoff;
 
    for (float x = _xoff; x < ofGetWidth(); x += 20) {
        
		
        // Calculate a y value according to noise, map to
        float y = _yoff+ofMap(ofNoise(xoff+_xoff, yoff), 0, 1, min,max); // Option #1: 2D Noise
        
        
        if(x >_xoff){
            ofSetLineWidth(1);
            ofFill();
            ofSetColor(40);
            ofSetColor(0, 255, 0);
            //ofLine(xPrev,yPrev,x,y);
           /* ofSetColor(225);
            */
            if(i < sampleStr.length()){
                
                string currentChar = utf8_substr2(sampleStr,i,1);
                
                
                //cout << currentChar << endl;
                
                totalLen = totalLen+font.getStringBoundingBox(currentChar, 0, 0).width;
                
                ofVec2f tanVec = ofVec2f(xPrev,yPrev) - ofVec2f(x,y);
                
                float yDiff = tanVec.y;
                float xDiff = tanVec.x;
                
                float arcTan = ofRadToDeg(atan(yDiff / xDiff));
                
                ofPushMatrix();
                ofTranslate(x,y);
                ofRotateZ(arcTan);
                float scaleVal = ofMap(x-_xoff, 0, ofGetWidth(), 0.1, 1);
                float alphaVal = ofMap(x-_xoff,0,ofGetWidth(),10,255);
                ofScale(1-scaleVal,1-scaleVal,1);
                
                //ofSetColor(255-(alphaVal));
               // if(i < sampleStr.length())
                //ofSetColor(0, 255, 0, ofMap(mouseX,0,ofGetWidth(),20,255));
                font.drawString(currentChar, 0, 0);
                ofPopMatrix();
            }
            
            i++;
            
        }
        
        
        xPrev = x;
        yPrev = y;
        // Increment x dimension for noise
        xoff += ofMap(mouseX, 0, ofGetWidth(), 0,0.01);
        //xoff += 0.01;
	}
	// increment y dimension for noise
	yoff += ofMap(mouseY, 0, ofGetHeight(), 0,0.01);
	//yoff += 0.003;
    
    curTextLength = 0;
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
