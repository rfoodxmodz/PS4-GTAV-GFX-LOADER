#include "types.h"
#include "imports.h"
#include "utility.h"
#include "library_functions.h"

void OpenMessageDialog(const char *text, int buttonType, int dialogMode) {
	sceMsgDialogInitialize();

	SceMsgDialogParam param;

	memset(&param, 0, sizeof(SceMsgDialogParam));
	memset(&param.baseParam, 0, sizeof(SceCommonDialogBaseParam));

	param.baseParam.magic = (uint32_t)(SCE_COMMON_DIALOG_MAGIC_NUMBER + (uint64_t)&param.baseParam);
	param.baseParam.size = (uint32_t)sizeof(SceCommonDialogBaseParam);
	param.size = sizeof(SceMsgDialogParam);

	param.mode = SCE_MSG_DIALOG_MODE_USER_MSG;

	SceMsgDialogUserMessageParam userMsgParam;
	memset(&userMsgParam, 0, sizeof(userMsgParam));
	userMsgParam.msg = text;
	userMsgParam.buttonType = SCE_MSG_DIALOG_BUTTON_TYPE_OK;
	param.userMsgParam = &userMsgParam;

	sceMsgDialogOpen(&param);

	SceCommonDialogStatus stat;
	while (1) {
		stat = sceMsgDialogUpdateStatus();

		if (stat == SCE_COMMON_DIALOG_STATUS_FINISHED) {
			sceMsgDialogTerminate();
			break;
		}
	}
}

char sceImeKeyboardRetVal[1000];
void OpenKeyboardDialog(int maxTextLength, const char *title, SceImeType type, SceImeEnterLabel enterLabel) {
	wchar_t inputTextBuffer[maxTextLength + 1];
	wchar_t _title[100];

	mbstowcs(_title, title, strlen(title) + 1);

	SceImeDialogParam param;

	memset(&param, 0, sizeof(SceImeDialogParam));

	param.maxTextLength = maxTextLength;
	param.inputTextBuffer = inputTextBuffer;
	param.title = _title;
	param.userId = SCE_USER_SERVICE_USER_ID_EVERYONE;
	param.type = type;
	param.enterLabel = enterLabel;
	param.posx = 1920.0f / 2;
	param.posy = 1080.0f / 2;
	param.horizontalAlignment = SCE_IME_HALIGN_CENTER;
	param.verticalAlignment = SCE_IME_VALIGN_CENTER;

	int init_log = sceImeDialogInit(&param, NULL);

	int keyboardRunning = 1;
	while (keyboardRunning) {
		int status = sceImeDialogGetStatus();

		if (status == SCE_IME_DIALOG_STATUS_FINISHED) {
			SceImeDialogResult result;
			memset(&result, 0, sizeof(SceImeDialogResult));

			sceImeDialogGetResult(&result);

			if (result.endstatus == SCE_IME_DIALOG_END_STATUS_OK) {
				char returnValue[maxTextLength + 1];
				wcstombs(returnValue, inputTextBuffer, maxTextLength);

				snprintf(sceImeKeyboardRetVal, sizeof(sceImeKeyboardRetVal), "%s", returnValue);
			}

			keyboardRunning = 0;
			sceImeDialogTerm();
		}
		else if (status == SCE_IME_DIALOG_STATUS_NONE) {
			keyboardRunning = 0;
			sceImeDialogTerm();
		}
	}
}
