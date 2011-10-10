#ifndef DOWNLOAD_LIST_MODEL_NODE_H
#define DOWNLOAD_LIST_MODEL_NODE_H

#include <vector>
#include <set>

#include <wx/dynarray.h>
#include <wx/string.h>
#include <wx/variant.h>

#include "../../net/thrift/pyload_types.h"
#include "../../log.h"
#include "../../services/pyload_data_store.h"

class DownloadListModelNode;

class DownloadListModelNode
{
public:
    DownloadListModelNode(DownloadListModelNode* parent) : m_parent(parent) {};

    virtual ~DownloadListModelNode() {
        deleteChildren();
    };

    DownloadListModelNode* getParent() {
        return m_parent;
    }

    std::vector<DownloadListModelNode*>& getChildren() {
        return m_children;
    }

    DownloadListModelNode* getNthChild(unsigned int n) {
        try {
            return m_children.at(n);
        } catch (std::out_of_range& e) {
            LOG(logERROR) << e.what();
            throw;
        }
    }

    void insertChild(DownloadListModelNode* child, unsigned int n) {
        std::vector<DownloadListModelNode*>::iterator node;
        try {
            m_children.insert(node + n, child);
        } catch (std::out_of_range& e) {
            LOG(logERROR) << e.what();
            throw;
        }

    }

    void appendChild(DownloadListModelNode* child) {
        m_children.push_back(child);
    }

    const unsigned int getChildCount() const {
        return m_children.size();
    }

    void setParent(DownloadListModelNode* parent) {
        m_parent = parent;
    }

    void setChildren(std::vector<DownloadListModelNode*> children) {
        deleteChildren();
        m_children = children;
    }

    virtual bool isContainer() const = 0;
    virtual bool hasColumns() const = 0;
    virtual bool isEnabled() const = 0;
    virtual void getHoster(wxVariant& hoster) = 0;
    virtual void setHoster(const wxVariant& hoster) = 0;
    virtual void getHosterSet(std::set<std::string>& hoster) = 0;
    virtual void getName(wxVariant& name) const = 0;
    virtual void setName(const wxVariant& name) = 0;
    virtual void getOrder(wxVariant& order) const = 0;
    virtual void setOrder(const wxVariant& order) = 0;
    virtual void getPriority(wxVariant& priority) const = 0;
    virtual void setPriority(const wxVariant& priority) = 0;
    virtual void getProgress(wxVariant& progress) const = 0;
    virtual void setProgress(const wxVariant& progress) = 0;
    virtual void getProgressText(wxVariant& progressText) const = 0;
    virtual void setProgressText(const wxVariant& progressText) = 0;
    virtual void getStatus(wxVariant& status) const = 0;
    virtual void setStatus(const wxVariant& status) = 0;

private:
    // Neither copy nor assign
    DownloadListModelNode(const DownloadListModelNode&);
    void operator=(const DownloadListModelNode&);

    virtual void deleteChildren() {
        std::vector<DownloadListModelNode*>::iterator node;
        for (node = m_children.begin(); node != m_children.end(); ++node) {
            delete *node;
        }
        m_children.clear();
    };

    DownloadListModelNode* m_parent;
    std::vector<DownloadListModelNode*> m_children;
};

class DownloadListModelNodeBackend : public DownloadListModelNode
{
public:
    DownloadListModelNodeBackend() : DownloadListModelNode(NULL) {};
    virtual ~DownloadListModelNodeBackend() {};

    virtual bool isContainer() const {
        return true;
    }

    virtual bool hasColumns() const {
        return true;
    }

    virtual bool isEnabled() const {
        return true;
    }

    virtual void getHoster(wxVariant& hoster) {
        std::set<std::string> hosterSet;
        getHosterSet(hosterSet);

        wxString hosterString("[");

        std::set<std::string>::iterator host;
        for (host = hosterSet.begin(); host != hosterSet.end(); ++host) {
            hosterString.append(*host).append(";");
        }
        hosterString.RemoveLast();
        hosterString.append("]");
        hoster = hosterString;
    }

    virtual void getHosterSet(std::set<std::string>& hoster) {
        std::vector<DownloadListModelNode*>::iterator node;
        for (node = getChildren().begin(); node != getChildren().end(); ++node) {
            (*node)->getHosterSet(hoster);
        }
    }

    virtual void getName(wxVariant& name) const {
        name = "Pyload";
    }

    virtual void getOrder(wxVariant& order) const {
        order = wxString();
    }

    virtual void getPriority(wxVariant& priority) const {
        priority = wxString();
    }

    virtual void getProgress(wxVariant& progress) const {
        progress = wxString();
    }

    virtual void getProgressText(wxVariant& progressText) const {
        progressText = wxString();
    }

