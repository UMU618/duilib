#pragma once

int ShowHelpInfo() {
  MessageBox(nullptr,
             _T("参数：界面文件(*.xml)\r\n按\"Esc\"或者\"Alt+F4\"退出。"),
             _T("界面预览工具"), MB_OK);
  return 0;
}