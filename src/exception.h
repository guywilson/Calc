#include "types.h"

#ifndef _INCL_EXCEPTION
#define _INCL_EXCEPTION

#define MESSAGE_BUFFER_SIZE			1024
#define EXCEPTION_BUFFER_SIZE		2048

#define	ERR_MALLOC					0x00000001
#define ERR_INDEX_OUT_OF_RANGE		0x00000002
#define ERR_ARRAY_OVERFLOW			0x00000004
#define ERR_UNMATCHED_PARENTHESIS	0x00000008
#define ERR_INVALID_NUM_ARGUMENTS	0x00000010
#define ERR_RPN_PARSE				0x00000020
#define ERR_INVALID_TOKEN			0x00000040

#define ERR_UNDEFINED				0x0000FFFF

class Exception
{
	private:
		dword		errorCode;
		char		szMessage[MESSAGE_BUFFER_SIZE];
		
		char		szFileName[256];
		char		szClassName[128];
		char		szMethodName[128];
		
		char 		exception[EXCEPTION_BUFFER_SIZE];
		
		dword		lineNumber;
		
		void		_initialise();
		
	public:
					Exception();
					Exception(const char *pszMessage);
					Exception(dword errorCode, const char *pszMessage);
					Exception(
							dword errorCode, 
							const char *pszMessage, 
							const char *pszFileName, 
							const char *pszClassName, 
							const char *pszMethodName, 
							dword lineNumber);
							
		dword		getErrorCode();
		dword		getLineNumber();
		
		char *		getFileName();
		char *		getClassName();
		char *		getMethodName();
		
		char *		getMessage();
		
		char *		getExceptionString();
};

#endif
