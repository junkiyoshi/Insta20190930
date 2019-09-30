#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	ofColor color;
	vector<int> hex_list = { 0x247BA0, 0x70C1B3, 0xB2DBBF, 0xF3FFBD, 0xFF1654 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotate(ofGetFrameNum() * 0.5);
	
	int depth = 15;
	int color_index = 0;
	for (auto len = 30; len <= 300; len += 15) {

		ofSetColor(this->color_list[(color_index++) % this->color_list.size()]);

		ofPushMatrix();
		ofRotateZ(ofRandom(360));
		ofRotateY(ofRandom(360));
		ofRotateX(ofRandom(360));

		int param_start = ofRandom(1000) + ofGetFrameNum();
		for (int param = param_start; param < param_start + 30; param++) {

			ofBeginShape();
			ofVertex(glm::vec3(this->make_point(len, param), depth * 0.5));
			ofVertex(glm::vec3(this->make_point(len, param + 1), depth * 0.5));
			ofVertex(glm::vec3(this->make_point(len, param + 1), depth * -0.5));
			ofVertex(glm::vec3(this->make_point(len, param), depth * -0.5));
			ofEndShape(true);
		}

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}