    virtual void getStatus(wxVariant& status) const {
        status = wxString();
    }

    virtual void setHoster(const wxVariant& hoster) {

    }

    virtual void setName(const wxVariant& name) {

    }

    virtual void setOrder(const wxVariant& order) {

    }

    virtual void setPriority(const wxVariant& priority) {

    }

    virtual void setProgress(const wxVariant& progress) {

    }

    virtual void setProgressText(const wxVariant& progressText) {

    }

    virtual void setStatus(const wxVariant& status) {

    }

private:
    // Neither copy nor assign
    DownloadListModelNodeBackend(const DownloadListModelNodeBackend&);
    void operator=(const DownloadListModelNodeBackend&);
};


class DownloadListModelNodePackage : public DownloadListModelNode
{
public:
    DownloadListModelNodePackage(DownloadListModelNode* parent, PackageData& packageData) : DownloadListModelNode(parent), m_packageData(packageData) {};
    virtual ~DownloadListModelNodePackage() {};

    virtual bool isContainer() const {
        return true;
    }

    virtual bool hasColumns() const {
        return true;
    }

    virtual bool isEnabled() const {
        return true;
    }

    virtual void getHoster(wxVariant& hoster) {
        std::set<std::string> hosterSet;
        getHosterSet(hosterSet);

        wxString hosterString("[");

        std::set<std::string>::iterator host;
        for (host = hosterSet.begin(); host != hosterSet.end(); ++host) {
            hosterString.append(*host).append(";");
        }
        hosterString.RemoveLast();
        hosterString.append("]");
        hoster = hosterString;
    }

    virtual void getHosterSet(std::set<std::string>& hoster) {
        std::vector<DownloadListModelNode*>::iterator node;
        for (node = getChildren().begin(); node != getChildren().end(); ++node) {
            (*node)->getHosterSet(hoster);
        }
    }

    virtual void getName(wxVariant& name) const {
        name = m_packageData.name;
    }

    virtual void getOrder(wxVariant& order) const {
        order = wxString(wxString::Format(wxT("%i"), m_packageData.order));
    }

    virtual void getPriority(wxVariant& priority) const {
        priority = wxString("todo");
    }

    virtual void getProgress(wxVariant& progress) const {
        progress = wxString::Format(wxT("%i / %i"), m_packageData.sizedone, m_packageData.sizetotal);
    }

    virtual void getProgressText(wxVariant& progressText) const {
        progressText = wxString::Format(wxT("%i / %i"), m_packageData.sizedone, m_packageData.sizetotal);
    }

    virtual void getStatus(wxVariant& status) const {
        status = wxString("todo");
    }

    virtual void setHoster(const wxVariant& hoster) {

    }

    virtual void setName(const wxVariant& name) {

    }

    virtual void setOrder(const wxVariant& order) {

    }

    virtual void setPriority(const wxVariant& priority) {

    }

    virtual void setProgress(const wxVariant& progress) {

    }

    virtual void setProgressText(const wxVariant& progressText) {

    }

    virtual void setStatus(const wxVariant& status) {

    }

private:
    // Neither copy nor assign
    DownloadListModelNodePackage(const DownloadListModelNodePackage&);
    void operator=(const DownloadListModelNodePackage&);

    PackageData m_packageData;
};

class DownloadListModelNodeFile : public DownloadListModelNode
{
public:
    DownloadListModelNodeFile(DownloadListModelNode* parent, FileData& fileData) : DownloadListModelNode(parent), m_fileData(fileData) {};
    virtual ~DownloadListModelNodeFile() {};

    virtual bool isContainer() const {
        return false;
    }

    virtual bool hasColumns() const {
        return true;
    }

    virtual bool isEnabled() const {
        return true;
    }

    virtual void getHoster(wxVariant& hoster) {
        hoster = m_fileData.plugin;
    }

    virtual void getHosterSet(std::set<std::string>& hoster) {
        hoster.insert(m_fileData.plugin);
    }

    virtual void getName(wxVariant& name) const {
        name = m_fileData.name;
    }

    virtual void getOrder(wxVariant& order) const {
        order = wxString::Format(wxT("%i"), m_fileData.order);
    }

    virtual void getPriority(wxVariant& priority) const {
        priority = wxString("todo");
    }

    virtual void getProgress(wxVariant& progress) const {
        progress = wxString::Format(wxT("todo / %i"), m_fileData.size);
    }

    virtual void getProgressText(wxVariant& progressText) const {
        progressText = wxString::Format(wxT("todo / %i"), m_fileData.size);
    }

    virtual void getStatus(wxVariant& status) const {
        status = m_fileData.statusmsg;
    }

    virtual void setHoster(const wxVariant& hoster) {

    }

