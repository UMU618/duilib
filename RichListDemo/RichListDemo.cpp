// RichListDemo.cpp : 定义应用程序的入口点。
//
#include "stdafx.h"

#include "RichListWnd.h"
#include "umu/apppath_t.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /*hPrevInstance*/,
                     LPSTR /*lpCmdLine*/,
                     int nCmdShow) {
  CPaintManagerUI::SetInstance(hInstance);
  CPaintManagerUI::SetResourcePath(umu::apppath::GetProductDirectory() +
                                   _T("_skin"));
  CPaintManagerUI::SetResourceZip(_T("RichListRes.zip"));

  HRESULT hr = ::CoInitialize(NULL);
  if (FAILED(hr)) {
    return hr;
  }

  CRichListWnd* pFrame = new CRichListWnd();
  if (pFrame == nullptr) {
    return ERROR_NOT_ENOUGH_MEMORY;
  }
  pFrame->Create(nullptr, _T("DuiLib Demo from mbstudio.cn / meineson"),
                 UI_WNDSTYLE_FRAME, 0L, 0, 0, 500, 400);
  pFrame->CenterWindow();
  ::ShowWindow(*pFrame, SW_SHOW);

  int result = CPaintManagerUI::MessageLoop();
  ::CoUninitialize();
  return result;
}
