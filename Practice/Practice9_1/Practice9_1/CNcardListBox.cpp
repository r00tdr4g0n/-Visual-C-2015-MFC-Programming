// CNcardListBox.cpp : implementation file
//

#include "pch.h"
#include "Practice9_1.h"
#include "CNcardListBox.h"
#include "Practice9_1Dlg.h"


// CNcardListBox

IMPLEMENT_DYNAMIC(CNcardListBox, CVSListBox)

CNcardListBox::CNcardListBox()
{

}

CNcardListBox::~CNcardListBox()
{
}


BEGIN_MESSAGE_MAP(CNcardListBox, CVSListBox)
END_MESSAGE_MAP()



// CNcardListBox message handlers



void CNcardListBox::OnAfterAddItem(int nIndex)
{
	// TODO: Add your implementation code here.
	CPractice91Dlg* pParent = (CPractice91Dlg*)GetParent();
	pParent->AddNameCard(GetItemText(nIndex));
}


void CNcardListBox::OnSelectionChanged()
{
	// TODO: Add your implementation code here.
	int nItem;

	if ((nItem = GetSelItem()) < 0) return;

	CPractice91Dlg* pParent = (CPractice91Dlg*)GetParent();
	pParent->SelectNameCard(nItem);
}


BOOL CNcardListBox::OnBeforeRemoveItem(int nIndex)
{
	// TODO: Add your implementation code here.
	CPractice91Dlg* pParent = (CPractice91Dlg*)GetParent();
	pParent->DeleteNameCard(GetSelItem());

	return TRUE;
}
