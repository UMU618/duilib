#include "StdAfx.h"

namespace DuiLib {
CIconUI::CIconUI()
    : icon_(nullptr),
      center_image_(false),
      default_size_(false),
      stretch_(false) {}

CIconUI::~CIconUI() {
  if (nullptr != icon_) {
    ::DestroyIcon(icon_);
    icon_ = nullptr;
  }
}

LPCTSTR CIconUI::GetClass() const {
  return _T("IconUI");
}

LPVOID CIconUI::GetInterface(LPCTSTR pstrName) {
  if (_tcscmp(pstrName, _T("Icon")) == 0) {
    return static_cast<CIconUI*>(this);
  }
  return CControlUI::GetInterface(pstrName);
}

void CIconUI::PaintStatusImage(HDC hDC) {
  CControlUI::PaintStatusImage(hDC);

  if (nullptr == icon_) {
    return;
  }

  int left = GetX();
  int top = GetY();
  int width = 0;
  int height = 0;

  if (stretch_) {
    width = GetWidth();
    height = GetHeight();
  } else {
    if (default_size_) {
      width = ::GetSystemMetrics(SM_CXICON);
      height = ::GetSystemMetrics(SM_CYICON);
    } else {
      ICONINFO ii = {};
      ::GetIconInfo(icon_, &ii);
      width = ii.xHotspot * 2;
      height = ii.yHotspot * 2;
    }
    if (center_image_) {
      if (width > GetWidth()) {
        width = GetWidth();
      } else {
        left += (GetWidth() - width) / 2;
      }
      if (height > GetHeight()) {
        height = GetHeight();
      } else {
        top += (GetHeight() - height) / 2;
      }
    }
  }
  ::DrawIconEx(hDC, left, top, icon_, width, height, 0, nullptr, DI_NORMAL);
}

void CIconUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue) {
  if (_tcscmp(pstrName, _T("centerimage")) == 0) {
    center_image_ = (_tcscmp(pstrValue, _T("true")) == 0);
  } else if (_tcscmp(pstrName, _T("defaultsize")) == 0) {
    default_size_ = (_tcscmp(pstrValue, _T("true")) == 0);
  } else if (_tcscmp(pstrName, _T("stretch")) == 0) {
    stretch_ = (_tcscmp(pstrValue, _T("true")) == 0);
  } else {
    CControlUI::SetAttribute(pstrName, pstrValue);
  }
}

void CIconUI::SetIcon(HICON icon) {
  if (nullptr != icon_) {
    ::DestroyIcon(icon_);
  }
  icon_ = ::CopyIcon(icon);
}

bool CIconUI::IsCenterImage() const {
  return center_image_;
}
void CIconUI::SetCenterImage(bool center_image) {
  center_image_ = center_image;
}

bool CIconUI::IsDefaultSize() const {
  return default_size_;
}
void CIconUI::SetDefaultSize(bool default_size) {
  default_size_ = default_size;
}

bool CIconUI::IsStretch() const {
  return stretch_;
}
void CIconUI::SetStretch(bool stretch) {
  stretch_ = stretch;
}
}  // namespace DuiLib
