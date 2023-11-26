//
//  ARANode.h
//  ARA
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARANode_h
#define ARANode_h

#include "ARAPlatform.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! A base class for a Tree-like hierarchy.
template < class T >
class Node
{
protected:
    
    //! @brief
    //! The parent node.
    Weak<T> mParentNode;
    
    //! @brief
    //! The children nodes.
    std::vector<Ptr<T>> mChildrenNodes;
    
public:
    
    //! @brief
    //! Returns the node's parent.
    inline Ptr<T> parent() const { return mParentNode.lock(); }
    
    //! @brief
    //! Returns the node's children.
    inline std::vector<Ptr<Node>> children() const { return mChildrenNodes; }
    
    //! @brief
    //! Returns the number of children.
    inline size_t childCount() const { return mChildrenNodes.size(); }
    
    //! @brief
    //! Returns the child at given index.
    inline Ptr<Node> child(size_t index) const { return mChildrenNodes.at(index); }
    
    //! @brief
    //! Returns the index of a given child node.
    inline size_t indexOfChild(const Ptr<Node>& child) const
    {
        auto it = std::find(mChildrenNodes.begin(), mChildrenNodes.end(), child);
        
        if (it == mChildrenNodes.end())
            return InvalidIndex;
        
        return std::distance(mChildrenNodes.begin(), it);
    }
    
    //! @brief
    //! Returns the previous child in the parent list.
    inline Ptr<Node> previous() const
    {
        auto p = mParentNode.lock();
        
        if (!p)
            return nullptr;
        
        auto it = p->mChildrenNodes.rbegin();
        
        for (; it != p->mChildrenNodes.rend(); ++it)
        {
            if ((*it).get() == this)
            {
                it++;
                break;
            }
        }
        
        if (it != p->mChildrenNodes.rend())
            return *it;
        
        return nullptr;
    }
    
    //! @brief
    //! Returns the next child in the parent list.
    inline Ptr<Node> next() const
    {
        auto p = mParentNode.lock();
        
        if (!p)
            return nullptr;
        
        auto it = p->mChildrenNodes.begin();
        
        for (; it != p->mChildrenNodes.end(); ++it)
        {
            if ((*it).get() == this)
            {
                it++;
                break;
            }
        }
        
        if (it != p->mChildrenNodes.end())
            return *it;
        
        return nullptr;
    }
};

ARA_END_NAMESPACE

#endif /* ARANode_h */
