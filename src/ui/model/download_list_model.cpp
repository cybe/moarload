#include "../../log.h"
#include "download_list_model.h"

DownloadListModel::DownloadListModel()
{
    m_root = new DownloadListModelNode(NULL, "PyLoad");

}

DownloadListModel::~DownloadListModel()
{
}

unsigned int DownloadListModel::GetChildren(const wxDataViewItem& parent, wxDataViewItemArray& array) const
{
    DownloadListModelNode* node = (DownloadListModelNode*) parent.GetID();
    if (!node) {
        array.Add(wxDataViewItem((void*) m_root));
        return 1;
    }

    if (node->GetChildCount() == 0) {
        return 0;
    }

    unsigned int count = node->GetChildren().GetCount();

    for (unsigned int pos = 0; pos < count; pos++) {
        DownloadListModelNode* child = node->GetChildren().Item(pos);
        array.Add(wxDataViewItem((void*) child));
    }

    return count;
}

wxDataViewItem DownloadListModel::GetParent(const wxDataViewItem& item) const
{
    // the invisible root node has no parent
    if (!item.IsOk()) {
        return wxDataViewItem(0);
    }

    DownloadListModelNode* node = (DownloadListModelNode*) item.GetID();

    // "PyLoad" also has no parent
    if (node->getParentNode() == NULL) {
        return wxDataViewItem(0);
    }

    return wxDataViewItem((void*) node->GetParent());
}

void DownloadListModel::GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const
{
    wxASSERT(item.IsOk());

    DownloadListModelNode* node = (DownloadListModelNode*) item.GetID();
    switch (col) {
        case 0:
            variant = (long) node->getOrder();
            break;
        case 1:
            variant = node->getName();
            break;
        case 2:
            variant = node->getHoster();
            break;
        case 3:
            variant = (long) node->getPriority();
            break;
        case 4:
            variant = node->getStatus();
            break;
        case 5:
            variant = node->getProgressText();
            break;

        default:
            LOG(logWARNING) <<  "DownloadListModel::GetValue: wrong column" << col ;
    }
}

bool DownloadListModel::IsContainer(const wxDataViewItem& item) const
{
    // the invisble root node can have children
    if (!item.IsOk())
        return true;

    DownloadListModelNode* node = (DownloadListModelNode*) item.GetID();
    return node->IsContainer();
}

bool DownloadListModel::IsEnabled(const wxDataViewItem& item, unsigned int col) const
{
    wxASSERT(item.IsOk());

    DownloadListModelNode* node = (DownloadListModelNode*) item.GetID();

    return true;
}

bool DownloadListModel::SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col)
{
    wxASSERT(item.IsOk());

    DownloadListModelNode* node = (DownloadListModelNode*) item.GetID();
    switch (col) {
        case 0:
            node->setOrder(variant.GetLong());
            return true;
        case 1:
            node->setName(variant.GetString());
            return true;
        case 2:
            node->setHoster(variant.GetString());
            return true;
        case 3:
            node->setPriority(variant.GetLong());
            return true;
        case 4:
            node->setStatus(variant.GetString());
            return true;
        case 5:
            node->setProgressText(variant.GetString());
            return true;

        default:
            LOG(logWARNING) <<  "DownloadListModel::SetValue: wrong column" << col ;
    }
    return false;
}
