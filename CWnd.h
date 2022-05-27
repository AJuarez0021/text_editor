#ifndef __CWND_H
#define __CWND_H

#include <windows.h>
class CWnd
{
private:
 HWND m_hWnd;
 char *szBufferIn;
 char *szBufferOut;
public :
 CWnd(){ 
  m_hWnd=NULL; 
  szBufferIn=new char[MAX_PATH];
  szBufferOut=new char[MAX_PATH];
  memset(szBufferIn,0,MAX_PATH);
  memset(szBufferOut,0,MAX_PATH);
 }
 ~CWnd(){
  if(szBufferIn!=0)
   delete [] szBufferIn;

  if(szBufferOut!=0)
   delete [] szBufferOut;
 }
 void SetHWND(HWND hWnd){ m_hWnd=hWnd; }
 HWND GetHWND() { return m_hWnd; } 
 bool Save(LPSTR lpszFilter, LPSTR lpszTitle,LPSTR lpszExt);
 bool Open(LPSTR lpszFilter, LPSTR lpszTitle);
 char *GetFileNameIn(){ return szBufferIn;   }
 char *GetFileNameOut(){ return szBufferOut; };
 bool ConverterToPdf(LPCSTR szFileNameIn,LPSTR szFileNameOut);
 bool SaveToTxt(HWND hEdit, LPCTSTR pszFileNameOut);
 void ShowError(HWND hWnd,LPCTSTR strMessage);
};

#endif