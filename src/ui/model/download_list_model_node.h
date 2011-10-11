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

class DownloadListModelNode {
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



class DownloadListModelNodeBackend : public DownloadListModelNode {
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



class DownloadListModelNodePackage : public DownloadListModelNode {
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
        progress = wxString::Format(wxT("%ld / %ld"), m_packageData.sizedone, m_packageData.sizetotal);
    }

    virtual void getProgressText(wxVariant& progressText) const {
        progressText = wxString::Format(wxT("%ld / %ld"), m_packageData.sizedone, m_packageData.sizetotal);
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



class DownloadListModelNodeFile : public DownloadListModelNode {
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
        progress = wxString::Format(wxT("todo / %ld"), m_fileData.size);
    }

    virtual void getProgressText(wxVariant& progressText) const {
        progressText = wxString::Format(wxT("todo / %ld"), m_fileData.size);
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

#endif // DOWNLOAD_LIST_MODEL_NODE_H
