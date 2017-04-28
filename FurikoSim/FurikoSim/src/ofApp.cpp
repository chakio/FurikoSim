#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofBackground(0, 0, 0);
	ofSetFrameRate(30);
	ofEnableSmoothing();
	ofSetVerticalSync(true);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	Furikos.clear();
	double T[15] = { (double)60/60,(double)60/58,(double)60/56,(double)60/54,(double)60/52,(double)60/50,(double)60/48,(double)60/46,(double)60/44,(double)60/42,(double)60/40,(double)60/38,(double)60/36,(double)60/34,(double)60/32};
	for (int i = 0; i < 15; i++)
	{
		Furiko furiko;
		furiko.setup((T[i])*(T[i])*9.8/(4*M_PI*M_PI), 60);
		Furikos.push_back(furiko);
	}

	//３次元の描画を簡単にすることを強く意識したライブラリです
	//視点設定も簡単にできるようなクラスが用意されています
	
	//draw()の中
	//カメラ機能の開始
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < Furikos.size(); i++)
	{
		Furikos[i].caltheta(ofGetElapsedTimeMillis());
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	ofSetLineWidth(2);
	for (int i = 0; i < Furikos.size(); i++)
	{
		ofSpherePrimitive sphere;
		ofPoint p1(0, 0+ofGetHeight()/4*0, -i * 30);
		ofPoint p2(Furikos[i].Length *500*cos(Furikos[i].Theta-M_PI/2), ofGetHeight() / 4*0+ Furikos[i].Length *500*sin(Furikos[i].Theta - M_PI / 2), -i * 30);
		ofSetColor(255, 255, 255);
		ofDrawLine(p1, p2);
		sphere.set(10, 16);
		sphere.setPosition(p2);
		sphere.draw();
	}
	ofPoint p1(0, 0 + ofGetHeight() / 4*0, 0);
	ofPoint p2(0, 0 + ofGetHeight() / 4*0, -420);
	ofSetLineWidth(10);
	ofDrawLine(p1, p2);
	cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

Furiko::Furiko() {

}

void Furiko::setup(double length, double theta0) {
	Length = length;
	Theta = theta0/180*M_PI;
}

void Furiko::caltheta(int time)
{
	Dtime = time - beforetime;
	Dtime /= 1000;
	a = -g / Length*sin(Theta);
	v = v + a*Dtime;
	Theta = Theta + v*Dtime;
	beforetime = time;
}