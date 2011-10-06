#include "download_list_data_model.h"

DownloadListDataModel::DownloadListDataModel()
{
    //ctor
}

DownloadListDataModel::~DownloadListDataModel()
{
    //dtor
}

unsigned int DownloadListDataModel::GetChildren(const wxDataViewItem &item, wxDataViewItemArray &children) const
{
    return 1;
}

unsigned int DownloadListDataModel::GetColumnCount() const
{
    return 1;
}

wxString DownloadListDataModel::GetColumnType(unsigned int col) const
{
    return _("s");
}

wxDataViewItem DownloadListDataModel::GetParent(const wxDataViewItem &item) const
{

}

void DownloadListDataModel::GetValue(wxVariant &variant, const wxDataViewItem &item, unsigned int col) const
{

}

bool DownloadListDataModel::IsContainer(const wxDataViewItem &item) const
{
    return false;
}

bool DownloadListDataModel::SetValue(const wxVariant &variant, const wxDataViewItem &item, unsigned int col)
{
    return false;
}
