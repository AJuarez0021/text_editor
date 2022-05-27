#ifndef __CSEARCH_H
#define __CSEARCH_H

#include <windows.h>
class CSearch
{
 private:
  TCHAR szFindText [256] ;
  TCHAR szReplText [256] ;
 public:
  HWND Find(HWND hWnd);
  HWND Replace(HWND hWnd);
  BOOL Find_Text (HWND hEdit, int *iSearchOffset, LPFINDREPLACE lpfr);
  BOOL FindNextText (HWND hEdit, int *iSearchOffset);
  BOOL Replace_Text (HWND hEdit, int *iSearchOffset, LPFINDREPLACE lpfr);
  BOOL FindValidFind (void){
     return * szFindText != '\0' ;
  }

};

#endif