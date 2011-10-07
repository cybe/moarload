#ifndef DOWNLOAD_LIST_MODEL_H
#define DOWNLOAD_LIST_MODEL_H

#include <wx/dataview.h>

#include "download_list_model_node.h"

class DownloadListModel : public wxDataViewModel
{

private:
    DownloadListModel(const DownloadListModel& rhs);
    DownloadListModel& operator=(const DownloadListModel& rhs);
    
    DownloadListModelNode*   m_root;

public:
    DownloadListModel();
    virtual ~DownloadListModel();

    virtual unsigned int GetColumnCount() const {
        return 6;
    }

    virtual wxString GetColumnType(unsigned int col) const {
        switch (col) {
            case 0 :
                return wxT("long");
                break;
            case 1 :
                return wxT("string");
                break;
            case 2 :
                return wxT("string");
                break;
            case 3 :
                return wxT("long");
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
    virtual unsigned int GetChildren(const wxDataViewItem& parent,
                                     wxDataViewItemArray& array) const;

};

#endif // DOWNLOAD_LIST_MODEL_H
