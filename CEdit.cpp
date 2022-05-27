#include "CEdit.h"

void CEdit::SetText(LPCTSTR strText)
{
 SetWindowText(hEdit,strText);
}

void CEdit::DestroyEdit()
{
 DestroyWindow(hEdit);
}


bool CEdit::CreateEdit(HWND hWnd,UINT nIDMenu)
{
 hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, 
	                    "EDIT", "", 
		                WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 
				        0, 0, 100, 100, 
						hWnd, 
						(HMENU)nIDMenu, 
						GetModuleHandle(NULL), 
						NULL);
 if(hEdit == NULL)
  return false;

 return true;
}

bool CEdit::ShowFile(LPCTSTR pszFileName)
{
	HANDLE hFile;
	bool bSuccess = false;

	hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(hFile != INVALID_HANDLE_VALUE){
		DWORD dwFileSize;
		dwFileSize = GetFileSize(hFile, NULL);
		if(dwFileSize != 0xFFFFFFFF){
			LPSTR pszFileText;
			pszFileText =(char*) GlobalAlloc(GPTR, dwFileSize + 1);
			if(pszFileText != NULL){
				DWORD dwRead;
				if(ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL)){
					pszFileText[dwFileSize] = 0; 
					if(SetWindowText(hEdit, pszFileText))
						bSuccess = true; 
				}
				GlobalFree(pszFileText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}