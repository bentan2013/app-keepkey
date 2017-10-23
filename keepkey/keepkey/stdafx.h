
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

//加入ADO支持库
#ifndef INPORT_ADO_SUPPORT
#define INPORT_ADO_SUPPORT
	#import "c:\program files\common files\system\ado\msado15.dll" \
		no_namespace rename ("EOF", "adoEOF")  
#endif
//加入宏
#include "CommonMacro.h"

//String
#include <iostream>


class StrConvTools
{
public:
	static CString M2U(const char* pszMulByte)
	{
		int iLen = MultiByteToWideChar(CP_OEMCP, 0, pszMulByte, -1, 0, 0);
		wchar_t *wp = new wchar_t[iLen];
		memset(wp, 0, iLen);
		MultiByteToWideChar(CP_OEMCP, 0, pszMulByte, -1, wp, iLen);

		CString strRet(wp);
		if(wp)
		{
			delete wp;
			wp = NULL;
		}

		return strRet;
	}

	static std::string U2M(LPCWSTR strUnicode)
	{
		int iLen = WideCharToMultiByte(CP_OEMCP, NULL, strUnicode, -1, NULL, 0, NULL, FALSE);

		char* pszRet = new char[iLen];
		memset(pszRet, 0, iLen);
		WideCharToMultiByte(CP_OEMCP, NULL, strUnicode, -1, pszRet, iLen, NULL, FALSE);

		std::string str(pszRet);
		if (pszRet != NULL)
		{
			delete pszRet;
			pszRet = NULL;
		}
		return str;
	}

	/**宽字符转窄字符*/
	static std::string ws2s(std::wstring &ws)
	{
		std::string curLocale = setlocale(LC_ALL, NULL);
		setlocale(LC_ALL, "chs");
		const wchar_t* _Source = ws.c_str();
		size_t _Dsize = 2 * ws.size() + 1;
		char * _Dest = new char[_Dsize];
		memset(_Dest, 0, _Dsize);
		wcstombs(_Dest, _Source, _Dsize);
		std::string result = _Dest;
		delete []_Dest;
		setlocale(LC_ALL, curLocale.c_str());
		return result;
	}

	/**窄字符转宽字符*/
	static std::wstring s2ws(std::string &s)
	{
		setlocale(LC_ALL, "chs");
		const char* _Source = s.c_str();
		size_t _Dsize = s.size() + 1;
		wchar_t* _Dest = new wchar_t[_Dsize];
		wmemset(_Dest, 0 , _Dsize);
		mbstowcs(_Dest, _Source, _Dsize);
		std::wstring result = _Dest;
		delete []_Dest;
		setlocale(LC_ALL, "C");
		return result;
	}

};



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


