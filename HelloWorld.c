/*
 ============================================================================
 Name        : HelloWorld.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Function Prototypes
 */
static void somefunc(char *p);

/*
 * Main
 */
int main(void ){
	int rc = 0;
	char szErrMsg[1028] = "";
	somefunc(szErrMsg);
	rc = puts(szErrMsg);
	return EXIT_SUCCESS;

}

/*
 * Function definitions
 */
void somefunc(char *pErrBuff){
	int rc = 0;
	char szErrMsg[256] = "";
	char INIGROUP[11] = "AnIniGroup";
	char INIValue[11] = "AnIniValue";

	/*
	 * The following code has potential for buffer overflow as sprintf
	 * does not check arguments to ensure it fits in target buffer.
	 */
	 rc = sprintf(szErrMsg,"\n Invalid INI entry: <%s> <MORTGAGEE=%s>. Format should be MORTGAGEE=;RECIP;MAILER",INIGROUP, INIValue);

	/*
	 * Instead, use snprint and specify buffer size.
	 */
	rc = snprintf(szErrMsg, 256,
			"\n Invalid INI entry: <%s> <MORTGAGEE=%s>. Format should be MORTGAGEE=;RECIP;MAILER",
			INIGROUP, INIValue);


	 /*
	 *  The following code has potential for overflow because strcat doesn't check arguments.
	 */
	 strcat(pErrBuff, szErrMsg);

	/*
	 * 	Instead, use strncat and specify buffer size.
	 * 		Note: strncat arg is the number of free chars left, eg.
	 * 		MAX_BUF_SIZE - 1 - strlen(buf)
	 */
	strncat(pErrBuff, szErrMsg, 256-1-strlen(szErrMsg));

	/*
	 * Alternatively, you can use strcat but you must check buffer size
	 * before performing the operation. Some static code analysis tools
	 * may not catch this check and still report a vulnerability.
	 *
	 */
	 if (strlen(szErrMsg) < 253){
		strcat(pErrBuff, szErrMsg);
	 }
	 return;
}
