// Tools.cpp: implementation of the CTools class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tools.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//Error code:
const int CTools::errFileNotMatch	= -0x10;//读文件验证串不对或文件长度为0
const int CTools::errFileOpenFailed = -0x11;//打开文件失败
const int CTools::errParamErr		= -0x12;//输入的参数有错
const int CTools::errMemErr			= -0x13;//内存分配出错
const int CTools::errNotStartCount	= -0x14;//没有开始计时，或不支持
const int CTools::errNotIncludeLibOrH = -0x15;//没有加入相应的库或头文件

//Version Info code:
const int CTools::verFileVersion	= 0x100;//文件版本信息
const int CTools::verComments		= 0x101;//文件注释
const int CTools::verPrivateBuild	= 0x102;//内部编译说明
const int CTools::verCompanyName	= 0x103;//公司名称

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTools::CTools()
{
	pArchive = NULL;
	pFileInfo = NULL;
	pErrInfo = NULL;
	nErrInfoCount = -1;
	m_nTimeCount.QuadPart = 0;
	m_iLastErrorCode = TRUE;
	m_bStartTimeCount = false;
	QueryPerformanceFrequency(&m_nTimeFrenquence);
}

CTools::~CTools()
{
	CloseArchive();
	if(pErrInfo)
		delete[] pErrInfo;
}

/* Transform "charasc"(ASC) to "charbcd"(BCD)
	with "len" of the Bcd Code */
/* 返回成功TRUE,错误FALSE */
bool CTools::AscToBcd(LPVOID charbcd, LPVOID charasc, int bcdlen)
{
	unsigned char *cbuf=NULL, *ubuf=NULL;  
	int lenchar=0, lenover=0;
	int i=0;

	try
	{
		if((charbcd == NULL) || (charasc == NULL) || (bcdlen == 0 ))
		{
			throw errParamErr;
		}
		
		cbuf = new unsigned char[bcdlen*2+1];
		ubuf = new unsigned char[bcdlen+1];
		
		if( (cbuf == NULL) || (ubuf == NULL) )
		{
			throw errMemErr;
		}
	}
	catch (int errCode) 
	{
		m_iLastErrorCode = errCode;
		return FALSE;
	}
	/* If the "lenchar"(len of actual asc) is less than 2*len referred
		,then set the rest buf to '0' */
	memcpy(cbuf, charasc,bcdlen*2);
	cbuf[bcdlen*2] = '\0';
	
    for(i=0; i<(bcdlen*2); i++)
    {
        if ((cbuf[i]>='a')&&(cbuf[i]<='f'))
             cbuf[i]=cbuf[i]-'a'+10;
        else if ((cbuf[i]>='A')&&(cbuf[i]<='F'))
             cbuf[i]=cbuf[i]-'A'+10;
        else if (IsNum(cbuf[i]))
             cbuf[i]-='0';
        else 
		{
			if( i == (bcdlen*2-1) )
				cbuf[i] =0x00;
			else	
				return FALSE;
		}
    }
    for(i=0;i<(bcdlen*2);i+=2)
    	ubuf[i/2]=cbuf[i]*16+cbuf[i+1]%16; 
    
    memcpy(charbcd, ubuf, bcdlen );

	delete[] ubuf;
	delete[] cbuf;
	return TRUE;
}

/* 返回成功TRUE,错误FALSE */
bool CTools::BcdToAsc(LPVOID charasc, LPVOID charbcd, int bcdlen)
{
	int i;
	unsigned char *cbuf, *ubuf;

	if( (charbcd == NULL) || (charasc == NULL) || ( bcdlen == 0 ) )
		return FALSE;

	cbuf = new unsigned char [bcdlen*2+1];
	ubuf = new unsigned char [bcdlen+1];

	if( ( cbuf == NULL ) || ( ubuf == NULL ) )
		return FALSE;

	memcpy(ubuf, (const char*)charbcd, bcdlen);
	for(i=0;i<bcdlen;i++){
		cbuf[2*i] = (ubuf[i] >> 4) ;
		cbuf[2*i+1] = (ubuf[i] & 0x0f) ;     
	} 
	for(i=0;i<bcdlen*2;i++){
		if(cbuf[i] < 10 ) cbuf[i] += '0' ;
		else cbuf[i] += 'A' - 10;
	}	     
	memcpy( charasc, cbuf, bcdlen*2);
	((char*)charasc)[bcdlen*2] = '\0';

	delete[] cbuf;
	delete[] ubuf;
	return TRUE;
}

