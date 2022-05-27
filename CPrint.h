#ifndef __CPRINT_H
#define __CPRINT_H

#include <windows.h>

class CPrint
{

 public:
  BOOL PrintFile (HINSTANCE hInst, HWND hWnd, HWND hEdit); //, PTSTR szFileName,UINT uID);

};
#endif