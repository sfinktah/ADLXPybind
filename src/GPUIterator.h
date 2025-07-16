//
// Created by sfink on 15/07/2025.
//

#ifndef GPUITERATOR_H
#define GPUITERATOR_H

#include "../../../../SDK/Include/ISystem.h"
#include "../../../../SDK/Include/ISystem2.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

class GPUIterator {
private:
    adlx::IADLXGPUListPtr m_list;
    adlx_uint m_current;
    bool m_begin;

public:
    // Default constructor
    GPUIterator();

    // Parameterized constructor
    GPUIterator(adlx::IADLXGPUList* list, bool begin = true);

    GPUIterator& iter();

    adlx::IADLXGPUPtr next();

    // These are needed for STL-style iteration
    adlx::IADLXGPUPtr operator*() const;

    bool operator==(const GPUIterator& other) const;

    bool operator!=(const GPUIterator& other) const;

    GPUIterator& operator++();
};

#endif //GPUITERATOR_H