int CTools::Des(LPVOID pin, LPVOID workkey, LPVOID cipher_pin)
{
	int		i;
	unsigned char	clear_txt[PINLEN],cipher_txt[PINLEN];
    unsigned char	key_block[PINLEN];
    unsigned char	bits[64];

	if( (pin == NULL) || (workkey == NULL) || (cipher_pin == NULL) )
		return FALSE;

	for(i=0;i<8;i++)
		key_block[i]=((PCHAR)workkey)[i];
	
	for (i=0;i<8;i++)
		clear_txt[i] =((PCHAR)pin)[i];
	
	expand(key_block,bits);
	setkey(bits);
	expand(clear_txt,bits);		/* expand to bit stream */
	encrypt(bits,ENCRYPT);		/* encrypt */
	compress(bits,cipher_txt);	/* compress to 8 characters */
	
	memcpy(cipher_pin ,cipher_txt,8);

	return TRUE;
}

int CTools::Undes(LPVOID pin,LPVOID workkey,LPVOID cipher_pin)
{
	int		i;
	unsigned char	clear_txt[PINLEN];
	unsigned char	pin_block[PINLEN];
	unsigned char	key_block[PINLEN];
	unsigned char	bits[64];
	

	if( (pin == NULL) || (workkey == NULL) || (cipher_pin == NULL) )
		return FALSE;

	for(i=0;i<8;i++)
		key_block[i] = ((PCHAR)workkey)[i];
	/* get  pan_block */
	expand(key_block,bits);
	setkey(bits);
	/* set key */
	
	expand((PUCHAR)pin,bits);		/* expand to bit stream */
	encrypt(bits,DESCRYPT);		/* descrypt */
	compress(bits,clear_txt);	/* compress to 8 characters */
	
	for (i=0;i<8;i++)
		pin_block[i] = clear_txt[i];
	memcpy(cipher_pin ,pin_block, 8);
	return TRUE;
}

void CTools::expand(unsigned char *in, unsigned char *out)
{
	int	i,j;

	for (i=0;i<8;i++){
		for (j=0;j<8;j++){
			*out = (in[i] <<j) & 0x80;
			if (*out == 0x80)
				*out = 0x01;
			out++;
			
		}
	}
}

void CTools::setkey(unsigned char *key)
{
	
	// ADD for include
	static	unsigned char	e[] = {
		32, 1, 2, 3, 4, 5,
			4, 5, 6, 7, 8, 9,
			8, 9,10,11,12,13,
			12,13,14,15,16,17,
			16,17,18,19,20,21,
			20,21,22,23,24,25,
			24,25,26,27,28,29,
			28,29,30,31,32, 1,
	};  
	static	unsigned char	C[64];
	static	unsigned char	D[64];
	
	/* Permuted-choice 1 from the key bits
	* to yield C and D.
	* Note that bits 8,16... are left out:
	* They are intended for a parity check.
	*/         
	
	
	// for setkey 
	static	unsigned char	PC1_C[] = {
		57,49,41,33,25,17, 9,
			1,58,50,42,34,26,18,
			10, 2,59,51,43,35,27,
			19,11, 3,60,52,44,36,
	};
	// for setkey
	static	unsigned char	PC1_D[] = {
		63,55,47,39,31,23,15,
			7,62,54,46,38,30,22,
			14, 6,61,53,45,37,29,
			21,13, 5,28,20,12, 4,
	};
	
	/*
	* Sequence of shifts used for the key schedule.
	*/    
	
	//For setkey
	static	unsigned char	shifts[] = {
		1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1,
	};
	
	/*
	* Permuted-choice 2, to pick out the bits from
	* the CD array that generate the key schedule.
	*/   
	
	// for setkey 
	static	unsigned char	PC2_C[] = {
		14,17,11,24, 1, 5,
			3,28,15, 6,21,10,
			23,19,12, 4,26, 8,
			16, 7,27,20,13, 2,
	};
	// for setkey 
	static	unsigned char	PC2_D[] = {
		41,52,31,37,47,55,
			30,40,51,45,33,48,
			44,49,39,56,34,53,
			46,42,50,36,29,32,
	};
	
	
	// END
	register i, j, k;
	int t;
	
	/*
	* First, generate C and D by permuting
	* the key.  The low order bit of each
	* 8-bit unsigned char is not used, so C and D are only 28
	* bits apiece.
	*/
	for (i=0; i<28; i++) {
		C[i] = key[PC1_C[i]-1];
		D[i] = key[PC1_D[i]-1];
	}
	
	/*
	* To generate Ki, rotate C and D according
	* to schedule and pick up a permutation
	* using PC2.
	*/
	for (i=0; i<16; i++) {
	/*
	* rotate.
		*/
		for (k=0; k<shifts[i]; k++) {
			t = C[0];
			for (j=0; j<28-1; j++)
				C[j] = C[j+1];
			C[27] = t;
			t = D[0];
			for (j=0; j<28-1; j++)
				D[j] = D[j+1];
			D[27] = t;
		}
		/*
		* get Ki. Note C and D are concatenated.
		*/
		for (j=0; j<24; j++) {
			KS[i][j] = C[PC2_C[j]-1];
			KS[i][j+24] = D[PC2_D[j]-28-1];
		}
	}
	
	for(i=0;i<48;i++)
		E[i] = e[i];
}

