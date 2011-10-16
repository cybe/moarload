#ifndef DOWNLOAD_LIST_MODEL_H
#define DOWNLOAD_LIST_MODEL_H

#include <wx/dataview.h>

#include "../../services/pyload_data_store.h"
#include "download_list_model_node.h"

class DownloadListModel : public wxDataViewModel {
private:
    DownloadListModel(const DownloadListModel& rhs);
    DownloadListModel& operator=(const DownloadListModel& rhs);
    void updateQueuePackages();

    PyloadDataStore& m_dataStore;
    DownloadListModelNode* m_backendNode;
    wxDataViewCtrl* m_downloadDataViewCtrl;

public:
    DownloadListModel(PyloadDataStore& dataStore, wxDataViewCtrl* downloadDataViewCtrl);
    virtual ~DownloadListModel();

    virtual unsigned int GetColumnCount() const {
        return 6;
    }

    virtual wxString GetColumnType(unsigned int col) const {
        switch (col) {
            case 0 :
                return wxT("string");
                break;
            case 1 :
                return wxT("string");
                break;
            case 2 :
                return wxT("string");
                break;
            case 3 :
                return wxT("string");
                break;
            case 4 :
                return wxT("string");
                break;
            case 5 :
                return wxT("string");
                break;
            default :
                return wxT("string");
        }
    }

    virtual void GetValue(wxVariant& variant,
                          const wxDataViewItem& item, unsigned int col) const;
    virtual bool SetValue(const wxVariant& variant,
                          const wxDataViewItem& item, unsigned int col);
    virtual bool IsEnabled(const wxDataViewItem& item,
                           unsigned int col) const;
    virtual wxDataViewItem GetParent(const wxDataViewItem& item) const;
    virtual bool IsContainer(const wxDataViewItem& item) const;
    virtual bool HasContainerColumns(const wxDataViewItem&   item) const;
    virtual unsigned int GetChildren(const wxDataViewItem& parent,
                                     wxDataViewItemArray& array) const;

};

#endif // DOWNLOAD_LIST_MODEL_H
