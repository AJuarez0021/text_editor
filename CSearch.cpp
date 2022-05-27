
#include "CSearch.h"
#include <tchar.h>   

HWND CSearch::Find(HWND hWnd)
{
 static FINDREPLACE fr ;       
     
 fr.lStructSize      = sizeof (FINDREPLACE) ;
 fr.hwndOwner        = hWnd ;
 fr.hInstance        = NULL ;
 fr.Flags            = FR_HIDEUPDOWN | FR_HIDEMATCHCASE | FR_HIDEWHOLEWORD ;
 fr.lpstrFindWhat    = szFindText ;
 fr.lpstrReplaceWith = NULL ;
 fr.wFindWhatLen     = 256;
 fr.wReplaceWithLen  = 0 ;
 fr.lCustData        = 0 ;
 fr.lpfnHook         = NULL ;
 fr.lpTemplateName   = NULL ;     
 return FindText (&fr) ;
}

HWND CSearch::Replace(HWND hWnd)
{
 static FINDREPLACE fr ;     
 fr.lStructSize      = sizeof (FINDREPLACE) ;
 fr.hwndOwner        = hWnd ;
 fr.hInstance        = NULL ;
 fr.Flags            = FR_HIDEUPDOWN | FR_HIDEMATCHCASE | FR_HIDEWHOLEWORD ;
 fr.lpstrFindWhat    = szFindText ;
 fr.lpstrReplaceWith = szReplText ;
 fr.wFindWhatLen     = 256 ;
 fr.wReplaceWithLen  = 256 ;
 fr.lCustData        = 0 ;
 fr.lpfnHook         = NULL ;
 fr.lpTemplateName   = NULL ;     
 return ReplaceText (&fr) ;
}


BOOL CSearch::Find_Text (HWND hEdit, int *iSearchOffset, LPFINDREPLACE lpfr)
{
     int    iLength, iPos ;
     PTSTR  pstrDoc, pstrPos ;
            
     
     iLength = GetWindowTextLength (hEdit) ;
     
     if (NULL == (pstrDoc = (PTSTR) malloc ((iLength + 1) * sizeof (TCHAR))))
          return FALSE ;
     
     GetWindowText (hEdit, pstrDoc, iLength + 1) ;              
     pstrPos = _tcsstr (pstrDoc + * iSearchOffset, lpfr->lpstrFindWhat) ;
     free (pstrDoc) ;
     
        
     
     if (pstrPos == NULL)
          return FALSE ;
     
      
     
     iPos = pstrPos - pstrDoc ;
     *iSearchOffset = iPos + lstrlen (lpfr->lpstrFindWhat) ;
     
         
     SetFocus(hEdit);
     SendMessage (hEdit, EM_SETSEL, iPos, * iSearchOffset) ;
     SendMessage (hEdit, EM_SCROLLCARET, 0, 0) ;     
     return TRUE ;
}

BOOL CSearch::FindNextText (HWND hEdit, int *iSearchOffset)
{
     FINDREPLACE fr ;     
     fr.lpstrFindWhat = szFindText ;     
     return Find_Text (hEdit, iSearchOffset, &fr) ;
}

BOOL CSearch::Replace_Text (HWND hEdit, int *iSearchOffset, LPFINDREPLACE lpfr)
{
               
     if (!Find_Text (hEdit, iSearchOffset, lpfr))
          return FALSE ;
     
        
	 SetFocus(hEdit);
     SendMessage (hEdit, EM_REPLACESEL, 0, (LPARAM) lpfr->lpstrReplaceWith) ;     
     return TRUE ;
}
