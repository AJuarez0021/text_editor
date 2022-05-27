#include "CFont.h"

void CFont::Create_Font(HWND hWnd)
{
     GetObject (GetStockObject (SYSTEM_FONT), sizeof (LOGFONT),(PTSTR) &logfont) ;
     hFont = CreateFontIndirect (&logfont) ;
     SendMessage (hWnd, WM_SETFONT, (WPARAM) hFont, 0) ;
}

void CFont::Set_Font(HWND hWnd)
{
     HFONT hFontNew ;
     RECT  rect ;
     
     hFontNew = CreateFontIndirect (&logfont) ;
     SendMessage (hWnd, WM_SETFONT, (WPARAM) hFontNew, 0) ;
     DeleteObject (hFont) ;
     hFont = hFontNew ;
     GetClientRect (hWnd, &rect) ;
     InvalidateRect (hWnd, &rect, TRUE) ;
}

BOOL CFont::Choose_Font(HWND hWnd)
{
     CHOOSEFONT cf ;
     
     cf.lStructSize    = sizeof (CHOOSEFONT) ;
     cf.hwndOwner      = hWnd ;
     cf.hDC            = NULL ;
     cf.lpLogFont      = &logfont ;
     cf.iPointSize     = 0 ;
     cf.Flags          = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS ;
     cf.rgbColors      = 0 ;
     cf.lCustData      = 0 ;
     cf.lpfnHook       = NULL ;
     cf.lpTemplateName = NULL ;
     cf.hInstance      = NULL ;
     cf.lpszStyle      = NULL ;
     cf.nFontType      = 0 ;              
     cf.nSizeMin       = 0 ;
     cf.nSizeMax       = 0 ;
     
     return ChooseFont (&cf) ;
}