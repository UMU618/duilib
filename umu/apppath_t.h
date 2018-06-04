#pragma once

namespace umu {
namespace apppath {
inline CString GetProgramPath(HMODULE module_handle = nullptr) {
    CString program_path;

    for (DWORD buffer_size = MAX_PATH; ; buffer_size += MAX_PATH) {
        DWORD size = ::GetModuleFileName(module_handle, program_path.GetBuffer(buffer_size), buffer_size);
        if (0 == size) {
            return _T("");
        }

        if (size < buffer_size) {
            program_path.ReleaseBuffer(size);
            return program_path;
        }

        if (ERROR_INSUFFICIENT_BUFFER != ::GetLastError()) {
            return _T("");
        }
    }
}

// ���ص�·������д� '\'
inline CString GetProgramDirectory(HMODULE module_handle = nullptr) {
    CString program_path(GetProgramPath(module_handle));
    program_path.Truncate(program_path.ReverseFind(_T('\\')) + 1);
    return program_path;
}

inline CString GetProgramBaseName(HMODULE module_handle = nullptr) {
    CString program_path(GetProgramPath(module_handle));
    return program_path.Mid(program_path.ReverseFind(_T('\\')) + 1);
}

inline CString GetProductDirectory(HMODULE module_handle = nullptr) {
    CString path(GetProgramDirectory(module_handle));
    // bin �����ִ�Сд
    LPTSTR found(StrRStrI(path, nullptr, _T("\\bin\\")));
    if (nullptr != found) {
        path.Truncate(static_cast<int>(found - path) + 1);
    } else {
        int backslash_count(0);
        for (int pos = path.GetLength() - 1; pos > 0; --pos) {
            if (_T('\\') == path.GetAt(pos)) {
                path.Truncate(pos + 1);
                if (2 == ++backslash_count) {
                    // �����ڶ��� \\ �ض�
                    break;
                }
            }
        }
    }
    return path;
}
} // end of namespace apppath
} // end of namespace umu