void CTools::encrypt(unsigned char *block, int edflag)
{
	static	unsigned char	IP[] = {
		58,50,42,34,26,18,10, 2,
			60,52,44,36,28,20,12, 4,
			62,54,46,38,30,22,14, 6,
			64,56,48,40,32,24,16, 8,
			57,49,41,33,25,17, 9, 1,
			59,51,43,35,27,19,11, 3,
			61,53,45,37,29,21,13, 5,
			63,55,47,39,31,23,15, 7,
	};
	
	/*
	* Final permutation, FP = IP^(-1)
	*/   
	
	// For encrypt 
	static	unsigned char	FP[] = {
		40, 8,48,16,56,24,64,32,
			39, 7,47,15,55,23,63,31,
			38, 6,46,14,54,22,62,30,
			37, 5,45,13,53,21,61,29,
			36, 4,44,12,52,20,60,28,
			35, 3,43,11,51,19,59,27,
			34, 2,42,10,50,18,58,26,
			33, 1,41, 9,49,17,57,25,
	};
	
	static	unsigned char	S[8][64] = {
		14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7,
			0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8,
			4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0,
			15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13,
			
			15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10,
			3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5,
			0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15,
			13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9,
			
			10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8,
			13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1,
			13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7,
			1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12,
			
			7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15,
			13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9,
			10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4,
			3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14,
			
			2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9,
			14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6,
			4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14,
			11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3,
			
			12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11,
			10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8,
			9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6,
			4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13,
			
			4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1,
			13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6,
			1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2,
			6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12,
			
			13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7,
			1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2,
			7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8,
			2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11,
	};
	
	/*
	* P is a permutation on the selected combination
	* of the current L and key.
	*/
	static	unsigned char	P[] = {
		16, 7,20,21,
			29,12,28,17,
			1,15,23,26,
			5,18,31,10,
			2, 8,24,14,
			32,27, 3, 9,
			19,13,30, 6,
			22,11, 4,25,
	};
	
	/*
	* The current block, divided into 2 halves.
	*/
	static	unsigned  char	L[64], R[64];
	static	unsigned char	tempL[64];
	static	unsigned char	f[64];
	
	/*
	* The combination of the key and the input, before selection.
	*/
	static	unsigned char	preS[64];
	
	/*
	* The payoff: encrypt a block.
	*/
	
	
	// END include
	int i, ii;
	register t, j, k;
	
	/*
	* First, permute the bits in the input
	*/
	for (j=0; j<64; j++)
		L[j] = block[IP[j]-1];
	
	/*============================================== */
	for (j=0;j<32;j++)
		R[j] = L[j+32];
	/*============================================== */
	
	/*
	* Perform an encryption operation 16 times.
	*/
	for (ii=0; ii<16; ii++) {
	/*
	* Set direction
		*/
		if (edflag)
			i = 15-ii;
		else
			i = ii;
			/*
			* Save the R array,
			* which will be the new L.
		*/
		for (j=0; j<32; j++)
			tempL[j] = R[j];
		
			/*
			* Expand R to 48 bits using the E selector;
			* exclusive-or with the current key bits.
		*/
		for (j=0; j<48; j++)
			preS[j] = R[E[j]-1] ^ KS[i][j];
		
			/*
			* The pre-select bits are now considered
			* in 8 groups of 6 bits each.
			* The 8 selection functions map these
			* 6-bit quantities into 4-bit quantities
			* and the results permuted
			* to make an f(R, K).
			* The indexing into the selection functions
			* is peculiar; it could be simplified by
			* rewriting the tables.
		*/
		for (j=0; j<8; j++) {
			t = 6*j;
			k = S[j][(preS[t+0]<<5)+
				(preS[t+1]<<3)+
				(preS[t+2]<<2)+
				(preS[t+3]<<1)+
				(preS[t+4]<<0)+
				(preS[t+5]<<4)];
			t = 4*j;
			f[t+0] = (k>>3)&01;
			f[t+1] = (k>>2)&01;
			f[t+2] = (k>>1)&01;
			f[t+3] = (k>>0)&01;
		}
		
		/*
		* The new R is L ^ f(R, K).
		* The f here has to be permuted first, though.
		*/
		for (j=0; j<32; j++)
			R[j] = L[j] ^ f[P[j]-1];
			/*
			* Finally, the new L (the original R)
			* is copied back.
		*/
		for (j=0; j<32; j++)
			L[j] = tempL[j];
		
	}
	/*
	* The output L and R are reversed.
	*/
	for (j=0; j<32; j++) {
		t = L[j];
		L[j] = R[j];
		R[j] = t;
	}
	
	
	/*============================================== */
	for (j=32;j<64;j++)
		L[j] = R[j-32];
	/*============================================== */
	/*
	* The final output
	* gets the inverse permutation of the very original.
	*/
	for (j=0; j<64; j++)
		block[j] = L[FP[j]-1];

}

