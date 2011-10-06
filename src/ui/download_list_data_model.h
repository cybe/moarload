#ifndef DOWNLOAD_LIST_DATA_MODEL_H
#define DOWNLOAD_LIST_DATA_MODEL_H

#include <wx/dataview.h>


class DownloadListDataModel : public wxDataViewModel
{
    public:
        DownloadListDataModel();
        virtual ~DownloadListDataModel();
        virtual unsigned int GetChildren(const wxDataViewItem &item, wxDataViewItemArray &children) const;
        virtual unsigned int GetColumnCount() const;
        virtual wxString GetColumnType(unsigned int col) const;
        virtual wxDataViewItem GetParent(const wxDataViewItem &item) const;
        virtual void GetValue(wxVariant &variant, const wxDataViewItem &item, unsigned int col) const;
        virtual bool IsContainer(const wxDataViewItem &item) const;
        virtual bool SetValue(const wxVariant &variant, const wxDataViewItem &item, unsigned int col);
    protected:
    private:
};

#endif // DOWNLOAD_LIST_DATA_MODEL_H
