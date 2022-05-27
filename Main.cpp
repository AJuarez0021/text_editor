//Txt To Pdf
//Es un editor de texto que permite
//Guardar el documento en .txt o en .pdf
//Programa compilado con Visual C++ 6.0
//http://www.programacioncpp.irandohosting.0lx.net
 
//Txt To Pdf utilza la libreria PDFLIB que se puede descargar desde 
//http://www.pdflib.com/
#pragma warning(disable:4098)

#include "CEdit.h"
#include "CWnd.h"
#include "CToolBar.h"
#include "CFont.h"
#include "CStatusBar.h"
#include "CSearch.h"
#include "resource.h"
#include "CPrint.h"
#include "hyperlink.h"
#include "HTMLHELP\htmlhelp.h"


const char szClassName[] = "ClaseVentana";
CToolBar tb;
CEdit e;
CWnd wnd;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#pragma comment(lib,"comctl32.lib")
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hWnd;
	MSG Msg;



	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = 0;
	wc.lpfnWndProc	 = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MAINMENU);
	wc.lpszClassName = szClassName;
	wc.hIconSm		 = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)); 

	if(!RegisterClassEx(&wc))
	{
		wnd.ShowError(NULL,"Error al registrar la ventana");
		return 0;
	}

	hWnd = CreateWindowEx(
		0,
		szClassName,
		TEXT("Txt To Pdf"),
		WS_OVERLAPPEDWINDOW ,
		GetSystemMetrics(SM_CXSCREEN)/4, GetSystemMetrics(SM_CYSCREEN)/4,
        CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	if(hWnd == NULL){	
		wnd.ShowError(NULL,"Error al crear la ventana");
		return 0;
	}

	wnd.SetHWND(hWnd);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	UnregisterClass(szClassName,hInstance);
	return Msg.wParam;
}

void CheckButtonTB(HWND hTB,HWND hWndEdit,UINT uID)
{
 
 int iSelect = SendMessage (hWndEdit, EM_GETSEL, 0, 0) ;             
 if (HIWORD (iSelect) == LOWORD (iSelect))
   SendMessage(hTB,TB_ENABLEBUTTON,uID,MAKELONG(FALSE, 0));	   
 else
   SendMessage(hTB,TB_ENABLEBUTTON,uID,MAKELONG(TRUE, 0));

}

VOID CALLBACK TimerProcClip(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
 CheckButtonTB(tb.GetHWNDToolBar(),e.GetHWNDEdit(),ID_EDIT_CUT);
 CheckButtonTB(tb.GetHWNDToolBar(),e.GetHWNDEdit(),ID_EDIT_COPY);

}

VOID CALLBACK TimerProcClip2(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
 if(SendMessage (e.GetHWNDEdit(), EM_CANUNDO, 0, 0) )
   SendMessage(tb.GetHWNDToolBar(),TB_ENABLEBUTTON,ID_EDIT_UNDO,MAKELONG(TRUE, 0));
 else
   SendMessage(tb.GetHWNDToolBar(),TB_ENABLEBUTTON,ID_EDIT_UNDO,MAKELONG(FALSE, 0));

 if(IsClipboardFormatAvailable (CF_TEXT))
   SendMessage(tb.GetHWNDToolBar(),TB_ENABLEBUTTON,ID_EDIT_PASTE,MAKELONG(TRUE, 0));
 else
   SendMessage(tb.GetHWNDToolBar(),TB_ENABLEBUTTON,ID_EDIT_PASTE,MAKELONG(FALSE, 0));
}



BOOL DoNotify(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#define lpnm   ((LPNMHDR)lParam)
#define lpnmTB ((LPNMTOOLBAR)lParam)

   RECT      rc;
   TPMPARAMS tpm;
   HMENU     hPopupMenu = NULL;
   HMENU     hMenuLoaded;
   BOOL      bRet = FALSE;

   switch(lpnm->code){
      case TBN_DROPDOWN:
         SendMessage(lpnmTB->hdr.hwndFrom, TB_GETRECT,(WPARAM)lpnmTB->iItem, (LPARAM)&rc);
         MapWindowPoints(lpnmTB->hdr.hwndFrom,HWND_DESKTOP, (LPPOINT)&rc, 2);                         
         tpm.cbSize = sizeof(TPMPARAMS);
         tpm.rcExclude = rc;
		 
         hMenuLoaded = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_POPUP)); 
         hPopupMenu = GetSubMenu(LoadMenu(GetModuleHandle(NULL),MAKEINTRESOURCE(IDR_POPUP)),0);

         TrackPopupMenuEx(hPopupMenu,TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,               
            rc.left, rc.bottom, wnd.GetHWND(), &tpm); 

		
         DestroyMenu(hMenuLoaded);			
      return (FALSE);
   }
   return FALSE;
}




