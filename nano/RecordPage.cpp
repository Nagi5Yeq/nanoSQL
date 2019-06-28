#include "RecordPage.hpp"

void RecordPage::writenext(PageId next)
{
	memcpy(pageData, &next, sizeof(PageId));
}

void RecordPage::writebefore(PageId before)
{
	memcpy(pageData + sizeof(PageId), &before, sizeof(PageId));
}

PageId RecordPage::readnext()
{
	PageId next;
	memcpy(&next, pageData, sizeof(PageId));
	return next;
}

PageId RecordPage::readbefore()
{
	PageId before;
	memcpy(&before, pageData + sizeof(PageId), sizeof(PageId));
	return before;
}
