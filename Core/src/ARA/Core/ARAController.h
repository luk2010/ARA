//
//  ARAController.h
//  lui
//
//  Created by jacques tronconi on 26/11/2023.
//

#ifndef ARAController_h
#define ARAController_h

#include "ARAError.h"
#include "ARANode.h"
#include "ARAView.h"
#include "ARAApplication.h"

ARA_BEGIN_NAMESPACE

//! @brief
//! An Error a Controller can throw.
ARA_DECLARE_ERROR(ControllerError)

//! @brief
//! A Controller class that manages the whole lifetime of a native view.
template < class T >
class Controller : public Node<T>, public std::enable_shared_from_this<T>
{
    //! @brief
    //! The view the controller manages.
    Ptr<View> mView;
    
protected:
    
    //! @brief
    //! Creates a new view.
    virtual Ptr<View> createView(Application& app)
    {
        return app.createView();
    }
    
public:
    
    //! @brief
    //! Returns the controller view.
    virtual Ptr<View> view()
    {
        if (!mView)
            mView = createView(Application::Get());
        return mView;
    }
    
    //! @brief
    //! Returns the controller view.
    inline Ptr<View> view() const { return mView; }
    
    //! @brief
    //! Adds a Controller to this controller children.
    virtual Ptr<Controller> addChild(const Ptr<T>& controller, const Ptr<T>& beforeChild = nullptr)
    {
        auto selfView = view();
        
        if (!selfView)
            throw ControllerError("[ARA::Controller] No view in this controller.");
        
        auto it = std::find(this->mChildrenNodes.begin(), this->mChildrenNodes.end(), beforeChild);
        auto childView = controller->view();
        
        if (!childView)
            throw ControllerError("[ARA::Controller] Cannot get controller view.");
        
        this->mChildrenNodes.insert(it, controller);
        controller->mParentNode = this->shared_from_this();
        
        selfView->addChild(childView, beforeChild ? beforeChild->view() : nullptr);
        
        return controller;
    }
    
    //! @brief
    //! Removes a Controller to this controller children.
    virtual void removeChild(const Ptr<T>& controller)
    {
        auto selfView = view();
        
        if (!selfView)
            throw ControllerError("[ARA::Controller] No view in this controller.");
        
        auto it = std::find(this->mChildrenNodes.begin(), this->mChildrenNodes.end(), controller);
        
        if (it == this->mChildrenNodes.end())
            return;
        
        std::erase(this->mChildrenNodes, controller);
        controller->mParentNode.reset();
        
        selfView->removeChild(controller->view());
    }
};

ARA_END_NAMESPACE

#endif /* ARAController_h */
