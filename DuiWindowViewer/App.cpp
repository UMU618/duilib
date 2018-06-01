#include "App.h"
#include "PreviewWnd.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE /*hPrevInstance*/,
                       LPTSTR lpCmdLine,
                       int nCmdShow) {
  CDuiString* filepath = new CDuiString(lpCmdLine);

  if (filepath->IsEmpty())
    return ShowHelpInfo();
  int n = filepath->ReverseFind('\\') + 1;
  if (filepath->Right(4) != _T(".xml"))
    return ShowHelpInfo();

  HRESULT Hr = ::CoInitialize(NULL);
  if (FAILED(Hr))
    return 0;

  CPreviewWnd* pPreviewForm = new CPreviewWnd();
  if (pPreviewForm == NULL)
    return 0;
  pPreviewForm->SetSkinFile(
      filepath->Right(filepath->GetLength() - n).GetData());
  pPreviewForm->SetSkinFolder(filepath->Left(n).GetData());
  pPreviewForm->Create(NULL, _T("Ô¤ÀÀ´°¿Ú"), UI_WNDSTYLE_FRAME,
                       WS_EX_WINDOWEDGE);
  pPreviewForm->CenterWindow();
  pPreviewForm->ShowWindow(true);

  CPaintManagerUI::MessageLoop();

  ::CoUninitialize();
  return 0;
}