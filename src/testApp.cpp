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
    for(int i = 0; i < num; i++)
    {
        path.push_back(ofVec2f((ofGetWidth()/2)+(100*sin(i*step)),(ofGetHeight()/2)+(100*cos(i*step))));
    }

    //make a shape from the path
    shape = extrude(path, mouseY/10);

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
    ofBeginShape();
    for(int i = 0; i < path.size(); i++)
    {
        ofVertex(path[i].x,path[i].y);
    }
    ofEndShape();

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
    vector<ofVec2f> temp;
    for(int i = 0; i < _path.size(); i++)
    {
        ofVec2f t;
        ofVec2f d = _path[i] - _path[(i+_path.size()-1) % _path.size()];
        ofVec2f p = d.getPerpendicular();

        t = p * -_width/2;
        t += _path[i].getMiddle(_path[(i+_path.size()-1) % _path.size()]);
        temp.push_back(t);
        t = p * _width/2;
        t += _path[i].getMiddle(_path[(i+_path.size()-1) % _path.size()]);
        temp.push_back(t);
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
        ret.push_back(temp[temp.size()-2]);
        ret.push_back(temp[temp.size()-1]);
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
        cout << x << endl;
        mousePath.push_back(ofVec2f(x,y));
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if(button == 2)
    {
        mousePath.clear();
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
