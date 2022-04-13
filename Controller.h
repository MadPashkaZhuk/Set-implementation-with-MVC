#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "resource.h"
#include "View.h"

class Controller {
public:
	static INT_PTR CALLBACK Manipulate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
		static Set model;
		static View view(hDlg, &model);
		char editControlBuff[255];
		std::string editControlString;
		std::stringstream sstream;
		int copyLen;
		UNREFERENCED_PARAMETER(lParam);
		switch (message) {
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
			case PUSH_BUTTON:
				editControlString.clear();
				copyLen = SendDlgItemMessage(hDlg, PUSH_EDIT, EM_GETLINE, NULL, (LPARAM)editControlBuff);
				for (int i = 0; i < copyLen; ++i) {
					editControlString += editControlBuff[i];
				}
				sstream = std::stringstream(editControlString);
				for (int element; sstream >> element;) {
					model.add(element);
				}
				view.Update();
				break;
			}
			break;
		case WM_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			break;
		}
		return (INT_PTR)FALSE;
	}
};

#endif  // CONTROLLER_H
