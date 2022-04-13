#ifndef VIEW_H
#define VIEW_H
#include <windows.h>
#include <sstream>
#include "Set.h"

class View {
public:
	View(HWND hdlg, Set* model_example) : hDlg(hdlg), model(model_example) {}

	void Update() {
		std::string stringElem;
		auto iter = model->CreateIterator();
		SendDlgItemMessage(hDlg, TEXT_LIST, LB_RESETCONTENT, NULL, NULL);
		for (iter->First(); !iter->isDone(); iter->Next()) {
			stringElem = std::to_string(iter->CurrentElement());
			SendDlgItemMessage(hDlg, TEXT_LIST, LB_INSERTSTRING, -1, (LPARAM)stringElem.data());
		}
		iter = model->CreateIterator();
		SendDlgItemMessage(hDlg, TEXT_LIST2, LB_RESETCONTENT, NULL, NULL);
		for (iter->First(); !iter->isDone(); iter->Next()) {
			if (iter->CurrentElement() == 1) {
				stringElem = std::to_string(iter->getIndex());
				SendDlgItemMessage(hDlg, TEXT_LIST2, LB_INSERTSTRING, -1, (LPARAM)stringElem.data());
			}
		}
		SendDlgItemMessage(hDlg, CARDINALITY_LIST, LB_RESETCONTENT, NULL, NULL);
		stringElem = std::to_string(model->cardinality());
		SendDlgItemMessage(hDlg, CARDINALITY_LIST, LB_INSERTSTRING, -1, (LPARAM)stringElem.data());
	}
private:
	HWND hDlg;
	Set* model;
};

#endif  // VIEW_H

