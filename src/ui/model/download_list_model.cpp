#include "download_list_model.h"

//#include "../../services/pyload_data_store.h"
//#include "../../services/pyload_requester.h"
//#include "../../net/request.h"


DownloadListModel::DownloadListModel(PyloadDataStore& dataStore, wxDataViewCtrl* downloadDataViewCtrl) :
    m_dataStore(dataStore),
    m_backendNode(new DownloadListModelNodeBackend()),
    m_downloadDataViewCtrl(downloadDataViewCtrl) {

    //r.sendRequest(new GetQueuePackagesRequest(ds));

    m_dataStore.getQueuePackagesUpdate().Connect(this, &DownloadListModel::updateQueuePackages);

    //    m_root = new DownloadListModelNode(NULL, wxString("PyLoad"));
    //
    //    DownloadListModelNode* m_pop = new DownloadListModelNode( m_root, 874, "XXXXXX", "You are not alone", 843, "You are not alone", "You are not alone", 23, true );
    //    //DownloadListModelNode* m_pop = new DownloadListModelNode( m_root, "XXXXXX");
    //
    //    // liste von paketen
    //    // iter liste
    //    // setze parent auf root
    //    // estelle node
    //    // gehe für jedes package alle dateien durch
    //    // erstelle dateien als nodes mit mutter paket
    //    // packete appende files
    //
    //    m_pop->Append(
    //        new DownloadListModelNode( m_pop, 874, "Michael Jackson", "You are not alone", 843, "You are not alone", "You are not alone", 23 ) );
    //    m_root->Append( m_pop );

}

DownloadListModel::~DownloadListModel() {
    delete m_backendNode;
}

unsigned int DownloadListModel::GetChildren(const wxDataViewItem& parent, wxDataViewItemArray& array) const {
    DownloadListModelNode* node = static_cast<DownloadListModelNode*>(parent.GetID());

    if (!node) {
        array.Add(wxDataViewItem(static_cast<void*>(m_backendNode)));
        return 1;
    }

    if (node->getChildCount() == 0) {
        return 0;
    }

    std::vector<DownloadListModelNode*>::const_iterator child;
    for (child = node->getChildren().begin(); child != node->getChildren().end(); ++child) {
        array.Add(wxDataViewItem(static_cast<void*>(*child)));
    }

    return node->getChildCount();
}

wxDataViewItem DownloadListModel::GetParent(const wxDataViewItem& item) const {
    // the invisible root node has no parent
    if (!item.IsOk()) {
        return wxDataViewItem(0);
    }

    DownloadListModelNode* node = static_cast<DownloadListModelNode*>(item.GetID());

    // "PyLoad" also has no parent
    if (node->getParent() == NULL) {
        return wxDataViewItem(0);
    }

    return wxDataViewItem(static_cast<void*>(node->getParent()));
}

void DownloadListModel::GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const {
    wxASSERT(item.IsOk());

    DownloadListModelNode* node = static_cast<DownloadListModelNode*>(item.GetID());
    switch (col) {
        case 0:
            node->getName(variant);
            break;
        case 1:
            node->getOrder(variant);
            break;
        case 2:
            node->getHoster(variant);
            break;
        case 3:
            node->getPriority(variant);
            break;
        case 4:
            node->getStatus(variant);
            break;
        case 5:
            node->getProgressText(variant);
            break;

        default:
            LOG(logWARNING) <<  "DownloadListModel::GetValue: wrong column" << col ;
    }
}

bool DownloadListModel::IsContainer(const wxDataViewItem& item) const {
    // the invisble root node can have children
    if (!item.IsOk()) {
        return true;
    }

    DownloadListModelNode* node = static_cast<DownloadListModelNode*>(item.GetID());
    return node->isContainer();
}
bool DownloadListModel::HasContainerColumns(const wxDataViewItem& item) const {
    DownloadListModelNode* node = static_cast<DownloadListModelNode*>(item.GetID());
    return node->hasColumns();
}

bool DownloadListModel::IsEnabled(const wxDataViewItem& item, unsigned int col) const {
    wxASSERT(item.IsOk());

    DownloadListModelNode* node = static_cast<DownloadListModelNode*>(item.GetID());
    return node->isEnabled();
}

bool DownloadListModel::SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col) {
    wxASSERT(item.IsOk());

    DownloadListModelNode* node = static_cast<DownloadListModelNode*>(item.GetID());
    switch (col) {
        case 0:
            node->setOrder(variant.GetString());
            return true;
        case 1:
            node->setName(variant.GetString());
            return true;
        case 2:
            node->setHoster(variant.GetString());
            return true;
        case 3:
            node->setPriority(variant.GetString());
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


void DownloadListModel::updateQueuePackages() {
    LOG(logDEBUG) << "DownloadListModel::updateQueuePackages";

    wxDataViewItemArray nodesToExpand;
    wxDataViewItem backendNodeItem(static_cast<void*>(m_backendNode));
    ItemChanged(backendNodeItem);
    nodesToExpand.Add(backendNodeItem);

    std::vector<PackageData> packages = m_dataStore.getQueuePackages();
    std::vector<PackageData>::iterator package;
    for (package = packages.begin() ; package != packages.end(); ++package) {
        DownloadListModelNode* packageNode = new DownloadListModelNodePackage(m_backendNode, *package);
        m_backendNode->appendChild(packageNode);
        wxDataViewItem packageNodeItem(static_cast<void*>(packageNode));
        ItemAdded(backendNodeItem, packageNodeItem);
        nodesToExpand.Add(packageNodeItem);

        std::vector<FileData> files = package->links;
        std::vector<FileData>::iterator file;
        for (file = files.begin() ; file != files.end(); ++file) {
            DownloadListModelNode* fileNode = new DownloadListModelNodeFile(packageNode, *file);
            packageNode->appendChild(fileNode);
            ItemAdded(wxDataViewItem(static_cast<void*>(packageNode)), wxDataViewItem(static_cast<void*>(fileNode)));
        }
    }

    for (size_t i = 0; i < nodesToExpand.GetCount(); ++i) {
        m_downloadDataViewCtrl->Expand(nodesToExpand[i]);
    }
}
