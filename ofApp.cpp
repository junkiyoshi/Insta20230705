#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	int len = 580;
	int span = 1;
	ofColor color;


	for (int x = len * -0.5; x < len * 0.5; x += span) {

		for (int y = len * -0.5; y < len * 0.5; y += span) {

			if (glm::length(glm::vec2(x, y)) > 250) { continue; }

			auto noise_value = ofMap(ofNoise(x * 0.008, y * 0.008, ofGetFrameNum() * 0.005), 0, 1, 0, 10);

			this->mesh.addVertex(glm::vec3(x, y, 0));
			this->mesh.addVertex(glm::vec3(x + span, y, 0));
			this->mesh.addVertex(glm::vec3(x + span, y + span, 0));
			this->mesh.addVertex(glm::vec3(x, y + span, 0));

			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 4); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);

			noise_value = noise_value - (int)noise_value;
			color = ofColor(ofMap(abs(noise_value - 0.5), 0, 0.5, 39, 239), 39, 39);
			for (int i = 0; i < 4; i++) {

				this->mesh.addColor(color);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	this->mesh.draw();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}