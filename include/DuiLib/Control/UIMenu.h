#ifndef __UIMENU_H__
#define __UIMENU_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "Utils/observer_impl_base.hpp"

namespace DuiLib {

/////////////////////////////////////////////////////////////////////////////////////
//
struct ContextMenuParam {
  // 1: remove all
  // 2: remove the sub menu
  // 3: UMU
  WPARAM wParam;
  HWND hWnd;
};

enum MenuAlignment {
  // UMU
  eMenuAlignment_Left = 0,
  eMenuAlignment_Top = 0,
  eMenuAlignment_Right = 1 << 1,
  eMenuAlignment_Bottom = 1 << 2,
};

typedef class ObserverImpl<BOOL, ContextMenuParam> ContextMenuObserver;
typedef class ReceiverImpl<BOOL, ContextMenuParam> ContextMenuReceiver;

extern ContextMenuObserver s_context_menu_observer;

// MenuUI
extern const TCHAR* const kMenuUIClassName;      // = _T("MenuUI");
extern const TCHAR* const kMenuUIInterfaceName;  // = _T("Menu");

class CListUI;
class DUILIB_API CMenuUI : public CListUI {
 public:
  CMenuUI();
  ~CMenuUI();

  LPCTSTR GetClass() const;
  LPVOID GetInterface(LPCTSTR pstrName);

  // UMU: 菜单循环选择，即选择项是最后项时，按 DOWN 键，选择项变成第一项……
  virtual int FindSelectable(int iIndex, bool bForward = true) const;

  virtual void DoEvent(TEventUI& event);

  virtual bool Add(CControlUI* pControl);
  virtual bool AddAt(CControlUI* pControl, int iIndex);

  virtual int GetItemIndex(CControlUI* pControl) const;
  virtual bool SetItemIndex(CControlUI* pControl, int iIndex);
  virtual bool Remove(CControlUI* pControl, bool bDoNotDestroy = false);

  SIZE EstimateSize(SIZE szAvailable);

  void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
};

/////////////////////////////////////////////////////////////////////////////////////
//

// MenuElementUI
extern const TCHAR* const kMenuElementUIClassName;      // = _T("MenuElement");
extern const TCHAR* const kMenuElementUIInterfaceName;  // = _T("MenuElement);

typedef void (*DELETER)(void* mem);

class CMenuElementUI;
class DUILIB_API CMenuWnd : public CWindowWnd, public ContextMenuReceiver {
 public:
  CMenuWnd(HWND hParent = NULL, DELETER deleter = nullptr);
  void Init(CMenuElementUI* pOwner,
            STRINGorID xml,
            LPCTSTR pSkinType,
            POINT point);
  LPCTSTR GetWindowClassName() const;
  void OnFinalMessage(HWND hWnd);

  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

  BOOL Receive(ContextMenuParam param);

 public:
  HWND m_hParent;
  POINT m_BasedPoint;
  STRINGorID m_xml;
  CDuiString m_sType;
  CPaintManagerUI m_pm;
  CMenuElementUI* m_pOwner;
  CMenuUI* m_pLayout;

  // UMU
 private:
  DELETER deleter_;
  int menu_alignment_;
};

class CListContainerElementUI;
class DUILIB_API CMenuElementUI : public CListContainerElementUI {
  friend CMenuWnd;

 public:
  CMenuElementUI();
  ~CMenuElementUI();

  LPCTSTR GetClass() const;
  LPVOID GetInterface(LPCTSTR pstrName);

  bool DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);

  void DrawItemText(HDC hDC, const RECT& rcItem);

  SIZE EstimateSize(SIZE szAvailable);

  bool Activate();

  void DoEvent(TEventUI& event);

  CMenuWnd* GetMenuWnd();

  void CreateMenuWnd();

 protected:
  CMenuWnd* m_pWindow;
};

}  // namespace DuiLib

#endif  // __UIMENU_H__
