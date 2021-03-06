#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(30);
    ofEnableSmoothing();
}

//--------------------------------------------------------------
void testApp::update()
{
    //fill path
    path.clear();
    int num = mouseX/10;
    if(num < 3)
        num = 3;
    float step = (2*PI) / num;
    for(int i = num-1; i >= 0; i--)
    {
        path.push_back(ofVec2f((ofGetWidth()/2)+(100*sin(i*step)),(ofGetHeight()/2)+(100*cos(i*step))));
    }

    //make a shape from the path
    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    shape = extrude(path, mouseY/10);
    ofSetPolyMode(OF_POLY_WINDING_ODD);
    mouseShape = extrude(mousePath, mouseY/10);
}

//--------------------------------------------------------------
void testApp::draw()
{
    //draw the shape
    ofFill();
    ofSetColor(0);
    ofBeginShape();
    for(int i = 0; i < shape.size(); i++)
    {
        ofVertex(shape[i].x,shape[i].y);
    }
    ofEndShape();

    //draw the mouse shape
    ofBeginShape();
    for(int i = 0; i < mouseShape.size(); i++)
    {
        ofVertex(mouseShape[i].x,mouseShape[i].y);
    }
    ofEndShape();

    ofSetPolyMode(OF_POLY_WINDING_NONZERO);

    //draw the path
    ofNoFill();
    ofSetColor(255,0,0);
    ofSetLineWidth(2);
    ofBeginShape();
    for(int i = 0; i < path.size(); i++)
    {
        ofVertex(path[i].x,path[i].y);
    }
    ofEndShape();

    //draw the mousePath
    ofSetPolyMode(OF_POLY_WINDING_ODD);
    ofSetColor(0,0,255);
    ofBeginShape();
    for(int i = 0; i < mousePath.size(); i++)
    {
        ofVertex(mousePath[i].x,mousePath[i].y);
    }
    ofEndShape();

}

vector<ofVec2f> testApp::extrude(vector<ofVec2f> _path, float _width)
{
    int size = _path.size();
    vector<ofVec2f> temp;
    for(int i = 0; i < size; i++)
    {
        //getting the two path segments around a given path point
        ofVec2f d1 = _path[i] - _path[(i+size-1) % size];
        ofVec2f d2 = _path[(i+1) % size] - _path[i];

        //calculating the angle bisector
        ofVec2f t = d1.getPerpendicular() - d2.getPerpendicular();
        t.rotate(-90);

        //calculating the correct width for the angle bisector (needs to be longer because of its angle)
        float w;
        if(sin(t.angleRad(d1)) != 0)
            w = (_width/2) / sin(t.angleRad(d1));
        else
            w = (_width/2);
        t.scale(w);
        temp.push_back(t + _path[i]);
        t.scale(-w);
        temp.push_back(t + _path[i]);
    }

    //IF polyMode == OF_POLY_WINDING_NONZERO
    //TODO: fix this for paths with size < 3
    if(ofGetStyle().polyMode == 0 && size > 2)
    {
        temp[0] = (_path[0] - _path[1]).getPerpendicular().scale(_width/2) + _path[0];
        temp[1] = (_path[0] - _path[1]).getPerpendicular().scale(-_width/2) + _path[0];
        temp[temp.size()-2] = (_path[size-2] - _path[size-1]).getPerpendicular().scale(_width/2) + _path[size-1];
        temp[temp.size()-1] = (_path[size-2] - _path[size-1]).getPerpendicular().scale(-_width/2) + _path[size-1];
    }

    vector<ofVec2f> ret;
    if(temp.size() > 2)
    {
        for(int i = 0; i < temp.size(); i++)
        {
            if(i % 2 != 0)
                ret.push_back(temp[i]);
        }
        for(int i = temp.size()-1; i > 0; i--)
        {
            if(i % 2 == 0)
                ret.push_back(temp[i]);
        }
        ret.push_back(temp[0]);

        //IF polyMode != OF_POLY_WINDING_NONZERO
        if(ofGetStyle().polyMode != 0)
        {
            //add two more points to close the shape
            ret.push_back(temp[temp.size()-2]);
            ret.push_back(temp[temp.size()-1]);
        }
    }
    return ret;
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
    if(button == 0)
    {
        mousePath.push_back(ofVec2f(x,y));
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if(button == 2)
    {
        mousePath.clear();
    }
    if(button == 0)
    {
        mousePath.push_back(ofVec2f(x,y));
    }
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
