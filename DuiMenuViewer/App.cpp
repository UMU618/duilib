#include "../DuiWindowViewer/App.h"

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

  CMenuWnd* pPreviewForm = new CMenuWnd();
  if (pPreviewForm == NULL)
    return 0;
  CPaintManagerUI::SetCurrentPath(filepath->Left(n).GetData());
  CDuiPoint point;
  GetCursorPos(&point);
  STRINGorID xml(filepath->GetData());
  pPreviewForm->Init(NULL, xml, _T("xml"), point);

  MSG msg = {0};
  while (::GetMessage(&msg, pPreviewForm->GetHWND(), 0, 0) > 0) {
    if (!CPaintManagerUI::TranslateMessage(&msg)) {
      ::TranslateMessage(&msg);
      ::DispatchMessage(&msg);
    }
  }

  ::CoUninitialize();
  return 0;
}