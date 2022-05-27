#ifndef __CTOOLBAR_H
#define __CTOOLBAR_H

#include <windows.h>
#include <commctrl.h>

class CToolBar
{

private:
	HWND m_hToolBar;
	TBBUTTON tbb;
    RECT rcTool;
public:
     CToolBar(){ 
	  INITCOMMONCONTROLSEX iccx;
	  iccx.dwSize=sizeof(INITCOMMONCONTROLSEX);
      iccx.dwICC=ICC_BAR_CLASSES;
      InitCommonControlsEx(&iccx);
	  m_hToolBar=NULL;
	 }
	~CToolBar(){ 
	}
	bool CreateToolBar(HWND hWnd,UINT uIDMenu);
	void AddButton(int nID,int iBitmap,const char *Text);
	void AddButtonExt(int nID,int iBitmap,const char *Text);
	void AddSeparator();
	void DestroyToolBar(){ DestroyWindow(m_hToolBar); }
    void Enable(BOOL bEnable,UINT uID);
	void AutoSize();
	int GetHeight();
	HWND GetHWNDToolBar(){ return m_hToolBar; }
};
#endif