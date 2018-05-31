#ifndef __UIBUTTON_H__
#define __UIBUTTON_H__

#pragma once

namespace DuiLib
{
	class DUILIB_API CButtonUI : public CLabelUI
	{
	public:
		CButtonUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;

		bool Activate();
		void SetEnabled(bool bEnable = true);
		void DoEvent(TEventUI& event);

		LPCTSTR GetNormalImage();
		void SetNormalImage(LPCTSTR pStrImage);
		LPCTSTR GetHotImage();
		void SetHotImage(LPCTSTR pStrImage);
		LPCTSTR GetPushedImage();
		void SetPushedImage(LPCTSTR pStrImage);
		LPCTSTR GetFocusedImage();
		void SetFocusedImage(LPCTSTR pStrImage);
		LPCTSTR GetDisabledImage();
		void SetDisabledImage(LPCTSTR pStrImage);
		LPCTSTR GetForeImage();
		void SetForeImage(LPCTSTR pStrImage);
		LPCTSTR GetHotForeImage();
		void SetHotForeImage(LPCTSTR pStrImage);

		// 对应按钮的5个状态图
		void SetFiveStatusImage(LPCTSTR pStrImage);
		void SetFadeAlphaDelta(BYTE uDelta);
		BYTE GetFadeAlphaDelta();

		void SetHotBkColor(DWORD dwColor);
		DWORD GetHotBkColor() const;
		void SetHotTextColor(DWORD dwColor);
		DWORD GetHotTextColor() const;
		void SetPushedTextColor(DWORD dwColor);
		DWORD GetPushedTextColor() const;
		void SetFocusedTextColor(DWORD dwColor);
		DWORD GetFocusedTextColor() const;
		SIZE EstimateSize(SIZE szAvailable);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void PaintText(HDC hDC);
    // UMU
    void PaintBkColor(HDC hDC);
		void PaintStatusImage(HDC hDC);

    // UMU {
    void SetPushedBkColor(COLORREF color);
    COLORREF GetPushedBkColor() const;
    void SetHotBorderColor(COLORREF color);
    COLORREF GetHotBorderColor() const;
    void SetPushedBorderColor(COLORREF color);
    COLORREF GetPushedBorderColor() const;
    void SetDisabledBorderColor(COLORREF color);
    COLORREF GetDisabledBorderColor() const;

    void PaintBorder(HDC hDC);

    void SetHotFont(int font);
    int GetHotFont() const;
    void SetPushedFont(int font);
    int GetPushedFont() const;
    // UMU }

	protected:
		enum
		{ 
			FADE_TIMERID = 11,
			FADE_ELLAPSE = 30,
		};

		UINT m_uButtonState;

		DWORD m_dwHotBkColor;
		DWORD m_dwHotTextColor;
		DWORD m_dwPushedTextColor;
		DWORD m_dwFocusedTextColor;
		BYTE m_uFadeAlpha;
		BYTE m_uFadeAlphaDelta;

		TDrawInfo m_diNormal;
		TDrawInfo m_diHot;
		TDrawInfo m_diHotFore;
		TDrawInfo m_diPushed;
		TDrawInfo m_diPushedFore;
		TDrawInfo m_diFocused;
		TDrawInfo m_diDisabled;

    // UMU
    COLORREF pushed_bk_color_;

    COLORREF hot_border_color_;
    COLORREF pushed_border_color_;
    COLORREF disabled_border_color_;

    int hot_font_;     // UMU: 热点字体
    int pushed_font_;  // UMU: 按下字体
	};

}	// namespace DuiLib

#endif // __UIBUTTON_H__