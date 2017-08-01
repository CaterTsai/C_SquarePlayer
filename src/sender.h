#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

#define STA '\x01'
#define END '\x02'
#define SENDER_MAX 30

enum eLightType : int
{
	eFrontLeftS = 0
	,eFrontRightS
	,eMiddleLeftM
	,eMiddleRightM
	,eBackLeftS
	,eBackCenerL
	,eBackRightS
};

class sender
{
public:
	void addServer(eLightType type, string ip, int port);

	template<typename T>
	void send(eLightType type, T data);

	template<typename T>
	void sendAll(T data);
	
private:
	map<eLightType, ofxUDPManager> _udp;

//-------------------
//Singleton
//-------------------
private:
	sender() {};
	~sender()
	{
		sender::Destroy();
	}
	sender(sender const&);
	void operator=(sender const&);


public:
	static sender* GetInstance();
	static void Destroy();

private:
	static sender *pInstance;
};

template<typename T>
inline void sender::send(eLightType type, T data)
{
	auto iter = _udp.find(type);
	if (iter == _udp.end())
	{
		return;
	}

	char msg[SENDER_MAX] = { 0 };
	msg[0] = STA;
	int length = data.length;
	memcpy(msg + 1, &data, sizeof(T));
	msg[length + 2] = END;
	//iter->second.Send(msg, SENDER_MAX);
};

template<typename T>
inline void sender::sendAll(T data)
{
	if (_udp.size() == 0)
	{
		return;
	}

	char msg[SENDER_MAX] = { 0 };
	msg[0] = STA;
	int length = data.length;
	memcpy(msg + 1, &data, data.length + 1);
	msg[length + 2] = END;

	for (auto& iter : _udp)
	{
		iter.second.Send(msg, SENDER_MAX);
	}
};
