#ifndef DOWNLOAD_LIST_MODEL_NODE_H
#define DOWNLOAD_LIST_MODEL_NODE_H

#include <wx/dynarray.h>
#include <wx/string.h>

#include "../../net/thrift/pyload_types.h"

class DownloadListModelNode;
WX_DEFINE_ARRAY_PTR(DownloadListModelNode*, DownloadListModelNodePtrArray);

class DownloadListModelNode
{

private:
    DownloadListModelNode(const DownloadListModelNode& rhs);
    DownloadListModelNode& operator=(const DownloadListModelNode& rhs);
    DownloadListModelNode* parentNode;
    DownloadListModelNodePtrArray childrenNodes;

    short                   m_order;
    wxString                m_name;
    wxString                m_hoster;
    Priority                m_priority;
    wxString                m_status;
    wxString                m_progressText;
    int                     m_progress;
    bool                    m_container;

public:
    DownloadListModelNode(DownloadListModelNode* parent, wxString& backendName) {
        parentNode = parent;
        m_name = backendName;
        m_container = true;
    }

    DownloadListModelNode(DownloadListModelNode* parent,
                          short order,
                          const wxString& name,
                          const wxString& hoster,
                          const Priority& priority,
                          const wxString& status,
                          const wxString& progressText,
                          const int progress,
                          const bool container = false) {
        
        parentNode = parent;
        m_order = order;
        m_name = name;
        m_hoster = hoster;
        m_priority = priority;
        m_status = status;
        m_progressText = progressText;
        m_progress = progress;
        m_container = container;
    }

    virtual ~DownloadListModelNode(){
        size_t count = childrenNodes.GetCount();
        for (size_t i = 0; i < count; i++)
        {
            DownloadListModelNode *child = childrenNodes[i];
            delete child;
        }
    }

    bool IsContainer() const {
        return m_container;
    }

    DownloadListModelNode* GetParent() {
        return parentNode;
    }
    DownloadListModelNodePtrArray& GetChildren() {
        return childrenNodes;
    }
    DownloadListModelNode* GetNthChild(unsigned int n) {
        return childrenNodes.Item(n);
    }
    void Insert(DownloadListModelNode* child, unsigned int n) {
        childrenNodes.Insert(child, n);
    }
    void Append(DownloadListModelNode* child) {
        childrenNodes.Add(child);
    }
    unsigned int GetChildCount() const {
        return childrenNodes.GetCount();
    }

};

#endif // DOWNLOAD_LIST_MODEL_NODE_H
