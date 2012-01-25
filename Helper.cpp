#include "Helper.h"

#ifdef _WIN32
#include <windows.h>

// GetUTF16 from ASCII
std::basic_string <Uint16> Helper::GetUTF16( const char* msg ) {
	int len = strlen(msg);
	wchar_t * res = new wchar_t[len + 1];
	int reslen = MultiByteToWideChar(CP_ACP, 0, msg, len, res, len+1);
	res[reslen] = 0;
	std::basic_string <Uint16> str((Uint16*)res);
	delete(res);
	return str;
}
#else
// GetUTF16 from UTF8
std::basic_string <Uint16> Helper::GetUTF16( const char* msg ) {
	std::basic_string <Uint16> str;
	char mask[7] = {0x7F, 0x00, 0x1F, 0x0F, 0x07, 0x03, 0x01};
	Uint16 unicode;
	for (int len; msg != NULL && *msg != 0; ) {
	  len = 0;
	  for (int i = 7; i >= 0; --i, ++len)
	    if (((1 << i) & *msg) == 0) break;
	  
	  unicode = 0;
	  unicode = (*msg) & mask[len];
	  for (int i = 1; i < len; ++i) 
	    unicode = (unicode << 6) | (*(++msg) & 0x3F);
	  
	  str += unicode;
	  ++msg;
	}
	
	return str;
}

#endif



