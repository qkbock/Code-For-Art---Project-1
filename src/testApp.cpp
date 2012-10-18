#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    //set frame rate
    ofSetFrameRate(200);
    ofEnableAlphaBlending();
    ofSetCircleResolution(100);
    ofBackground(106, 203, 255);
    //set up two D array so that all values are = to zero
    for (int i = 0; i < NUMBEROFPOINTS; i++) {
        for(int j = 0; j < 3; j++){
            points[i][j] = 0;
        }
    }
    //set how quickly/how far out the wave will go
    speed = 5;
    propigation = 1/speed;
    //set the wave height
    incriment = 10;
    //the wave width is kinda the frequency
    waveWidth = 30;
    
    
    
    //set up sun
    counter = 4.77;
    sun.x = 100;
    
    //set up sky
    sky.r = 106;
    sky.g = 203;
    sky.b = 255;
    
    splashOn = false;
    gravity = .05;
}

//--------------------------------------------------------------
void testApp::update(){
    
    //move each point according to the values next to it
    for(int i = 0; i < NUMBEROFPOINTS; i++){
        // keep the points at either end fixed
        if(i == 0 || i == NUMBEROFPOINTS){
            points[i][0] = 0;
        }
        //the new height for the point will equal information from its previous frame + the previous frame from the point on either side of it + the oppisit of its value from 2 frames ago.  All of this will be  multipled by .99 so that it slowly dampens and times 1.008 propigation.  I am not quite sure the significance of this, I guessed and checked until I liked how it looked and 1.008 was that number
        else{
            points[i][0] = propigation*1.005 * (-speed*points[i][2] + 2*(speed-1)*points[i][1] + points[i-1][1] + points[i+1][1]) *.99;
        }
    }
    
    //dont let it bounce up too high
    for(int i = 0; i < NUMBEROFPOINTS; i++){
        if(points[i][0] > 300){
            points[i][0] = 300;
        }
        if(points[i][1] > 300){
            points[i][1] = 300;
        }
        if(points[i][2] > 300){
            points[i][2] = 300;
        }
        if(points[i][0] < -300){
            points[i][0] = -300;
        }
        if(points[i][1] < -300){
            points[i][1] = -300;
        }
        if(points[i][2] < -300){
            points[i][2] = -300;
        }
    }
    
    //make the line smoother by making each point the average of the two on either side of it
    for(int i = 2; i < NUMBEROFPOINTS - 2; i++){
        points[i][0] = points[i-2][0]*.25 + points[i-1][0]*.25 + points[i+1][0]*.25 + points[i+2][0]*.25;
    }
    
    //move everything down one spot so that the information is stored for the last frame and two frames ago
    for(int i = 0; i < NUMBEROFPOINTS; i++){
        points[i][2] = points[i][1];
        points[i][1] = points[i][0];
    }
    
    
    //move sun
    sun.x += .1;
//    float yValue = ofMap(sun.x, 0, ofGetWidth(), 0, 2*PI);
    counter += .0005;
    sun.y = sin(counter)*170 + 210;
    
    if(sun.x > ofGetWidth()+75){
        sun.x = -75;
    }
}


