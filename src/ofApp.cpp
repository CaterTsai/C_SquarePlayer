#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	loadConfig();
	_playIndex = -1;
	initAudio();
	setupLight();
	ofBackground(0);

	_isIdle = true;
	_changeTimer = _exChangeTime;
	_idleTimer = _exIdleAnimTime;
	_timer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update()
{
	float delta = ofGetElapsedTimef() - _timer;
	_timer += delta;

	_changeTimer -= delta;
	if (_changeTimer <= 0)
	{
		change();
		_changeTimer = _exChangeTime;
	}

	_idleTimer -= delta;
	if (!_isIdle)
	{
		//Check Idle		
		if (_idleTimer < 0)
		{
			_isIdle = true;
			_idleTimer = _exIdleAnimTime;
		}
	}
	else
	{
		if (_idleTimer < 0)
		{
			_lightCtrl.idleLight();
			_idleTimer = _exIdleAnimTime;
		}
	}
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

	if (_isIdle)
	{
		ofSetColor(255, 255, 0);
		ofDrawCircle(10, 10, 10);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'n')
	{
		change();
		_changeTimer = _exChangeTime;
	}
	_isIdle = false;
	_idleTimer = _exIdleTime;
}

//--------------------------------------------------------------
void ofApp::change()
{
	_audioSets[_playIndex].stop();
	_playIndex = (_playIndex + 1) % _audioSets.size();
	_audioSets[_playIndex].play();
	_lightCtrl.setType(_playIndex);
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

//--------------------------------------------------------------
void ofApp::setupLight()
{

	sender::GetInstance()->add(eLightType::eFrontLeftS, _exSerialPort1, 115200);
	sender::GetInstance()->add(eLightType::eFrontRightS, _exSerialPort2, 115200);
	//sender::GetInstance()->add(eLightType::eFrontLeftS, "192.168.1.173", 11999);

	_lightCtrl.enable();
	_lightCtrl.setType(_playIndex);
}

//--------------------------------------------------------------
void ofApp::loadConfig()
{
	ofxXmlSettings	_xml;
	_xml.loadFile("_config.xml");

	_exSerialPort1 = _xml.getValue("serial1", "", 0);
	_exSerialPort2 = _xml.getValue("serial2", "", 0);

	_exIdleTime = _xml.getValue("idleTime", 60, 0);
	_exIdleAnimTime = _xml.getValue("idleAnimTime", 4, 0);
	_exChangeTime = _xml.getValue("changeTime", 600, 0);

}
