// App.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "ScrCaptureWnd.h"

#include <atlbase.h>
#include <atlstr.h>

#include "umu/apppath_t.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE /*hPrevInstance*/,
                       LPTSTR /*lpCmdLine*/,
                       int nCmdShow) {
  CPaintManagerUI::SetInstance(hInstance);
  //CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
  CPaintManagerUI::SetResourcePath(umu::apppath::GetProductDirectory() +
                                   _T("_skin\\ScrCapture"));

  HRESULT Hr = ::CoInitialize(NULL);
  if (FAILED(Hr))
    return 0;

  CScrCaptureWnd* pFrame = CScrCaptureWnd::Instance();
  if (pFrame == NULL)
    return 0;
  pFrame->Create(NULL, _T(""), WS_VISIBLE | WS_POPUP,
                 /*WS_EX_TOOLWINDOW|WS_EX_TOPMOST*/ 0);
  pFrame->ShowWindow(true);
  CPaintManagerUI::MessageLoop();

  ::CoUninitialize();
  return 0;
}