//--------------------------------------------------------------
void testApp::draw(){
    sky.r = ofMap(sun.y, 0, 350, 106, 44);
    sky.g = ofMap(sun.y, 0, 350, 203, 46);
    sky.b = ofMap(sun.y, 0, 350, 255, 126);
    ofBackground(sky);
    
    
    //draw moon
    float moonOpacity = ofMap(sun.y, 315, 380, 0, 220);
    ofSetColor(209, 209, 211, moonOpacity-100);
    ofCircle(900, 100, 35);
    ofSetColor(209, 209, 211, moonOpacity-50);
    ofCircle(900, 100, 38);
    ofSetColor(155, 155, 155, moonOpacity-150);
    ofCircle(910, 90, 13);
    ofSetColor(155, 155, 155, moonOpacity-150);
    ofCircle(910, 90, 10);
    ofSetColor(155, 155, 155, moonOpacity-150);
    ofCircle(885, 98, 6);
    ofSetColor(155, 155, 155, moonOpacity-150);
    ofCircle(885, 98, 8);
    ofSetColor(155, 155, 155, moonOpacity-150);
    ofCircle(890, 125, 8);
    ofSetColor(155, 155, 155, moonOpacity-150);
    ofCircle(890, 125, 10);
    ofSetColor(155, 155, 155, moonOpacity-150);
    ofCircle(920, 123, 5);
    ofSetColor(155, 155, 155, moonOpacity-150);
    ofCircle(920, 123, 7);
    ofSetColor(155, 155, 155, moonOpacity-150);
    ofCircle(920, 110, 5);
    ofSetColor(155, 155, 155, moonOpacity-150);
    ofCircle(920, 110, 7);
    ofSetColor(155, 155, 155, moonOpacity-150);
    ofCircle(890, 75, 5);
    ofSetColor(155, 155, 155, moonOpacity-150);
    ofCircle(890, 75, 7);
    
    //draw the sun
    if(sun.y < 365){
        ofSetColor(254, 240, 144, 50);
        ofCircle(sun, 50);
        ofSetColor(254, 240, 144, 50);
        ofCircle(sun, 45);
        ofSetColor(254, 240, 144, 50);
        ofCircle(sun, 40);
        ofSetColor(254, 240, 144, 50);
        ofCircle(sun, 35);
        ofSetColor(254, 240, 144, 255);
        ofCircle(sun, 30);
    }
    

    
    //translate everything to the middle of the screen
    ofPushMatrix();
    ofScale(1, -1);
    ofTranslate(0, -ofGetHeight());
    OF_RECTMODE_CORNER;
    // draw all the points as rectangles
    for (int i = 0; i < NUMBEROFPOINTS; i++) {
        ofSetColor(13, 110, 177, 255);
        ofRect(i, 0, 1, 450-points[i][0]);
        ofSetColor(144, 209, 254, 15);
        ofRect(i, 0, 1, 400-points[i][0]*.9);
        ofSetColor(144, 209, 254, 15);
        ofRect(i, 0, 1, 350-points[i][0]*.8);
        ofSetColor(144, 209, 254, 15);
        ofRect(i, 0, 1, 300-points[i][0]*.7);
        ofSetColor(144, 209, 254, 15);
        ofRect(i, 0, 1, 250-points[i][0]*.6);
        ofSetColor(144, 209, 254, 15);
        ofRect(i, 0, 1, 200-points[i][0]*.5);
        ofSetColor(144, 209, 254, 15);
        ofRect(i, 0, 1, 150-points[i][0]*.4);
        ofSetColor(144, 209, 254, 15);
        ofRect(i, 0, 1, 100-points[i][0]*.3);
        ofSetColor(144, 209, 254, 15);
        ofRect(i, 0, 1, 50-points[i][0]*.2);
    }
    ofPopMatrix();
    
    if(splashOn == true){
        for(int i = 0; i < NUMBEROFSPLASHES; i++){
            waterOpacity = ofMap(waterCounter, 0, 150, 200, 0);
            yVel[i] += gravity;
            splashes[i].x += xVel[i];
            splashes[i].y += yVel[i];
            ofSetColor(225, waterOpacity);
            ofCircle(splashes[i], 2);
        }
        waterCounter++;
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    //constrain clicking and movement to inside the frame
    if(x > 0 && x < ofGetWidth()){
        for(int i = 0; i < NUMBEROFPOINTS; i++) {
            //move the line if you are close to the line
            float distance = ofDist(i, 320, x, y);
            if(distance < 1){
                float decreaser = .99;
                //move the point where your mouse is to the be the highest
                points[x][2] = incriment;
                //move the surrounding "waveWidth" points to be slightly below the peak of the wave
                for(int k = 0; k < waveWidth; k++){
                    points[x-k][2] = incriment*.99;
                    decreaser-=.2;
                }
                //make a splash
                for(int i = 0; i < NUMBEROFSPLASHES; i++){
                    splashes[i].x = x;
                    splashes[i].y = y;
                    xVel[i] = ofRandom(-2, 2);
                    yVel[i] = ofRandom(-1, -4);
                    waterOpacity = 200;
                    waterCounter = 0;
                    splashOn = true;
                }
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    if(x > 0 && x < ofGetWidth()){
        points[x][2] = incriment;
    }
}


//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    cout << y << endl;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    if(x > 0 && x < ofGetWidth()){
        float decreaser = .99;
        points[x][2] = incriment;
        for(int k = 0; k < waveWidth; k++){
            points[x-k][2] = incriment*.99;
            decreaser-=.2;
        }
    }
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





// reference: http://www.openprocessing.org/sketch/14656