BOOL CALLBACK AboutProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
 HYPCTRL hc; 
 switch(msg)
 {

  case WM_INITDIALOG:  
	    InitHypCtrl(&hc);
		hc.ulStyle	 = ulHover;
		hc.szLink	 = TEXT("http://www.programacioncpp.irandohosting.0lx.net");
		hc.szTooltip = TEXT("Visitar Pagina Web");
		CreateHypCtrl(hWnd, &hc,18, 120, 0, 0);

       break;
  case WM_CLOSE:
       EndDialog(hWnd,0);                      
       break;
  case WM_COMMAND:
       switch(LOWORD(wParam)){
          case IDC_ABOUT_OK:
               EndDialog(hWnd,0);  
               break;
      }
      break;
      case WM_DESTROY:        
           return TRUE;
      default:
           return FALSE;
  }
 return DefWindowProc(hWnd, msg, wParam, lParam);
}
static HWND hDlgModeless;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static CStatusBar sb;	
	static CFont f;
	static CSearch s;
    static bOpen=false;    
	static int       iOffset ; 
	static UINT      messageFindReplace ;
    CPrint p;
    LPFINDREPLACE    pfr ;

	switch(msg)
	{
		
		case WM_CREATE:
		{
														
		    RECT r;
		    GetClientRect(hwnd,&r);	
			int Stat[] = {r.right, -1};
			e.CreateEdit(hwnd,IDC_MAIN_EDIT);
			tb.CreateToolBar(hwnd,IDC_MAIN_TOOL);			
			tb.AddButton(ID_FILE_NEW,STD_FILENEW,NULL);
			tb.AddButton(ID_FILE_OPEN,STD_FILEOPEN,NULL);					            
			tb.AddButtonExt(ID_POPUP_PDF,STD_FILESAVE,NULL); 
			tb.AddSeparator();
			tb.AddButton(ID_EDIT_CUT,STD_CUT,NULL);
			tb.AddButton(ID_EDIT_COPY,STD_COPY,NULL);	
			tb.AddButton(ID_EDIT_PASTE,STD_PASTE,NULL);
			tb.AddSeparator();
			tb.AddButton(ID_SEARCH_FIND,STD_FIND,NULL);
			tb.AddButton(ID_SEARCH_REPLACE,STD_REPLACE,NULL);
			tb.AddButton(ID_FILE_PRINT,STD_PRINT,NULL);
			tb.AddSeparator();
	        tb.AddButton(ID_EDIT_UNDO,STD_UNDO,NULL);
			tb.AddButton(ID_FILE_HELP,STD_HELP,NULL);
			sb.CreateStatusBar(hwnd,IDC_MAIN_STATUS);			   
			sb.SetParts(Stat);     
			SetTimer(hwnd,1,10,TimerProcClip);
			SetTimer(hwnd,2,10,TimerProcClip2);						
			f.Create_Font(e.GetHWNDEdit());		
			messageFindReplace = RegisterWindowMessage (FINDMSGSTRING) ;
			
		}		
		break;	
	
		case WM_INITMENUPOPUP:
          if (lParam == 1)
          {
			   int iEnable;
               EnableMenuItem ((HMENU) wParam, ID_EDIT_UNDO,
                    SendMessage (e.GetHWNDEdit(), EM_CANUNDO, 0, 0) ?
                                   MF_ENABLED : MF_GRAYED) ;
               
               EnableMenuItem ((HMENU) wParam, ID_EDIT_PASTE,
                    IsClipboardFormatAvailable (CF_TEXT) ?
                                   MF_ENABLED : MF_GRAYED) ;
               
               int iSelect = SendMessage (e.GetHWNDEdit(), EM_GETSEL, 0, 0) ;
               
               if (HIWORD (iSelect) == LOWORD (iSelect))
                    iEnable = MF_GRAYED ;			   
               else
                    iEnable = MF_ENABLED ;

			   
               
               EnableMenuItem ((HMENU) wParam, ID_EDIT_CUT,   iEnable) ;
               EnableMenuItem ((HMENU) wParam, ID_EDIT_COPY,  iEnable) ;
               EnableMenuItem ((HMENU) wParam, ID_EDIT_DELETE, iEnable) ;

			   EnableMenuItem ((HMENU) wParam, ID_SEARCH_FIND,    iEnable) ;
               EnableMenuItem ((HMENU) wParam, ID_SEARCH_NEXT,    iEnable) ;
               EnableMenuItem ((HMENU) wParam, ID_SEARCH_REPLACE, iEnable) ;

			 
               return 0 ;
          }
          break ;

		case WM_SIZE:
		{
			
			int iEditHeight;
			RECT rcClient;		
			tb.AutoSize();		            
			sb.AutoSize();			
			GetClientRect(hwnd, &rcClient);
			iEditHeight = rcClient.bottom - tb.GetHeight() - sb.GetHeight();			
			SetWindowPos(e.GetHWNDEdit(), NULL, 0, tb.GetHeight(), rcClient.right, iEditHeight, SWP_NOZORDER);
			int Stat[] = {rcClient.right, -1};
			sb.SetParts(Stat);     
		
		}
		break;
	
		case WM_CLOSE:
			tb.DestroyToolBar();
			sb.DestroyStatusBar();
			e.DestroyEdit();
			f.DestroyFont();
			DestroyWindow(hwnd);
		break;
		case WM_DESTROY:
			KillTimer(hwnd,1);
			KillTimer(hwnd,2);
			DeleteFile("c:\\temp.txt");
			PostQuitMessage(0);
		break;
		case WM_NOTIFY: 
		  DoNotify(hwnd,msg,wParam,lParam);
          switch (((LPNMHDR) lParam)->code) 
		  {  
               case TTN_GETDISPINFO: 
			{ 
               LPTOOLTIPTEXT lpttt; 
			   lpttt = (LPTOOLTIPTEXT) lParam; 
			   lpttt->hinst = GetModuleHandle(NULL); 
			   switch(lpttt->hdr.idFrom){			    
			     case ID_FILE_PRINT:
					  lpttt->lpszText=TEXT("Imprimir");
					  break;
			     case ID_SEARCH_FIND:
					  lpttt->lpszText=TEXT("Buscar");
					  break;
				 case ID_SEARCH_REPLACE:
					  lpttt->lpszText=TEXT("Reemplazar");
					  break;
			     case ID_FILE_NEW:                    
					  lpttt->lpszText=TEXT("Nuevo archivo de texto");
					  break;
                 case ID_FILE_OPEN:
					  lpttt->lpszText=TEXT("Abre un archivo de texto");
					  break;
				 case ID_FILE_SAVEAS:
					  lpttt->lpszText=TEXT("Guardar");
					  break;
				 case ID_EDIT_CUT:
					  lpttt->lpszText=TEXT("Cortar");
					  break;
				 case ID_EDIT_COPY:
					  lpttt->lpszText=TEXT("Copiar");
					  break;
				 case ID_EDIT_PASTE:
					  lpttt->lpszText=TEXT("Pegar");
					  break;
				 case ID_EDIT_UNDO:
					  lpttt->lpszText=TEXT("Deshacer");
					  break;
				 case ID_FILE_HELP:
					  lpttt->lpszText=TEXT("Ayuda");
					  break;
			   }
			   break;
			}
		  }
        break;
		case WM_SETFOCUS:
             SetFocus (e.GetHWNDEdit()) ;			 
             return 0 ;

		
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			    case IDC_HELP_CONTENT:
					{
					 HWND hResult=NULL;
                     hResult=HtmlHelp(hwnd,"txt_to_pdf.chm",HH_DISPLAY_INDEX,NULL);
					 if(hResult == NULL)
					  wnd.ShowError(hwnd,TEXT("Error la ayuda no existe"));
					
					}
					 break;
			    case ID_FILE_PRINT:		
                     if(!p.PrintFile((HINSTANCE)GetModuleHandle(NULL),hwnd,e.GetHWNDEdit()))
                      wnd.ShowError(hwnd,"Error al imprimir");
					 break;
			    case ID_SEARCH_FIND:								
					 SendMessage (e.GetHWNDEdit(), EM_GETSEL, 0, (LPARAM) &iOffset) ;
					 hDlgModeless = s.Find(hwnd);			
					 
					return 0;
				case ID_SEARCH_NEXT:
				
					 SendMessage (e.GetHWNDEdit(), EM_GETSEL, 0, (LPARAM) &iOffset) ;	
					 if(s.FindValidFind())
					  s.FindNextText(e.GetHWNDEdit(),&iOffset);
					 else
					  hDlgModeless = s.Find(hwnd);
					 return 0;

			   case ID_SEARCH_REPLACE:
                     SendMessage (e.GetHWNDEdit(), EM_GETSEL, 0, (LPARAM) &iOffset) ;
                     hDlgModeless = s.Replace(hwnd) ;
                     return 0 ;

			    case IDC_HELP_ABOUT:
					 DialogBox((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, (DLGPROC)AboutProc);
					 break;
			    case ID_POPUP_PDF:					
					 SendMessage(hwnd,WM_COMMAND,ID_FILE_PDF,0);
					 break;
				case ID_POPUP_TXT:					 
					 SendMessage(hwnd,WM_COMMAND,ID_FILE_TXT,0);
					 break;
			    case ID_FORMAT_FONT:	 								
					 if (f.Choose_Font (hwnd))
                      f.Set_Font (e.GetHWNDEdit()) ;               
				
                     return 0 ;
				case ID_FILE_EXIT:
					 PostMessage(hwnd, WM_CLOSE, 0, 0);
				     break;
				case ID_EDIT_UNDO:
					 SendMessage (e.GetHWNDEdit(), WM_UNDO, 0, 0) ;			
					 break;
                case ID_EDIT_CUT:
					 SendMessage(e.GetHWNDEdit(),WM_CUT,0,0);
					 break;
				case ID_EDIT_COPY:
					 SendMessage(e.GetHWNDEdit(),WM_COPY,0,0);
					 break;
				case ID_EDIT_PASTE:
					 SendMessage(e.GetHWNDEdit(),WM_PASTE,0,0);
					 break;
				case ID_EDIT_SELECTALL:
					 SendMessage(e.GetHWNDEdit(),EM_SETSEL,0,-1);					 
					 return 0;
				case ID_EDIT_DELETE:			
                     SendMessage (e.GetHWNDEdit(), WM_CLEAR, 0, 0) ;
                     return 0 ;
				case ID_FILE_NEW:					
					 e.SetText("");		
					 sb.SetText("");
				     break;
				case ID_FILE_OPEN:
					 if(wnd.Open("Archivo TXT *.txt\0*.txt\0", "Abrir archivo")){
					  e.ShowFile(wnd.GetFileNameIn());							
					  sb.SetText(wnd.GetFileNameIn());
					  bOpen=true;
					 }
					 else
					  bOpen=false;
				     break;
				case ID_FILE_TXT:
					 if(wnd.Save("Archivo TXT *.txt\0*.txt\0","Guardar Archivo","txt")){					  
					  wnd.SaveToTxt(e.GetHWNDEdit(),wnd.GetFileNameOut());
					  sb.SetText(wnd.GetFileNameOut());
					 }
					 break;
				case ID_FILE_PDF:
					{
					 DWORD dwLength=e.GetTextLength();
					 if(dwLength > 0){
                      if(wnd.Save("Archivo PDF *.pdf\0*.pdf\0","Guardar Archivo","pdf")){					  
					   wnd.SaveToTxt(e.GetHWNDEdit(),"c:\\temp.txt");
					   wnd.ConverterToPdf("c:\\temp.txt",wnd.GetFileNameOut());
					   sb.SetText(wnd.GetFileNameOut());
					  }
					 }
					 else{
					  if(bOpen){
                       if(wnd.Save("Archivo PDF *.pdf\0*.pdf\0","Guardar Archivo","pdf")){					  
					    wnd.ConverterToPdf(wnd.GetFileNameIn(),wnd.GetFileNameOut());
					    sb.SetText(wnd.GetFileNameOut());
					   }
					  }
					  else{
                       if(wnd.Save("Archivo PDF *.pdf\0*.pdf\0","Guardar Archivo","pdf")){					  
					    wnd.SaveToTxt(e.GetHWNDEdit(),"c:\\temp.txt");
					    wnd.ConverterToPdf("c:\\temp.txt",wnd.GetFileNameOut());
					    sb.SetText(wnd.GetFileNameOut());
					   }
					  }
					 }	
					}
					 break;
			
			}
		break;
		default:
			if (msg == messageFindReplace)
          {
               pfr = (LPFINDREPLACE) lParam ;
               
               if (pfr->Flags & FR_DIALOGTERM)
                    hDlgModeless = NULL ;
               
               if (pfr->Flags & FR_FINDNEXT)
                    if (!s.Find_Text (e.GetHWNDEdit(), &iOffset, pfr))
                         MessageBox(hwnd, TEXT ("Texto no encontrado"), TEXT ("Txt To Pdf"),MB_OK) ;
                                          
                    
               if (pfr->Flags & FR_REPLACE || pfr->Flags & FR_REPLACEALL)
                    if (!s.Replace_Text (e.GetHWNDEdit(), &iOffset, pfr))
                         MessageBox (hwnd, TEXT ("Text no encontrado"),TEXT ("Txt to Pdf"),MB_OK) ; 
                                          
                         
               if (pfr->Flags & FR_REPLACEALL)
                    while (s.Replace_Text(e.GetHWNDEdit(), &iOffset, pfr)) ;
                              
              
			   return 0;
          }
			return DefWindowProc(hwnd, msg, wParam, lParam);;
            break;
			
	}
	return 0;
}



