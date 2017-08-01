#pragma once


struct LFlash
{
	LFlash()
		:length(8)
		,id(0)
		,type('t')
		,time(1000)
		, enable1(true)
		, enable2(true)
		, enable3(true)
		, enable4(true)
	{}

	unsigned char length;
	unsigned char id;
	unsigned char type;
	unsigned short time;
	bool enable1;
	bool enable2;
	bool enable3;
	bool enable4;
};

struct LPointRandom
{
	LPointRandom()
		:length(4)
		, id(1)
		, type('t')
		, time(1000)
	{}

	unsigned char length;
	unsigned char id;
	unsigned char type;
	unsigned short time;
};

struct LLineRandom
{
	LLineRandom()
		:length(4)
		, id(2)
		, type('t')
		, time(1000)
	{}

	unsigned char length;
	unsigned char id;
	unsigned char type;
	unsigned short time;
};

struct LRunLine
{
	 char length;
	 char id;
	 char type;
	 short time;
	 char runType;//0~4
};

struct LOpen
{
	LOpen()
		:length(4)
		, id(4)
		, type('t')
		, time(1000)
	{}
	unsigned char length;
	unsigned char id;
	unsigned char type;
	unsigned short time;
};

struct LRunLineCenter
{
	LRunLineCenter()
		: length(4)
		, id(5)
		, type('t')
		, time(1000)
		, runType(0)
	{}

	unsigned char length;
	unsigned char id;
	unsigned char type;
	unsigned short time;
	unsigned char runType;//0~4
};