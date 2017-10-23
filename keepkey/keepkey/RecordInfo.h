#pragma once

class RecordInfo
{
public:
	RecordInfo(void);
	~RecordInfo(void);
public:
	long m_ID;
	char m_cDescripe[30];
	char m_cCount[30];
	char m_cPassWord[30];
};
