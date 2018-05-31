#pragma once


namespace DuiLib
{
    class DUILIB_API CIconUI : public CControlUI
    {
    public:
        CIconUI();
        ~CIconUI();

        LPCTSTR GetClass() const;
        LPVOID GetInterface(LPCTSTR pstrName);

        virtual void PaintStatusImage(HDC hDC);
        virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

        void SetIcon(HICON icon);

        bool IsCenterImage() const;
        void SetCenterImage(bool center_image);

        bool IsDefaultSize() const;
        void SetDefaultSize(bool default_size);

        bool IsStretch() const;
        void SetStretch(bool stretch);

    protected:
        HICON icon_;
        bool center_image_;
        bool default_size_;
        bool stretch_;
    };
}
