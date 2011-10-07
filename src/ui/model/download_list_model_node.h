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

    DownloadListModelNode* m_parentNode;
    DownloadListModelNodePtrArray m_childrenNodes;
    short                   m_order;
    wxString                m_name;
    wxString                m_hoster;
    Priority                m_priority;
    wxString                m_status;
    wxString                m_progressText;
    int                     m_progress;
    bool                    m_container;

public:
    DownloadListModelNode(DownloadListModelNode* parent, const wxString& backendName) {
        m_parentNode = parent;
        m_name = backendName;
        m_container = true;
    }

    DownloadListModelNode(DownloadListModelNode* parent,
                          short order,
                          wxString& name,
                          wxString& hoster,
                          Priority& priority,
                          wxString& status,
                          wxString& progressText,
                          int progress,
                          bool container = false) {

        m_parentNode = parent;
        m_order = order;
        m_name = name;
        m_hoster = hoster;
        m_priority = priority;
        m_status = status;
        m_progressText = progressText;
        m_progress = progress;
        m_container = container;
    }

    virtual ~DownloadListModelNode() {
        size_t count = m_childrenNodes.GetCount();
        for (size_t i = 0; i < count; i++) {
            DownloadListModelNode* child = m_childrenNodes[i];
            delete child;
        }
    }

    bool IsContainer() const {
        return m_container;
    }

    DownloadListModelNode* GetParent() {
        return m_parentNode;
    }
    DownloadListModelNodePtrArray& GetChildren() {
        return m_childrenNodes;
    }
    DownloadListModelNode* GetNthChild(unsigned int n) {
        return m_childrenNodes.Item(n);
    }
    void Insert(DownloadListModelNode* child, unsigned int n) {
        m_childrenNodes.Insert(child, n);
    }
    void Append(DownloadListModelNode* child) {
        m_childrenNodes.Add(child);
    }
    unsigned int GetChildCount() const {
        return m_childrenNodes.GetCount();
    }

    void setChildrenNodes(const DownloadListModelNodePtrArray& childrenNodes) {
        this->m_childrenNodes = childrenNodes;
    }
    void setContainer(bool container) {
        this->m_container = container;
    }
    void setHoster(const wxString& hoster) {
        this->m_hoster = hoster;
    }
    void setName(const wxString& name) {
        this->m_name = name;
    }
    void setOrder(short order) {
        this->m_order = order;
    }
    void setParentNode(DownloadListModelNode* parentNode) {
        this->m_parentNode = parentNode;
    }
    void setPriority(const Priority& priority) {
        this->m_priority = priority;
    }
    void setProgress(int progress) {
        this->m_progress = progress;
    }
    void setProgressText(const wxString& progressText) {
        this->m_progressText = progressText;
    }
    void setStatus(const wxString& status) {
        this->m_status = status;
    }
    const DownloadListModelNodePtrArray& getChildrenNodes() const {
        return m_childrenNodes;
    }
    bool getContainer() const {
        return m_container;
    }
    const wxString& getHoster() const {
        return m_hoster;
    }
    const wxString& getName() const {
        return m_name;
    }
    short getOrder() const {
        return m_order;
    }
    DownloadListModelNode* getParentNode() {
        return m_parentNode;
    }
    const Priority& getPriority() const {
        return m_priority;
    }
    int getProgress() const {
        return m_progress;
    }
    const wxString& getProgressText() const {
        return m_progressText;
    }
    const wxString& getStatus() const {
        return m_status;
    }
};

#endif // DOWNLOAD_LIST_MODEL_NODE_H
