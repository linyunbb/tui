// Tools.h: interface for the CTools class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLS_H__EC500B4C_7545_4A36_B546_1DD02C819657__INCLUDED_)
#define AFX_TOOLS_H__EC500B4C_7545_4A36_B546_1DD02C819657__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mmsystem.h"
#define		ENCRYPT		0
#define		DESCRYPT	1
#define     PINLEN      9   

#define		_GO_DEBUG	0

struct ErrInfo
{
	int code;
	CString info;
};

const unsigned char auchCRCLo[] =
{
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
	0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
	0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
	0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
	0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};
const unsigned char auchCRCHi[] =
{
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
	0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
	0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
	0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
	0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
	0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
	0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
	0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
	0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
	0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
	0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
	0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
	0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
	0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
	0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
	0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
	0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
	0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
	0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
	0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
	0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
	0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};


/* 
Description:
	s->CString	 ch->char	 p->point	 uch->unsigned char
	in->input	out->output		back->return
	First letter small,and follow large,such as pUch

Notes:
1.The difference between "char" and "unsigned char" is the 
meaning in value.0x80->char means -128,0x80->unsigned char
means 128, so if assign it to a int(value) that the int means
what the value means
2.assigned "int" to char|unsigned char, first get the int's last
8 bit,such as int temp=0x7f(0x0000007f) -> 0x7f
			  int temp=-0x7f(0xffffff81) -> 0x81 
then with Note.1 get the exact value
*/

#define _VERSION_FUNS 1 
/*
Use extended funs:
	Use GetVersionInfo must include "version.lib"
*/
#define _SYNTHESIZE_FUNS 1
/*
 *	Use SynthesizeKeyInput(...) should inlude "winable.h"
 */

class CTools  
{
public:
	int TriDes(LPVOID input, LPVOID doublekey, LPVOID output);
	int Undes(LPVOID pin, LPVOID workkey, LPVOID cipher_pin);
	int Des(LPVOID pin, LPVOID workkey, LPVOID cipher_pin);

	void calCrc16(LPVOID ptr, unsigned char len, LPVOID crc);

	bool BcdToAsc(LPVOID charasc, LPVOID charbcd, int bcdlen);
	bool AscToBcd(LPVOID charbcd, LPVOID charasc, int bcdlen);
	long StringToInt(CString str, unsigned int base);
	int TranslateInputToHex(CString sIn, LPVOID pUchOut);
	CString ShowHex(const LPVOID ToBeConverted,int ConvertLen,CString interval="");
	void TimeStringConvert(CTime *pTime, unsigned char *Bcd,BOOL toTime);
	
	void SetBit(char &chByte, int iBits, bool bValue);
	bool IsSet(char chByte, int iBits);

	CArchive* GetArchive(CString filename,BOOL bSave=true, BOOL bContinue = true);
	int LoadErrorCodes(CString filename);
	CString GetErrorInfo(int errcode);
	void ReadIniData(CString filename,CString section, CString key,CString *string, int *value = NULL);
	CString RelativeToAbsolutePath(CString originPath);
	BOOL WriteInitData(CString filename,CString section,CString key,CString string);
public:
	CString InsertLineReturn(CString src,int nCount);
	inline bool IsNum(char ch){
		if((ch>='0')&&(ch<='9'))
			return true;
		return false;
	}
	inline bool Isch(char ch){
		if((ch>='a')&&(ch<='z'))
			return true;
		return false;
	}
	inline bool IsCh(char ch){
		if((ch>='A')&&(ch<='Z'))
			return true;
		return false;
	}
	inline CString GetRunPath(){
		CString exename=AfxGetApp()->m_pszHelpFilePath;
		return (exename.Left(exename.ReverseFind('\\')+1));
	}
	CTools();
	virtual ~CTools();
private:
	void compress(unsigned char* in, unsigned char* out);
	void encrypt(unsigned char* block, int edflag);
	void setkey(unsigned char* key);
	void expand(unsigned char* in, unsigned char* out);

private:
	LARGE_INTEGER m_nTimeCount;
	LARGE_INTEGER m_nTimeFrenquence;
	unsigned char	KS[16][48];
    unsigned char	E[64];
	int nErrInfoCount;
	CArchive *pArchive;
	CFile *pFileInfo;
public:
	bool ElapsedTime(double *Time);
	bool StartTimeCount();
	bool m_bStartTimeCount;

	int m_iLastErrorCode;
	int GetLastErrorCode(CString *pInfo = NULL );
	void CloseArchive();
	ErrInfo* pErrInfo;
//Error Info:
public:
	void GetDirFiles(CString dirPath, CStringArray& files);
	BOOL CreateDir(CString dirPath);
	BOOL IsDirExist(CString dirPath);
	BOOL DelInitData(CString filename, CString section, BOOL bSection, CString key);
	void SendWndData(HWND hwnd, PVOID data, int len);
	bool CtrlKeyDown();
	static const int errFileNotMatch ;
	static const int errFileOpenFailed ;
	static const int errParamErr ;
	static const int errMemErr ;
	static const int errNotStartCount;
	static const int errNotIncludeLibOrH;

	static const int verFileVersion;
	static const int verComments;
	static const int verPrivateBuild;
	static const int verCompanyName;

};

#endif // !defined(AFX_TOOLS_H__EC500B4C_7545_4A36_B546_1DD02C819657__INCLUDED_)