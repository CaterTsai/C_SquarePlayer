#pragma once

#include "ofxXmlSettings.h"
#include "constParameter.h"
#include "audioSet.h"
#include "lightCtrl.h"


class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void change();

public:
	void initAudio();
	
private:
	bool _isIdle;
	float _timer, _idleTimer, _changeTimer;
	int _playIndex;
	vector<audioSet> _audioSets;

#pragma region light
public:
	void setupLight();

private:
	lightCtrl _lightCtrl;
#pragma endregion

#pragma region Confing
public:
	void loadConfig();

private:
	string _exSerialPort1, _exSerialPort2;
	int _exIdleTime, _exIdleAnimTime, _exChangeTime;
#pragma endregion

};
