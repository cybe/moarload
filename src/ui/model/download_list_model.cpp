#include "../../log.h"
#include "download_list_model.h"

DownloadListModel::DownloadListModel()
{
    m_root = new DownloadListModelNode(NULL, wxString("PyLoad"));
    
    DownloadListModelNode* m_pop = new DownloadListModelNode( m_root, 874, "XXXXXX", "You are not alone", 843, "You are not alone", "You are not alone", 23, true );
    //DownloadListModelNode* m_pop = new DownloadListModelNode( m_root, "XXXXXX");
    
    // liste von paketen
    // iter liste
    // setze parent auf root
    // estelle node
    // gehe für jedes package alle dateien durch
    // erstelle dateien als nodes mit mutter paket
    // packete appende files
    
    m_pop->Append(
        new DownloadListModelNode( m_pop, 874, "Michael Jackson", "You are not alone", 843, "You are not alone", "You are not alone", 23 ) );
    m_root->Append( m_pop );

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
            variant = node->getName();
        break;
        case 1:
            variant = (long) node->getOrder();
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
bool DownloadListModel::HasContainerColumns(const wxDataViewItem&	item) const
{
    return true;
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
