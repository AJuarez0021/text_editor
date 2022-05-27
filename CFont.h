#ifndef __CFONT_H
#define __CFONT_H

#include <windows.h>

class CFont
{
private:
 LOGFONT logfont ;
 HFONT   hFont ;
public:
 void Create_Font(HWND hWnd);
 void Set_Font(HWND hWnd);
 BOOL Choose_Font(HWND hWnd);
 void DestroyFont(){ DeleteObject (hFont); }
};

#endif