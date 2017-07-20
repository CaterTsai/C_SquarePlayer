#pragma once

#include "constParameter.h"
#include "audioSet.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

public:
	void initAudio();
private:
	int _playIndex;
	vector<audioSet> _audioSets;

};
