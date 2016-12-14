#include "ofApp.h"

using namespace ofxCv;
using namespace cv;



void ofApp::setup() {
    
    // ==========================Box2d========================================
    box2d.init();
    box2d.setGravity(0, 0);
    box2d.createBounds();
    box2d.setFPS(60.0);
//============================================box2d==========================================
    
    
    
    
    
    
    // ----------------------------------------ofFaceTracker----------------------------------------------
    ofSetVerticalSync(true);
    cam.initGrabber(640, 480);
    
    tracker.setup();
    tracker.setRescale(.5);
}

void ofApp::update() {
    //----------------==============================box2D-=================================
    box2d.update();
       //----------------==============================box2D-=================================
    cam.update();
    if(cam.isFrameNew()) {
        if(tracker.update(toCv(cam))) {
            classifier.classify(tracker);
            
        }
    }
//------------------------------------facetracker--------------------------------------------------------------------------
}

void ofApp::draw() {
    //---------------------------------------------------facetracker----------------------------------------------------
    ofSetColor(255);
    cam.draw(0, 0);
    tracker.draw();
    
    int w = 100, h = 12;
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(5, 10);
    ofVec2f position=tracker.getPosition();
    float x =position.x;
    float y=position.y;

    int n = classifier.size();
    
    int primary = classifier.getPrimaryExpression();
    if(primary == 2){
        shared_ptr<CustomParticle> p = shared_ptr<CustomParticle>(new CustomParticle);
        p.get()->setPhysics(1.0, 0.5, 0.3);
        p.get()->setup(box2d.getWorld(), x, y, ofRandom(20, 60));
        p.get()->setVelocity(ofRandom(-30, 30), ofRandom(-30, 30));
        p.get()->setupTheCustomData();
        particles.push_back(p);

        for(int i=0; i<particles.size(); i++) {
            particles[i].get()->draw();
        }

}
//    for(int i = 0; i < n; i++){
//        ofSetColor(i == primary ? ofColor::red : ofColor::black);
//        ofDrawRectangle(0, 0, w * classifier.getProbability(i) + .5, h);
//        ofSetColor(255);
//        ofDrawBitmapString(classifier.getDescription(i), 5, 9);
//        ofTranslate(0, h + 5);
//    }
    ofPopMatrix();
    ofPopStyle();
    
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
    ofDrawBitmapStringHighlight(
                                string() +
                                "r - reset\n" +
                                "e - add expression\n" +
                                "a - add sample\n" +
                                "s - save expressions\n"
                                "l - load expressions",
                                14, ofGetHeight() - 7 * 12);
    
    
   //------------------------------------------------------facetracker----------------------------------------------------
    //===========================================================box2d===============================================
    
    string info = "FPS: "+ofToString(ofGetFrameRate(), 1);
    info += "\nClick to add particles\nThe letters and color are from the custom data.";
    ofSetHexColor(0x444342);
    ofDrawBitmapString(info, 20, 20);
    //===========================================================box2d===============================================

}

void ofApp::keyPressed(int key) {
    
 //-----------------------------------------------------facetracker-----------------------------------------------------
    
    
    if(key == 'r') {
        tracker.reset();
        classifier.reset();
    }
    if(key == 'e') {
        classifier.addExpression();
    }
    if(key == 'a') {
        classifier.addSample(tracker);
    }
    if(key == 's') {
        classifier.save("expressions");
    }
    if(key == 'l') {
        classifier.load("expressions");
    }
    //--------------------------------------------------------facetracker-------------------------------------
}


void ofApp::mousePressed(int x, int y, int button) {
    }






















