#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	ofEnableSmoothing();
	ofSetVerticalSync(true);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	Furikos.clear();
	double T[15] = { (double)60/60,(double)60/58,(double)60/56,(double)60/54,(double)60/52,(double)60/50,(double)60/48,(double)60/46,(double)60/44,(double)60/42,(double)60/40,(double)60/38,(double)60/36,(double)60/34,(double)60/32};

	for (int i = 0; i < 15; i++)
	{
		Furiko furiko;
		furiko.setup(calLength(T[i],(double)15/180*M_PI), 15);
		Furikos.push_back(furiko);
	}

	//�R�����̕`����ȒP�ɂ��邱�Ƃ������ӎ��������C�u�����ł�
	//���_�ݒ���ȒP�ɂł���悤�ȃN���X���p�ӂ���Ă��܂�
	
	//draw()�̒�
	//�J�����@�\�̊J�n
}

//--------------------------------------------------------------
void ofApp::update(){
	if (start)
	{
		for (int i = 0; i < Furikos.size(); i++)
		{
			Furikos[i].caltheta(ofGetElapsedTimeMillis());
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	
		ofSetLineWidth(1);
		for (int i = 0; i < Furikos.size(); i++)
		{
			ofSpherePrimitive sphere;
			ofPoint p1(0, 0 + ofGetHeight() / 2, -i * 30);
			ofPoint p2(Furikos[i].Length * 2000 * cos(Furikos[i].Theta - M_PI / 2), ofGetHeight() / 2 + Furikos[i].Length *2000 * sin(Furikos[i].Theta - M_PI / 2), -i * 30);

			ofSetColor(255, 255, 255);
			ofDrawLine(p1, p2);
			ofSetColor(calcolor(Furikos[i].Theta, (double)40 / 180 * M_PI));
			sphere.set(20, 3);
			sphere.setPosition(p2);
			sphere.draw();
		}
		ofSetColor(255, 255, 255);
		ofPoint p1(0, 0 + ofGetHeight() / 2, 0);
		ofPoint p2(0, 0 + ofGetHeight() / 2, -420);
		ofSetLineWidth(10);
		ofDrawLine(p1, p2);
	
	cam.end();

	stringstream ss;
	ss << "framerate: " << ofToString(ofGetFrameRate(), 0);
	ofDrawBitmapString(ss.str(), 10, 20);
	
}

ofColor ofApp::calcolor(double digree,double max) {

	double colorR, colorG, colorB;
	double i = (digree + max) / (2 * max) * 300;
	if (i < 100)
	{
		colorR = (double)255 / 100 * (double)i;
		colorG = 0;
		colorB = (double)255 - 255 / 100 * (double)i;
	}
	else if (i < 200)
	{
		colorR = (double)510 - 255 / 100 * (double)i;
		colorG = (double)255 / 100 * (double)i - 255;
		colorB = 0;
	}
	else
	{
		colorR = 0;
		colorG = (double)765 - 255 / 100 * (double)i;
		colorB = (double)255 / 100 * (double)i - 510;
	}
	ofColor color(colorR, colorG, colorB);
	
	return (color);
}

double ofApp::calLength(double time, double theta) {

	double A;

	A = (time*time)*9.8 / (4 * M_PI*M_PI);

	double E = 1;
	for (int i = 1; i < 30; i++)
	{
		double B = 1;
		for (int j = 1; j < i+1; j++)
		{
			B *= (2*j-1);
		}
		double C=1;
		for (int k = 1; k < i+1; k++)
		{
			C *=(2*k);
		}
		double D=1;
		for (int l = 0; l < 2 * i; l++)
		{
			D *= sin(theta / 2);
		}
		double E1 = 0;
		E1 = ((double)B*(double)B) / ((double)C *(double)C)*D;
		E += E1;
		//cout << E << endl;
	}
	double Length;
	Length = (double)A / ((double)E*(double)E);
	//Length = E;
	//cout << E << endl;
	return Length;
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's')
	{
		start = true;
		for (int i = 0; i < Furikos.size(); i++)
		{
			Furikos[i].beforetime=ofGetElapsedTimeMillis();
		}
	}
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