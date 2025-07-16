//
// Created by sfink on 15/07/2025.
//

#ifndef ADXLGPUHOLDER_H
#define ADXLGPUHOLDER_H
#include "../../../../SDK/Include/ISystem2.h"

class ADLXGPUHolder {
private:
    adlx::IADLXGPUListPtr m_gpuList;
    adlx::IADLXGPUPtr m_gpu;
    ADLX_RESULT m_result;

public:
    // Constructor that initializes with ADLXHelper
    explicit ADLXGPUHolder(adlx::IADLXSystem* systemService);

    // Destructor
    ~ADLXGPUHolder();

    // Status check
    bool isValid() const;

    // Getters
    adlx::IADLXGPUListPtr getGPUList();
    adlx::IADLXGPUPtr getGPU() const;

    // Prevent copying
    ADLXGPUHolder(const ADLXGPUHolder&) = delete;
    ADLXGPUHolder& operator=(const ADLXGPUHolder&) = delete;

    // Allow moving
    ADLXGPUHolder(ADLXGPUHolder&& other) noexcept;
    ADLXGPUHolder& operator=(ADLXGPUHolder&& other) noexcept;
};

#endif //ADXLGPUHOLDER_H