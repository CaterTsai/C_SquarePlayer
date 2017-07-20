#pragma once
#include "constParameter.h"

class audioSet
{
public:
	audioSet()
		:_isLoad(false)
	{};

	void load(string folder);
	void play();
	void stop();
	
	//Button Event
	void keyPressed(ofKeyEventArgs &e);
	void keyReleased(ofKeyEventArgs &e);

	bool isTrackOn(int index);
	bool isFXOn(int index);

private:
	void playFX(int index);
	void releaseFX(int index);
	void onTrack(int index);
	void offTrack(int index);

private:
	bool _isLoad;
	ofSoundPlayer _bgm;
	ofSoundPlayer _trackPlayer[cTrackNum];
	
	bool _fxCheck[cFXNum];
	ofSoundPlayer _fxPlayer[cFXNum];
	
};