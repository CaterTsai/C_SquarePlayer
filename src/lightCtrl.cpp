#include "lightCtrl.h"

//-------------------------------------
void lightCtrl::setType(int type)
{
	_type = type;
	ZeroMemory(_fxCheck, cFXNum);
}

//-------------------------------------
void lightCtrl::enable()
{	
	ofRegisterKeyEvents(this);
}

//-------------------------------------
void lightCtrl::disable()
{
	ofUnregisterKeyEvents(this);
}

//-------------------------------------
void lightCtrl::keyPressed(ofKeyEventArgs & e)
{
	switch (e.key)
	{
		case 'a':
		{
			playEvent(0);
			break;
		}
		case 's':
		{
			playEvent(1);
			break;
		}
		case 'd':
		{
			playEvent(2);
			break;
		}
	}
}

//-------------------------------------
void lightCtrl::keyReleased(ofKeyEventArgs & e)
{
	switch (e.key)
	{
	case 'a':
	{
		releaseEvent(0);
		break;
	}
	case 's':
	{
		releaseEvent(1);
		break;
	}
	case 'd':
	{
		releaseEvent(2);
		break;
	}
	}
}

//-------------------------------------
void lightCtrl::playEvent(int id)
{
	if (_fxCheck[id])
	{
		return;
	}

	if (_type == 0)
	{
		switch (id)
		{
		case 0:
		{
			LRunLine data;
			cout << sizeof(LRunLine) << endl;
			data.runType = 0;
			sender::GetInstance()->send(eFrontLeftS, data);
			break;
		}
		case 1:
		{
			LRunLineCenter data;
			
			data.runType = 1;
			sender::GetInstance()->sendAll(data);
			break;
		}
		case 2:
		{
			LRunLine data;
			data.runType = 2;
			sender::GetInstance()->send(eFrontLeftS, data);
			break;
		}
		}
	}
	else 
	{
		switch (id)
		{
		case 0:
		{
			LRunLine data;
			data.runType = 0;
			sender::GetInstance()->send(eFrontLeftS, data);
			break;
		}
		case 1:
		{
			LRunLineCenter data;
			data.runType = 1;
			sender::GetInstance()->sendAll(data);
			break;
		}
		case 2:
		{
			LRunLine data;
			data.runType = 2;
			sender::GetInstance()->send(eFrontLeftS, data);
			break;
		}
		}
	}
	_fxCheck[id] = true;
}

//-------------------------------------
void lightCtrl::releaseEvent(int id)
{
	if (_fxCheck[id])
	{
		_fxCheck[id] = false;
	}
}
