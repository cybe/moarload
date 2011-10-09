#ifndef NODE_H
#define NODE_H

#include <vector>

#include "../../log.h"

class Node;

class Node
{
public:
    Node() {};
    
    Node(Node* parent) {
        m_parent = parent;
    };
    
    virtual ~Node() {
        deleteChildren();
    };

    Node* getParent() {
        return m_parent;
    }

    std::vector<Node*>& getChildren() {
        return m_children;
    }

    Node* getNthChild(unsigned int n) {
        try {
            return m_children.at(n);
        } catch (std::out_of_range& e) {
            LOG(logERROR) << e.what();
            throw;
        }
    }

    void insertChild(Node* child, unsigned int n) {
        std::vector<Node*>::iterator node;
        try {
            m_children.insert(node + n, child);
        } catch (std::out_of_range& e) {
            LOG(logERROR) << e.what();
            throw;
        }

    }

    void appendChild(Node* child) {
        m_children.push_back(child);
    }

    unsigned int getChildCount() const {
        return m_children.size();
    }

    void setParent(Node* parent) {
        m_parent = parent;
    }
    
    void setChildren(std::vector<Node*> children) {
        deleteChildren();
        m_children = children;
    }

private:
    // Neither copy nor assign
    Node(const Node&);
    void operator=(const Node&);
    
    void deleteChildren() {
        std::vector<Node*>::iterator node;
        for (node = m_children.begin(); node != m_children.end(); ++node) {
            delete *node;
        }
        m_children.clear();
    };

    Node* m_parent;
    std::vector<Node*> m_children;
};

#endif // NODE_H