void CTools::compress(unsigned char *in, unsigned char *out)
{
	int	temp;
	int	i,j;
	
	for(i=0;i<8;i++){
		out[i] = 0;
		temp = 1;
		for (j=7;j>=0;j--){
			out[i] = out[i] + ( in[i*8+j] * temp);
			temp *= 2;
		}
	}
	
}

int CTools::TriDes(LPVOID input, LPVOID doublekey, LPVOID output)
{
	unsigned char left_key[9];
    unsigned char right_key[9];
    unsigned char tmpstr1[9], tmpstr2[9];
    
    if( (input == NULL) || (doublekey == NULL) || (output == NULL) )
		return FALSE;

	memcpy( left_key, (PCHAR)doublekey, 8 );
    memcpy( right_key, (PCHAR)doublekey+8, 8 );
	
    Des( input, left_key, tmpstr1 );
    Undes( tmpstr1, right_key, tmpstr2 );
    Des( tmpstr2, left_key, output );

	return TRUE;
}

void CTools::SetBit(char &chByte, int iBits, bool bValue)
{
	char chMask;
	chMask=( 0x01<<iBits );
	if( bValue ){
		chByte|=chMask;
	}
	else{
		chByte&=~( chMask );
	}
}

bool CTools::IsSet(char chByte, int iBits)
{
	char chMask;
	chMask=( 0x01<<iBits );
	if( chByte&chMask)
		return true;
	else
		return false;
}

/*
	将str串以十六进制数解释成int型 
	str可以在前头加'-'号，也可以加'0x'标记，转换时自动去掉
	成功返回相应数值，失败返回INT_MAX(最大的整数)
*/
long CTools::StringToInt(CString str, unsigned int base )
{
	int value = -1;
	value = _tcstoul(str,NULL,base);
	if( errno == 34 )
		return INT_MAX;
	if ( value != 0 )
		return value;
	
	for(int i = 0; i< str.GetLength(); i++ )
	{
		if( str[i] != '0' )
			return INT_MAX;
	}
	return 0;
}

/*
	将String以空格分开的串解释为十六进制输入数组 
	成功返回长度,数据在des中,失败(数据格式有错)返回-1长度
*/

int CTools::TranslateInputToHex(CString sIn, LPVOID pUchOut)
{
	int pos=0;
	CString ch="";
	int index=0;
	int temp=0;
	
	sIn.TrimLeft();
	sIn.TrimRight();
	if( sIn.IsEmpty() )
		return 0;
	while(1)
	{
		pos= sIn.Find(' ');
		if( pos == -1 ) //not find ' '
		{	
			
			if( sIn.GetLength() == 0 )
				break;
			
			if( sIn.GetLength() > 2 ){
				return -1;
			}
			ch = sIn;
			temp = StringToInt(ch,16);
			if ( temp == INT_MAX ){
				return -1;
			}
			((unsigned char*)pUchOut)[index++] = temp;
			break;
		}
		else
		{
			ch = sIn.Left( pos );
			sIn = sIn.Mid( pos+1 );
			sIn.TrimLeft();

			if( ch.GetLength() == 0 )
				continue;
			if( ch.GetLength() >3 )
			{
				return -1;
			}
			
			int temp = StringToInt(ch,16);
			if ( temp == INT_MAX )
			{
				return -1;
			}
			((unsigned char*)pUchOut)[index++] = temp;
		}
	}
	return index;
}

