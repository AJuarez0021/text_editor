#ifndef __CEDIT_H
#define __CEDIT_H

#include <windows.h>

class CEdit
{
private:
 HWND hEdit;
public:
 CEdit(){ hEdit=NULL; }
 ~CEdit(){ }
 bool CreateEdit(HWND hWnd,UINT nIDMenu);
 void DestroyEdit(); 
 HWND GetHWNDEdit(){ return hEdit; }
 bool ShowFile(LPCTSTR strFileName);
 void SetText(LPCTSTR strText);
 DWORD GetTextLength(){
  return GetWindowTextLength(hEdit); 
 }
};

#endif