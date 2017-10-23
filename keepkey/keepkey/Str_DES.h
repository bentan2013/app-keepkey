#pragma once
#include "des.h"

class CStr_DES
{
public:
	CStr_DES(void);
	~CStr_DES(void);

	bool SetKey(const char *ckey, int len);
	CString Encode(CString strInput);
	CString Decode(CString strInput);

private:
	void CodeByDES(WCHAR *input, int nInputLength, WCHAR* &output, bool bIsJiami);


private:
	DES m_des;
	char m_ckey[8];
};
