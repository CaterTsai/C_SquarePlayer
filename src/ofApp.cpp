#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	_playIndex = -1;
	initAudio();
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	float deltaW = ofGetWidth() / 4.0f;
	float deltaH = ofGetHeight() / 3.0f;
	float size = deltaW * 0.5;

	ofSetColor(255);
	

	for (int i = 0; i < cTrackNum; i++)
	{
		ofVec2f pos(deltaW * i + deltaW, deltaH);
		_audioSets[_playIndex].isTrackOn(i)?ofSetColor(100):ofSetColor(255);
		ofDrawRectangle(pos.x - size * 0.5, pos.y - size * 0.5, size, size);
	}

	for (int i = 0; i < cTrackNum; i++)
	{
		ofVec2f pos(deltaW * i + deltaW, deltaH * 2);
		_audioSets[_playIndex].isFXOn(i) ? ofSetColor(0, 100, 0) : ofSetColor(0, 255, 0);
		ofDrawRectangle(pos.x - size * 0.5, pos.y - size * 0.5, size, size);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'n')
	{
		_audioSets[_playIndex].stop();
		_playIndex = (_playIndex + 1) % _audioSets.size();
		_audioSets[_playIndex].play();
	}
}

//--------------------------------------------------------------
void ofApp::initAudio()
{
	ofDirectory dir;
	dir.open("audios");
	int size = dir.listDir();
	_audioSets.resize(size);
	for (int i = 0; i < size; i++)
	{
		string path = dir.getAbsolutePath() + "\\" +dir.getName(i);
		_audioSets[i].load(path);
	}

	if (size > 0)
	{
		_audioSets[0].play();
		_playIndex = 0;
	}
}