/*获得用于Serialize的文档指针,用完可自行Close，但不要delete
bContinue指是否返回上一次的指针，原来用做读(写)的，现在也只能是读(写)，不然忽略*/
CArchive* CTools::GetArchive(CString filename,BOOL bSave, BOOL bContinue)
{
	BOOL ret;
	CFileException fe;
	CString VerifyString="BBQData@TUI";
	CString sVer = "";
	CString fullpath = RelativeToAbsolutePath(filename);
	
	if( pArchive )
	{
#if _GO_DEBUG
		AfxMessageBox("文档:"
			+*pArchive.GetFile()->GetFilePath()
			+"已初始化，释放重新初始化!");
#endif
		if( bContinue )//继续读写
		{
			if( (pArchive->IsStoring()&&bSave)
				||(pArchive->IsLoading()&&!bSave))
				return pArchive;
		}
		//重头读，重新写
		pArchive->Flush();
		pArchive->Close();
		pFileInfo->Close();
		delete pArchive;
		delete pFileInfo;
		pArchive = NULL;
		pFileInfo = NULL;
	}

	//存数据
	pFileInfo = new CFile;
	if( bSave )
	{
		ret=pFileInfo->Open(fullpath,
			CFile::modeCreate|CFile::modeReadWrite|CFile::shareExclusive,
			&fe);
		if( ret == FALSE )
		{
#if _GO_DEBUG
			fe.ReportError();
#endif
			delete pFileInfo;
			pFileInfo = NULL;
			m_iLastErrorCode = errFileOpenFailed;
			return NULL;
		}
		pArchive = new CArchive(pFileInfo,CArchive::store|CArchive::bNoFlushOnDelete);
		//Write current S/W version		
		CString sSWVer;
		sSWVer.Format("%d", g_SWVer);
		VerifyString = VerifyString+"-"+sSWVer;
		*pArchive<<VerifyString;
		pArchive->Flush();
		return pArchive;
	}
	else//读数据
	{
		ret=pFileInfo->Open(fullpath,
			CFile::modeRead|CFile::shareDenyWrite,
			&fe);
		
		if(ret == FALSE )
		{
#if _GO_DEBUG
			fe.ReportError();
#endif
			delete pFileInfo;
			pFileInfo = NULL;
			m_iLastErrorCode = errFileOpenFailed;
			return NULL;
		}
		
		if(pFileInfo->GetLength()!=0)
		{
			pArchive = new CArchive(pFileInfo,CArchive::load|CArchive::bNoFlushOnDelete);			
			CString fileToVerify;
			*pArchive>>fileToVerify;
			int pos = fileToVerify.Find(VerifyString);
			if( pos == -1 )
			{
				m_iLastErrorCode = errFileNotMatch;
				return NULL;
			}
			//Get the Version
			pos = fileToVerify.Find("-");
			if( pos == -1 )
			{
				g_DataVer = 0;
				LogInfo("Upgrade");
			}
			else
			{
				CString sDataVer = fileToVerify.Mid(pos+1);
				g_DataVer = atoi(sDataVer.GetBuffer(100));
			}
			return pArchive;
		}
		else
		{
#if _GO_DEBUG
			AfxMessageBox("文件长度为0");
#endif
			pFileInfo->Close();
			delete pFileInfo;
			pFileInfo = NULL;
			m_iLastErrorCode = errFileNotMatch;
			return NULL;
		}
	}	
}

/* 用于显示十六进制数据,interval指出中间要加入的间隔 */
CString CTools::ShowHex(const LPVOID ToBeConverted,int ConvertLen,CString interval)
{
	CString strResult="";
	CString ch="";
	BYTE value;
	int length;
	if(ConvertLen==0)
		length=strlen((char*)ToBeConverted);
	else
		length=ConvertLen;
	for(int i=0;i<length;i++)
	{
		value=((char*)ToBeConverted)[i];
		ch.Format ("%02x",value);
		if(i!=length-1)
			strResult+=ch+interval;
		else
			strResult+=ch;
		ch="";
	}
	return strResult;
}

