//
// Created by sfink on 15/07/2025.
//

#include "GPUIterator.h"
#include <pybind11/pybind11.h>

// Default constructor
GPUIterator::GPUIterator() : m_list(nullptr), m_current(0), m_begin(true) {
}

// Parameterized constructor
GPUIterator::GPUIterator(adlx::IADLXGPUList* list, bool begin)
    : m_list(list), m_begin(begin) {
    if (list && begin) {
        m_current = list->Begin();
    } else if (list) {
        m_current = list->End();
    } else {
        m_current = 0;
    }
}

GPUIterator& GPUIterator::iter() {
    return *this;
}

adlx::IADLXGPUPtr GPUIterator::next() {
    if (!m_list || m_current >= m_list->End()) {
        throw py::stop_iteration();
    }

    adlx::IADLXGPUPtr gpu = nullptr;
    ADLX_RESULT res = m_list->At(m_current, &gpu);
    if (!ADLX_SUCCEEDED(res) || !gpu) {
        throw py::stop_iteration();
    }

    m_current++;
    return gpu;
}

adlx::IADLXGPUPtr GPUIterator::operator*() const {
    adlx::IADLXGPUPtr gpu = nullptr;
    if (m_list) {
        m_list->At(m_current, &gpu);
    }
    return gpu;
}

bool GPUIterator::operator==(const GPUIterator& other) const {
    return m_current == other.m_current;
}

bool GPUIterator::operator!=(const GPUIterator& other) const {
    return m_current != other.m_current;
}

GPUIterator& GPUIterator::operator++() {
    if (m_list && m_current < m_list->End()) {
        m_current++;
    }
    return *this;
}
