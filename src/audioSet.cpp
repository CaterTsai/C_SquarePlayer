#include "audioSet.h"

//---------------------------------------------
void audioSet::load(string folder)
{
	bool isAllSuccess = true;
	//Track
	for (int i = 0; i < cTrackNum; i++)
	{
		isAllSuccess &= _trackPlayer[i].load(folder + "/track_" + ofToString(i + 1) + ".wav");
		_trackPlayer[i].setLoop(true);
		_trackPlayer[i].setVolume(1.0);
	}

	//FX
	for (int i = 0; i < cFXNum; i++)
	{
		isAllSuccess &= _fxPlayer[i].load(folder + "/fx_" + ofToString(i + 1) + ".wav");
		_fxPlayer[i].setLoop(false);
		_fxPlayer[i].setMultiPlay(false);
	}

	//BGM
	isAllSuccess &= _bgm.load(folder + "/bgm.wav");
	_bgm.setLoop(true);

	_isLoad = isAllSuccess;

}

//---------------------------------------------
void audioSet::play()
{
	if (!_isLoad)
	{
		return;
	}

	_bgm.play();
	for (int i = 0; i < cTrackNum; i++)
	{
		_trackPlayer[i].setVolume(0.0);
		_trackPlayer[i].play();
	}
	ZeroMemory(_fxCheck, cFXNum);
	ofRegisterKeyEvents(this);
}

//---------------------------------------------
void audioSet::stop()
{
	if (!_isLoad)
	{
		return;
	}
	ofUnregisterKeyEvents(this);

	_bgm.stop();
	//Track
	for (int i = 0; i < cTrackNum; i++)
	{
		_fxPlayer[i].stop();
	}

	//FX
	for (int i = 0; i < cFXNum; i++)
	{
		_trackPlayer[i].stop();
	}
}

//---------------------------------------------
void audioSet::keyPressed(ofKeyEventArgs& e)
{
	if (!_isLoad)
	{
		return;
	}

	switch (e.key)
	{
		case 'q':
		{
			onTrack(0);
			break;
		}
		case 'w':
		{
			onTrack(1);
			break;
		}
		case 'e':
		{
			onTrack(2);
			break;
		}
		case 'a':
		{
			playFX(0);
			break;
		}
		case 's':
		{
			playFX(1);
			break;
		}
		case 'd':
		{
			playFX(2);
			break;
		}
	}
}

//---------------------------------------------
void audioSet::keyReleased(ofKeyEventArgs& e)
{
	if (!_isLoad)
	{
		return;
	}

	switch (e.key)
	{
	case 'q':
	{
		offTrack(0);
		break;
	}
	case 'w':
	{
		offTrack(1);
		break;
	}
	case 'e':
	{
		offTrack(2);
		break;
	}
	case 'a':
	{
		releaseFX(0);
		break;
	}
	case 's':
	{
		releaseFX(1);
		break;
	}
	case 'd':
	{
		releaseFX(2);
		break;
	}
	}
}

//---------------------------------------------
bool audioSet::isTrackOn(int index)
{
	if (index >= 0 && index < cTrackNum)
	{
		return _trackPlayer[index].getVolume() > 0.0;
	}
	else
	{
		return false;
	}
	
}

//---------------------------------------------
bool audioSet::isFXOn(int index)
{
	if (index >= 0 && index < cFXNum)
	{
		return _fxCheck[index];
	}
	else
	{
		return false;
	}
}

//---------------------------------------------
void audioSet::playFX(int index)
{
	if (index >= 0 && index < cFXNum && !_fxCheck[index])
	{
		_fxPlayer[index].play();
		_fxCheck[index] = true;
	}
}

//---------------------------------------------
void audioSet::releaseFX(int index)
{
	if (index >= 0 && index < cFXNum && _fxCheck[index])
	{
		_fxCheck[index] = false;
	}
}

//---------------------------------------------
void audioSet::onTrack(int index)
{
	if (index >= 0 && index < cTrackNum)
	{
		_trackPlayer[index].setVolume(1.0);
	}
}

//---------------------------------------------
void audioSet::offTrack(int index)
{
	if (index >= 0 && index < cFXNum)
	{
		_trackPlayer[index].setVolume(0.0);
	}
}