/* 载入filename指定的错误列表文件,
	bCurDir指定是否是当前运行的路径即相对路径
	返回记录数，如果为-1表示错误
*/
int CTools::LoadErrorCodes(CString filename)
{
	CString fullpath = RelativeToAbsolutePath(filename);
	
	CFile errfile;
	if( !errfile.Open(filename,CFile::modeRead) ){
#if _GO_DEBUG
		AfxMessageBox("无法打开文件");
#endif
		nErrInfoCount = -1;
		return -1;
	}
	if( errfile.GetLength() == 0 ){
		errfile.Close();
#if _GO_DEBUG
		AfxMessageBox("文件长度为0");
#endif
		nErrInfoCount = -1;
		return -1;
	}
	CArchive ar(&errfile,CArchive::load);

	int count=0;
	CString temp;
	BOOL ret;

	while(1)
	{
		ret = ar.ReadString(temp);
		if( ret == FALSE )
			break;
		count ++;
	}
	if( pErrInfo)
	{
		delete[] pErrInfo;
		pErrInfo = NULL;
	}
	pErrInfo = new ErrInfo[count];
	if( pErrInfo == NULL )
	{
		ar.Close();
		errfile.Close();
#if _GO_DEBUG
		AfxMessageBox("无法分配内存");
#endif
		nErrInfoCount = -1;
		return -1;
	}
	ar.Close();
	errfile.Close();

	errfile.Open(fullpath,CFile::modeRead);
	CArchive ar1(&errfile,CArchive::load);
	
	int index,pos;
	CString left,right;
	int nUseless=0;
	int nUse=0;

	for( int i=0;i<count;i++)
	{
		ar1.ReadString(temp);
		temp.TrimLeft();
		temp.TrimRight();
		if((temp.IsEmpty())
			||(temp[0] == '#'))
		{
			nUseless ++;
			continue;
		}
		pos = temp.Find(' ');
		if( pos == -1 )
		{
			ar1.Close();
			errfile.Close();
			delete[] pErrInfo;
			pErrInfo = NULL;
#if _GO_DEBUG
			AfxMessageBox("格式有错");
#endif
			nErrInfoCount = -1;
			return -1;
		}
		left = temp.Left(pos);
		index = StringToInt(left,16);
		if( index == INT_MAX )
		{
			ar1.Close();
			errfile.Close();
			delete[] pErrInfo;
			pErrInfo = NULL;
#if _GO_DEBUG
			AfxMessageBox("格式有错");
#endif
			nErrInfoCount = -1;
			return -1;
		}
		right = temp.Mid(pos+1);
		right.TrimLeft();
		pErrInfo[nUse].code = index;
		pErrInfo[nUse].info = right;
		nUse++;
	}
	ar1.Close();
	errfile.Close();
	nErrInfoCount = count-nUseless;
	return nErrInfoCount;
}

/*
	由载入的文件中读取相应的错误信息 
	如果没有调用LoadErrorCodes直接使用该函数，
	则该函数自动加载当前运行目录下的errInfo.txt文件
*/
CString CTools::GetErrorInfo(int errcode)
{
	CString output;
	if( nErrInfoCount == -1 )
	{
		LoadErrorCodes(".\\errInfo.txt");
		if( nErrInfoCount == -1 )
		{
			output = "无错误信息可查询!";
			return output;
		}
	}
	for(int i=0;i<nErrInfoCount;i++)
	{
		if( pErrInfo[i].code == errcode )
		{
			output = pErrInfo[i].info;
			break;
		}
	}
	if( i == nErrInfoCount )
	{
		output = "未知错误码";
	}
	return output;
}	

/*计算CRC-16，P(X) = x_16 + x_15 + x_2 +1('_'表示次方)*/
void CTools::calCrc16(LPVOID ptr, unsigned char len, LPVOID crc)
{
	unsigned char uIndex ;
	unsigned char uchCRCHi = 0x0;
	unsigned char uchCRCLo = 0x0;
	unsigned char *pTemp = (PUCHAR)ptr;

	while(len--)
	{
		uIndex = uchCRCLo ^ *pTemp++ ;
		uchCRCLo = uchCRCHi ^ auchCRCLo[uIndex];
		uchCRCHi = auchCRCHi[uIndex] ;
	}
	((PCHAR)crc)[0] = uchCRCHi;
	((PCHAR)crc)[1] = uchCRCLo;
}

