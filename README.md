# Txt To Pdf

A lightweight text editor for Windows that allows you to write or open plain text files and export them as PDF documents. Built with pure Win32 API in C++.

## Features

- **Text editing** — full-featured editor with cut, copy, paste, undo, and select all
- **File operations** — create new documents, open `.txt` files, and save as `.txt` or `.pdf`
- **PDF export** — converts text content to A4-format PDF using the PDFLib library
- **Find & Replace** — search for text and replace occurrences within the document
- **Font selection** — choose any system font for the editing area
- **Print support** — print documents directly from the application
- **Toolbar** — quick-access buttons for the most common actions with tooltips
- **Status bar** — displays the current file path

## Project Structure

| File | Description |
|------|-------------|
| `Main.cpp` | Application entry point, window procedure, and message loop |
| `CEdit.h / .cpp` | Wrapper around the Win32 Edit control |
| `CWnd.h / .cpp` | Main window helpers: open/save dialogs, TXT export, PDF conversion |
| `CFont.h / .cpp` | Font selection dialog and font management |
| `CSearch.h / .cpp` | Find and Replace dialog logic |
| `CStatusBar.h / .cpp` | Status bar creation and management |
| `CToolBar.h / .cpp` | Toolbar creation and button management |
| `CPrint.h / .cpp` | Print dialog and document printing |
| `resource.rc` | Menu, dialog, and icon resources |

## Dependencies

- **PDFLib** — used for PDF generation (`PDFLIB\pdflib.h`). Download from [pdflib.com](http://www.pdflib.com/).
- **HtmlHelp API** — used to display the `.chm` help file (`txt_to_pdf.chm`).
- **Hyperlink control** — custom hyperlink control (`hyperlink.h` / `hyperlink.lib`) used in the About dialog.
- **comctl32.lib** — Windows Common Controls (toolbar, status bar).

## Build Requirements

- **Compiler:** Visual C++ 6.0 (project files: `TxtToPdf.dsp` / `TxtToPdf.dsw`)
- **Platform:** Windows (Win32)

To build, open `TxtToPdf.dsw` in Visual C++ 6.0 and build the solution. Make sure the PDFLib headers and library are placed under the `PDFLIB\` directory relative to the project root.

## Usage

1. Launch the application.
2. Type text directly in the editor, or open an existing `.txt` file via **File > Open**.
3. Save the document:
   - As plain text: **File > Save as TXT**
   - As PDF: **File > Save as PDF** (uses the PDFLib library to generate an A4 PDF)
4. Use **Edit > Find / Replace** or the toolbar buttons to search within the document.
5. Use **Format > Font** to change the editor font.
6. Use **File > Print** to print the current document.

## Notes

- PDF conversion writes a temporary file to `C:\temp.txt` during the export process, which is deleted on exit.
- PDF pages use the Times-Roman font at 9pt with A4 dimensions. Text automatically continues on a new page when the current one is full.
