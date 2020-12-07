#pragma once


// CNcardListBox

class CNcardListBox : public CVSListBox
{
	DECLARE_DYNAMIC(CNcardListBox)

public:
	CNcardListBox();
	virtual ~CNcardListBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void OnAfterAddItem(int nIndex);
	void OnSelectionChanged();
	BOOL OnBeforeRemoveItem(int nIndex);
};