/* 
	Time->String: ASC码输出,可用AscToBcd得到Bcd码,Bcd码长度为7
	String->Time: CTime类输出,指定的年必须是[1970,2038]之间
*/
void CTools::TimeStringConvert(CTime *pTime, unsigned char *Bcd,BOOL toTime)
{
	int nYear,nMonth,nDay,nHour,nMinute,nSecond;
	unsigned char tempbuf[20];
	CString temptime;
	if( !toTime ) //Time->String(ASC码)
	{
		//2000-12-31-12-00-00(实际无'-')
		temptime=pTime->Format("%Y%m%d%H%M%S");
		AscToBcd(Bcd,
			(unsigned char*)temptime.GetBuffer(14),
			6);
		temptime.ReleaseBuffer();
	}
	else		//String->Time(如果nYear不在1970-2038年就会出错,pTime = -1)
	{
		//BCD格式如：20 00 12 31 12 00 00(7字节)
		memset(tempbuf,0,20);
		BcdToAsc(tempbuf,Bcd,2);
		nYear = atoi((char*)tempbuf);
		BcdToAsc(tempbuf,Bcd+2,1);
		nMonth = atoi((char*)tempbuf);
		BcdToAsc(tempbuf,Bcd+3,1);
		nDay = atoi((char*)tempbuf);
		BcdToAsc(tempbuf,Bcd+4,1);
		nHour = atoi((char*)tempbuf);
		BcdToAsc(tempbuf,Bcd+5,1);
		nMinute = atoi((char*)tempbuf);
		BcdToAsc(tempbuf,Bcd+6,1);
		nSecond = atoi((char*)tempbuf);
		*pTime = CTime(nYear,nMonth,nDay,nHour,nMinute,nSecond);
	}
}

BOOL CTools::WriteInitData(CString filename,CString section, CString key, CString string)
{
	CString inipath = RelativeToAbsolutePath(filename);
	return WritePrivateProfileString(section,key,string,inipath);
}

CString CTools::RelativeToAbsolutePath(CString originPath)
{
	CString fullpath = originPath;
	CString runPath = GetRunPath();
	if( originPath.Left(2).Compare("..") == 0 )
	{
		runPath = runPath.Left(runPath.ReverseFind('\\'));
		fullpath = runPath+originPath.Mid(3);
	}
	else if( originPath.Left(1).Compare(".") == 0 )
	{
		fullpath = runPath + originPath.Mid(2);
	}
	return fullpath;
}

void CTools::ReadIniData(CString filename,CString section, CString key,CString *string, int *value)
{
	CString fullpath = RelativeToAbsolutePath(filename);
	BOOL ret;
	char buffer[100];
	memset(buffer, 0x20, 100);
	if( value == NULL )
	{
		ret = GetPrivateProfileString(section,key,"",buffer,100,fullpath);
		*string = CString(buffer);
	}
	else
	{
		*value = GetPrivateProfileInt(section,key,0,fullpath);
	}
}

CString CTools::InsertLineReturn(CString src,int nCount)
{
	if( nCount <0 )
		return src;
	int len = src.GetLength();	
	if( len < nCount )
		return src;

	bool bEven = false;
	if( nCount/2*2 == nCount )
		bEven = true;
	//去掉换行符以便重组
	src.Replace("\r\n","");
	
	int offset = 0;
	int asccount =0;
	int i;
	int prepos = 0;
	int curpos = 0;
	while(1)
	{
		curpos = curpos+ nCount;// - offset;

		//计算asc码的个数，奇数并且最后一字节为汉字则向后移一位，
		//防止中间载断汉字
		asccount = 0;
		for( i=prepos; i<curpos;i++)
		{
			if( src[i] > 0 )//<0的为0x80以上的汉字编码
			{
				asccount++;
			}
		}
		if( ((asccount/2*2) != asccount) && (bEven) )
		{
			if( src[i] < 0 )
				offset = 1;
		}
		else
		{
			if(!bEven)
			{
				if( src[i] < 0 )
				offset = 1;
			}
			else
				offset = 0;
		}
		curpos-=offset;//指针向后移一位

		//插入换行符,指针向前移两位
		src.Insert(curpos,"\r\n");
		curpos +=2;
		prepos = curpos;//保存当前的指针用于计算asc的个数
		len-=(nCount-offset+2);
		if( len <nCount )
			return src;
	}
}

void CTools::CloseArchive()
{
	if(pArchive)
	{
		pArchive->Flush();
		pArchive->Close();
		pFileInfo->Close();
		delete pArchive;
		delete pFileInfo;
		pArchive = NULL;
		pFileInfo = NULL;
	}
}

//开始计时，精度为mms
bool CTools::StartTimeCount()
{
	if(QueryPerformanceCounter(&m_nTimeCount))
	{
		m_bStartTimeCount = true;
		return true;
	}

	m_iLastErrorCode = errNotStartCount;
	return false;
}

