#pragma once

int ShowHelpInfo() {
  MessageBox(nullptr,
             _T("�����������ļ�(*.xml)\r\n��\"Esc\"����\"Alt+F4\"�˳���"),
             _T("����Ԥ������"), MB_OK);
  return 0;
}