    virtual void setName(const wxVariant& name) {

    }

    virtual void setOrder(const wxVariant& order) {

    }

    virtual void setPriority(const wxVariant& priority) {

    }

    virtual void setProgress(const wxVariant& progress) {

    }

    virtual void setProgressText(const wxVariant& progressText) {

    }

    virtual void setStatus(const wxVariant& status) {

    }

private:
    // Neither copy nor assign
    DownloadListModelNodeFile(const DownloadListModelNodeFile&);
    void operator=(const DownloadListModelNodeFile&);

    FileData m_fileData;
};

//class DownloadListModelNode
//{
//
//private:
//    DownloadListModelNode(const DownloadListModelNode& rhs);
//    DownloadListModelNode& operator=(const DownloadListModelNode& rhs);
//
//    DownloadListModelNode* m_parentNode;
//    DownloadListModelNodePtrArray m_childrenNodes;
//    short                   m_order;
//    wxString                m_name;
//    wxString                m_hoster;
//    Priority                m_priority;
//    wxString                m_status;
//    wxString                m_progressText;
//    int                     m_progress;
//    bool                    m_container;
//
//public:
//    DownloadListModelNode(DownloadListModelNode* parent, const wxString& backendName) {
//        m_order = -1;
//        m_priority = -1;
//        m_progress = -1;
//        m_parentNode = parent;
//        m_name = backendName;
//        m_container = true;
//    }
//
//    DownloadListModelNode(DownloadListModelNode* parent,
//                          int order,
//                          const wxString& name,
//                          const wxString& hoster,
//                          int priority,
//                          const wxString& status,
//                          const wxString& progressText,
//                          int progress,
//                          bool container = false) {
//
//        m_parentNode = parent;
//        m_order = order;
//        m_name = name;
//        m_hoster = hoster;
//        m_priority = priority;
//        m_status = status;
//        m_progressText = progressText;
//        m_progress = progress;
//        m_container = container;
//    }
//
//    virtual ~DownloadListModelNode() {
//        size_t count = m_childrenNodes.GetCount();
//        for (size_t i = 0; i < count; i++) {
//            DownloadListModelNode* child = m_childrenNodes[i];
//            delete child;
//        }
//    }
//
//    bool IsContainer() const {
//        return m_container;
//    }
//
//    DownloadListModelNode* GetParent() {
//        return m_parentNode;
//    }
//    DownloadListModelNodePtrArray& GetChildren() {
//        return m_childrenNodes;
//    }
//    DownloadListModelNode* GetNthChild(unsigned int n) {
//        return m_childrenNodes.Item(n);
//    }
//    void Insert(DownloadListModelNode* child, unsigned int n) {
//        m_childrenNodes.Insert(child, n);
//    }
//    void Append(DownloadListModelNode* child) {
//        m_childrenNodes.Add(child);
//    }
//    unsigned int GetChildCount() const {
//        return m_childrenNodes.GetCount();
//    }
//
//    void setChildrenNodes(const DownloadListModelNodePtrArray& childrenNodes) {
//        this->m_childrenNodes = childrenNodes;
//    }
//    void setContainer(bool container) {
//        this->m_container = container;
//    }
//    void setHoster(const wxString& hoster) {
//        this->m_hoster = hoster;
//    }
//    void setName(const wxString& name) {
//        this->m_name = name;
//    }
//    void setOrder(short order) {
//        this->m_order = order;
//    }
//    void setParentNode(DownloadListModelNode* parentNode) {
//        this->m_parentNode = parentNode;
//    }
//    void setPriority(const Priority& priority) {
//        this->m_priority = priority;
//    }
//    void setProgress(int progress) {
//        this->m_progress = progress;
//    }
//    void setProgressText(const wxString& progressText) {
//        this->m_progressText = progressText;
//    }
//    void setStatus(const wxString& status) {
//        this->m_status = status;
//    }
//    const DownloadListModelNodePtrArray& getChildrenNodes() const {
//        return m_childrenNodes;
//    }
//    bool getContainer() const {
//        return m_container;
//    }
//    const wxString& getHoster() const {
//        return m_hoster;
//    }
//    const wxString& getName() const {
//        return m_name;
//    }
//    short getOrder() const {
//        return m_order;
//    }
//    DownloadListModelNode* getParentNode() {
//        return m_parentNode;
//    }
//    const Priority& getPriority() const {
//        return m_priority;
//    }
//    int getProgress() const {
//        return m_progress;
//    }
//    const wxString& getProgressText() const {
//        return m_progressText;
//    }
//    const wxString& getStatus() const {
//        return m_status;
//    }
//};

#endif // DOWNLOAD_LIST_MODEL_NODE_H
