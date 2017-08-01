#include "sender.h"

//--------------------------------------------------------------
void sender::addServer(eLightType type, string ip, int port)
{
	if (_udp.find(type) != _udp.end())
	{
		ofLog(OF_LOG_ERROR, "[sender::addServer]Duplicate type");
		return;
	}

	ofxUDPManager newUdp;
	_udp.insert(make_pair(type, newUdp));
	_udp[type].Create();
	_udp[type].Connect(ip.c_str(), port);
	_udp[type].SetNonBlocking(true);
}


//--------------------------------------------------------------
sender* sender::pInstance = 0;
sender* sender::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new sender();
	}
	return pInstance;
}

//--------------------------------------------------------------
void sender::Destroy()
{
	if (pInstance != 0)
	{
		delete pInstance;
	}
}