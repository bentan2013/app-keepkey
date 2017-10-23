#include "StdAfx.h"
#include "Str_DES.h"

CStr_DES::CStr_DES(void)
{
	memset(m_ckey, 0, 8);
}

CStr_DES::~CStr_DES(void)
{
}

bool CStr_DES::SetKey(const char *ckey, int len)
{
	memcpy(m_ckey, ckey, 8);
	return true;
}

CString CStr_DES::Encode(CString strInput)
{
	int length = strInput.GetLength();
	WCHAR *wTest = new WCHAR[length + 1];
	memset(wTest, 0, sizeof(WCHAR) * (length + 1));
	memcpy(wTest, strInput.GetBuffer(), length * sizeof(WCHAR));
	WCHAR *wOutput = NULL;
	CodeByDES(wTest, length, wOutput, true);
	CString strOutput = wOutput;

	DELETE_OBJECT(wTest);
	DELETE_OBJECT(wOutput);
	return strOutput;

}
	
CString CStr_DES::Decode(CString strInput)
{
	int length = strInput.GetLength();
	CString strLen;
	WCHAR *wTest = new WCHAR[length];
	memset(wTest, 0, sizeof(WCHAR) * (length));
	memcpy(wTest, strInput.GetBuffer(), length * sizeof(WCHAR));

	WCHAR *wJieMiHou = NULL;
	CodeByDES(wTest, length ,wJieMiHou, false);

	CString reslut = wJieMiHou;
	DELETE_OBJECT(wJieMiHou);
	DELETE_OBJECT(wTest);
	return reslut;
}

void CStr_DES::CodeByDES(WCHAR *input, int nInputLength, WCHAR* &output, bool bIsJiami)
{
	char inbuff[8],oubuff[8],skey[8];
	memset(inbuff, 0, 8);
	int nOutputLength = ((nInputLength + 3)/4) * 4;
	output = new WCHAR[nOutputLength + 1];
	memset(output, 0, (nOutputLength + 1) * sizeof(WCHAR));

	memset(skey, 0, 8);
	memcpy(skey, m_ckey, 8);

	int nRound = 0;

	nInputLength *= 2;

	if (bIsJiami)
	{
		nRound = nInputLength /8;
		int n = 0;
		int nleft = nInputLength % 8;

		if (nleft != 0)
		{
			nRound ++;
		}

		while(n < nRound)
		{
			memset(inbuff, 0, 8);
			memcpy(inbuff, input + n * 4, 8);
			m_des.NDes_Go(oubuff, inbuff, sizeof(inbuff), skey, sizeof(skey), 0);
			memcpy(output + n * 4, oubuff, 8);
			n ++;
		}
	}
	else
	{
		if(nInputLength % 8 > 0)
		{
			CString strLen;
			strLen.Format(L"%d", nInputLength);
			AfxMessageBox(strLen);
			AfxMessageBox(L"无效的加密数据!");
			return;
		}
		nRound = nInputLength / 8;
		for (int i=0; i< nRound; i++)
		{
			memcpy(inbuff, input + i * 4, 8);
			m_des.NDes_Go(oubuff, inbuff, sizeof(oubuff), skey, sizeof(skey), 1);
			memcpy(output + i * 4, oubuff, 8);
		}
	}
}