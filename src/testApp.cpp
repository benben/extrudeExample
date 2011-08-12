#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
 ofSetFrameRate(30);
}

//--------------------------------------------------------------
void testApp::update(){
    num = mouseX/10;
    if(num < 3)
        num = 3;
    r = 100;
    w = mouseY/10;
    vecs.clear();
    float step = (2*PI) / num;
    for(int i = 0; i < num; i++)
    {
        vecs.push_back(ofVec2f((ofGetWidth()/2)+(r*sin(i*step)),(ofGetHeight()/2)+(r*cos(i*step))));
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    int width = 100;
    ofEnableSmoothing();
    ofNoFill();
    ofSetColor(0);
    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    pvecs.clear();
    ofBeginShape();
    for(int i = 0; i < num; i++)
    {
        //cout << i << " - " << (i+num-1) % num << endl;
        ofVec2f d = vecs[i] - vecs[(i+num-1) % num];
        pvecs.push_back(d.getPerpendicular());
        //ofVertex(vecs[i].x,vecs[i].y);
    }
    ofEndShape();
    shape.clear();
    for(int i = 0; i < num; i++)
    {
        ofVec2f t;
        t = pvecs[i] * -w;
        t += vecs[i].getMiddle(vecs[(i+num-1) % num]);
        shape.push_back(t);
        //ofLine((vecs[i].getMiddle(vecs[(i+num-1) % num])).x,(vecs[i].getMiddle(vecs[(i+num-1) % num])).y,t.x,t.y);
        t = pvecs[i] * w;
        t += vecs[i].getMiddle(vecs[(i+num-1) % num]);
        shape.push_back(t);
        //ofLine((vecs[i].getMiddle(vecs[(i+num-1) % num])).x,(vecs[i].getMiddle(vecs[(i+num-1) % num])).y,t.x,t.y);
    }
    ofFill();
    if(shape.size() > 1)
    {
        ofBeginShape();
        for(int i = 0; i < num*2; i++)
        {
            if(i % 2 != 0)
                ofVertex(shape[i].x,shape[i].y);
        }
        for(int i = num*2-1; i > 0; i--)
        {
            if(i % 2 == 0)
                ofVertex(shape[i].x,shape[i].y);
        }
        ofVertex(shape[0].x,shape[0].y);
        ofVertex(shape[shape.size()-2].x,shape[shape.size()-2].y);
        ofVertex(shape[shape.size()-1].x,shape[shape.size()-1].y);
        ofEndShape();
    }
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