//结束计时
bool CTools::ElapsedTime(double *Time)
{
	if( !m_bStartTimeCount )
	{
		m_iLastErrorCode = errNotStartCount;
		return false;
	}
	m_bStartTimeCount = false;
	if( Time == NULL )
	{
		m_iLastErrorCode = errParamErr;
		return false;
	}
	
	
	LARGE_INTEGER nStopTime;
	if(!QueryPerformanceCounter(&nStopTime) ||
		(m_nTimeCount.QuadPart == 0 ))
	{
		return false;
	}
	else
	{
		*Time = (double) (nStopTime.QuadPart - m_nTimeCount.QuadPart);
		*Time = (*Time/m_nTimeFrenquence.QuadPart);
		return true;
	}
}
int CTools::GetLastErrorCode(CString *pInfo)
{
	if ( pInfo == NULL )
		return m_iLastErrorCode;

	switch(m_iLastErrorCode) {
	case TRUE:
		*pInfo = "成功";
		break;
	case FALSE:
		*pInfo = "失败";
		break;
	case errFileNotMatch:
		*pInfo = "读存档文件时校验串不符或文件长度为0";
		break;
	case errFileOpenFailed:
		*pInfo = "打开文件失败";
		break;
	case errNotStartCount:
		*pInfo = "没有开始计时，或不支持";
		break;
	case errNotIncludeLibOrH:
		*pInfo = "没有加入相应的库与头文件以支持相应函数";
	default:
		*pInfo = "未知返回";
		break;
	}
	return m_iLastErrorCode;
}

bool CTools::CtrlKeyDown()
{
	BOOL bCtrlKeyDown;
	//Most significant bit means "Key Down"
	SHORT ret=GetAsyncKeyState(VK_CONTROL);	
	bCtrlKeyDown = (ret >>(sizeof(SHORT)*8-1));
	if( bCtrlKeyDown )
		return true;
	else
		return false;
}

//向窗口(可以用FindWindow(NULL,Name)来找到窗口)分送数据:
/*
	接收方：接收WM_COPYDATA，可按如下得到数据
	PCOPYDATASTRUCT m_data;
	m_data = (PCOPYDATASTRUCT)lPrama;
	char *data;
	data = (char*)m_data->lpData;
	int len = (int)m_data->cbData;
	int shortdata= (int)m_data->dwData;
*/
void CTools::SendWndData(HWND hwnd, PVOID data, int len)
{
	COPYDATASTRUCT m_MyData;
	m_MyData.dwData = len; 
	m_MyData.cbData = len;
	m_MyData.lpData = data;

	SendMessage(hwnd,WM_COPYDATA,
						(WPARAM)(HWND) hwnd,
						(LPARAM) (LPVOID) &m_MyData);
	//pWnd->SendMessage(WM_SERVER_MSG);
}


BOOL CTools::DelInitData(CString filename, CString section, BOOL bSection, CString key)
{
	CString inipath = RelativeToAbsolutePath(filename);
	if( bSection )
	{
		return WritePrivateProfileString(section,NULL,NULL,inipath);
	}
	else
	{
		return WritePrivateProfileString(section,key,NULL,inipath);
	}
}

BOOL CTools::IsDirExist(CString dirPath)
{
	CString updateDirPath =dirPath;
	updateDirPath = dirPath.Left(updateDirPath.GetLength()-1);
	WIN32_FIND_DATA wfd;
	BOOL rValue = FALSE;
	HANDLE hFind = FindFirstFile(updateDirPath, &wfd);
    if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {
		rValue = TRUE;
	}
	FindClose(hFind);
	return rValue;
}

BOOL CTools::CreateDir(CString dirPath)
{
	SECURITY_ATTRIBUTES attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength =sizeof(SECURITY_ATTRIBUTES);
	return CreateDirectory(dirPath, &attrib);
}

void CTools::GetDirFiles(CString dirPath, CStringArray &files)
{
	WIN32_FIND_DATA fdata = {0};  
	HANDLE hSearch = FindFirstFile(_T(dirPath+"*.*"),&fdata);
	if(hSearch == INVALID_HANDLE_VALUE)    
		return;
	CString FileName;
	if(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		//Not dir
	}
	else
	{
		FileName.Format("%s\\%s",dirPath,fdata.cFileName);
		files.Add(FileName);
	}
	
	while(FindNextFile(hSearch, &fdata))
	{
		if(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  {
			//Not dir
		}
		else
		{
			FileName.Format("%s\\%s",dirPath,fdata.cFileName);
			files.Add(FileName);
		}
	}
	for(int i=0 ;i<files.GetSize(); i++)
	{
//		AfxMessageBox(files.GetAt(i));
	}

	FindClose(hSearch);
}