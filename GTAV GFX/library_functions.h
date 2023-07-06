#pragma once

void OpenMessageDialog(const char *text, int buttonType = SCE_MSG_DIALOG_BUTTON_TYPE_OK, int dialogMode = SCE_MSG_DIALOG_MODE_USER_MSG);

extern char sceImeKeyboardRetVal[1000];
void OpenKeyboardDialog(int maxTextLength, const char *title, SceImeType type = SCE_IME_TYPE_DEFAULT, SceImeEnterLabel enterLabel = SCE_IME_ENTER_LABEL_DEFAULT);
