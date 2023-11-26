//
//  ARAApplication.cpp
//  lui
//
//  Created by jacques tronconi on 26/11/2023.
//

#include "ARAApplication.h"

ARA_BEGIN_NAMESPACE

Application* Application::mInstance = NULL;

Application::Application()
{
    if (mInstance)
        throw ApplicationError("[ARA::Application] An Application is already constructed.");
    mInstance = this;
}

Application::~Application()
{
    mInstance = NULL;
}

Application& Application::Get()
{
    return *mInstance;
}

ARA_END_NAMESPACE
