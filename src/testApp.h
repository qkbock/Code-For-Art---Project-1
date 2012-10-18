#pragma once

#include "ofMain.h"

#define NUMBEROFPOINTS 1024
#define NUMBEROFSPLASHES 50

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    
    //0 will be the set that is drawn, 1 the previous frame and 2 the frame before that
    float points[NUMBEROFPOINTS][3];
    float heightChangeCurrent[NUMBEROFPOINTS];
    float heightChangePrevious[NUMBEROFPOINTS];
    float time;
    int mouseCrossedX;
    float pmouseCrossedX;
    float mouseCrossedY;
    float pmouseCrossedY;
    
    float currentAndPreviousX[2];
    float currentAndPreviousY[2];
    float incriment;
    float propigation;
    float speed;
    int waveWidth;
    
    ofPoint sun;
    float counter;
    ofColor sky;
    
    ofPoint splashes[NUMBEROFSPLASHES];
    float xVel[NUMBEROFSPLASHES];
    float yVel[NUMBEROFSPLASHES];
    bool splashOn;
    float gravity;
    float waterOpacity;
    float waterCounter;
};
