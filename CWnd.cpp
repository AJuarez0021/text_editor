#include "CWnd.h"
#include "PDFLIB\pdflib.h"
#include <fstream>
#include <string>

using namespace std;

bool CWnd::Open(LPSTR lpszFilter, LPSTR lpszTitle)
{
	static OPENFILENAME  ofn;   
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFilter = (lpszFilter);
	ofn.lpstrFile = szBufferIn;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = (lpszTitle);
	ofn.Flags = OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY;
	if(!GetOpenFileName (&ofn))
	 return false;

	return true;
}


bool CWnd::Save(LPSTR lpszFilter, LPSTR lpszTitle,LPSTR lpszExt)
{
	static OPENFILENAME  ofn;   
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFilter = (lpszFilter);
	ofn.lpstrFile = szBufferOut;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = (lpszTitle);
	ofn.Flags = OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY;
	ofn.lpstrDefExt = TEXT(lpszExt);
	if(!GetSaveFileName (&ofn))
	 return false;

	return true;
}


void CWnd::ShowError(HWND hWnd,LPCTSTR strMessage)
{
 MessageBox(hWnd,strMessage,"Txt To Pdf",MB_ICONERROR|MB_OK);
 
}


bool CWnd::ConverterToPdf(LPCSTR szFileNameIn,LPSTR szFileNameOut)
{
 PDF *pPDF;
 int font;
 ifstream in(szFileNameIn);
 string strLine;


 if(in.fail())
  return false;

 if ((pPDF = PDF_new()) == (PDF *) 0){
   return false;
 }

  PDF_TRY(pPDF) {
	if (PDF_begin_document(pPDF, szFileNameOut, 0, "") == -1) {	
	    return false;
	}


	PDF_set_parameter(pPDF, "hypertextencoding", "host");
	PDF_set_info(pPDF, "Creator", "TxtToPdf");
	PDF_set_info(pPDF, "Author", "Abel Juarez");
	PDF_set_info(pPDF, "Title", "");    	
	int y=800;
	int x=50;
	PDF_begin_page_ext(pPDF, a4_width, a4_height, "");
	font = PDF_load_font(pPDF, "Times-Roman", 0, "host", "");
	PDF_setfont(pPDF, font, 9);
    while(!in.eof()){	 
     getline(in,strLine);
	 PDF_show_xy(pPDF,strLine.c_str(),x,y);
     y-=10;
	 if(y==100){
       PDF_end_page_ext(pPDF, "");
       PDF_begin_page_ext(pPDF, a4_width, a4_height, "");
	   font = PDF_load_font(pPDF, "Times-Roman", 0, "host", "");
	   PDF_setfont(pPDF, font, 9);
	   x=50;
	   y=800;
	 }	       
	}	    
	PDF_end_page_ext(pPDF, "");
	PDF_end_document(pPDF, "");
  }
  PDF_CATCH(pPDF) {        
        PDF_delete(pPDF);
        return false;
  }

  PDF_delete(pPDF);
  in.close();
  return true;
}



bool CWnd::SaveToTxt(HWND hEdit, LPCTSTR pszFileNameOut)
{
     HANDLE hFile;

	 hFile = CreateFile(pszFileNameOut, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	 if(hFile != INVALID_HANDLE_VALUE){
		DWORD dwTextLength;
		dwTextLength = GetWindowTextLength(hEdit);	
		if(dwTextLength > 0){
			LPSTR pszText;
			DWORD dwBufferSize = dwTextLength + 1;
            DWORD dwWritten;
			pszText = (char*)GlobalAlloc(GPTR, dwBufferSize);
			if(pszText != NULL){
				if(GetWindowText(hEdit, pszText, dwBufferSize)){
					
					if(!WriteFile(hFile, pszText, dwTextLength, &dwWritten, NULL))
					 return false;			
				}
				GlobalFree(pszText);
			}
		}
		CloseHandle(hFile);
	 }
  
 
  return true;
}
