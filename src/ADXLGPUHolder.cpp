//
// Created by sfink on 15/07/2025.
//

#include "ADXLGPUHolder.h"
#include <algorithm>

ADLXGPUHolder::ADLXGPUHolder(adlx::IADLXSystem* systemService) 
    : m_gpuList(nullptr)
    , m_gpu(nullptr)
    , m_result(ADLX_FAIL) {
    
    if (systemService != nullptr) {
        // Get the GPU list
        m_result = systemService->GetGPUs(&m_gpuList);
        
        // If we got the list successfully, get the first GPU
        if (ADLX_SUCCEEDED(m_result)) {
            // ReSharper disable once CppDFANullDereference
            m_result = m_gpuList->At(0, &m_gpu);
        }
    }
}

ADLXGPUHolder::~ADLXGPUHolder() {
    m_gpu = nullptr;
    m_gpuList = nullptr;
}

bool ADLXGPUHolder::isValid() const {
    return ADLX_SUCCEEDED(m_result) && m_gpuList != nullptr && m_gpu != nullptr;
}

adlx::IADLXGPUListPtr ADLXGPUHolder::getGPUList() {
    // Don't manually acquire - the smart pointer handles reference counting
    return m_gpuList;
}

adlx::IADLXGPUPtr ADLXGPUHolder::getGPU() const {
    // Don't manually acquire - the smart pointer handles reference counting
    return m_gpu;
}

ADLXGPUHolder::ADLXGPUHolder(ADLXGPUHolder&& other) noexcept 
    : m_gpuList(other.m_gpuList)
    , m_gpu(other.m_gpu)
    , m_result(other.m_result) {
    // Clear the source object's pointers
    other.m_gpuList = nullptr;
    other.m_gpu = nullptr;
    other.m_result = ADLX_FAIL;
}

ADLXGPUHolder& ADLXGPUHolder::operator=(ADLXGPUHolder&& other) noexcept {
    if (this != &other) {
        // Release current resources
        m_gpu = nullptr;
        m_gpuList = nullptr;
        
        // Move from other
        m_gpuList = other.m_gpuList;
        m_gpu = other.m_gpu;
        m_result = other.m_result;
        
        // Clear the source object's pointers
        other.m_gpuList = nullptr;
        other.m_gpu = nullptr;
        other.m_result = ADLX_FAIL;
    }
    return *this;
}