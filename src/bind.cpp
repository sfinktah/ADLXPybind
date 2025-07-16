//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

// Include pybind11 depends
// ReSharper disable CppPassValueParameterByConstReference
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>

// Include SDK depends
#include "../ADLXPybind/ADLX/SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "../ADLXPybind/ADLX/SDK/Include/ADLXDefines.h"
#include "../ADLXPybind/ADLX/SDK/Include/IDisplays.h"
#include "../ADLXPybind/ADLX/SDK/Include/IPerformanceMonitoring2.h"
#include "../ADLXPybind/ADLX/SDK/Include/IPerformanceMonitoring3.h"
#include "../ADLXPybind/ADLX/SDK/Include/ISystem2.h"


namespace py = pybind11;
using namespace adlx;

// Add this near the top of your bind.cpp file, or in a header if appropriate
// This tells pybind11 that IADLXGPUListFacade is the same as IADLXGPUList
namespace adlx {
    using IADLXGPUListFacade = IADLXGPUList;
}

// Always needed for custom holder types
PYBIND11_DECLARE_HOLDER_TYPE(T, IADLXInterfacePtr_T<T>, true);

// Only needed if the type's `.get()` goes by another name
namespace pybind11 {
    namespace detail {
        template <typename T>
            struct holder_helper<IADLXInterfacePtr_T<T>> { // <-- specialization
                static const T *get(const IADLXInterfacePtr_T<T> &p) { return p.GetPtr(); }
            };
    }
}

#include "./PySystem.h"
#include "./PyDisplayService.h"
#include "./PyDisplay.h"
#include "./PyDisplayChangeHandler.h"
#include "./PyPerformanceMonitoringServices.h"
#include "./PyGPUMetricsSupport.h"
#include "./PyGPUMetricsSupport2.h"
#include "./PyGPUMetrics.h"
#include "./PyGPUMetrics2.h"
#include "./PyGPUList.h"
#include "./PyGPU.h"
#include "./GPUIterator.h"
#include "./ADXLGPUHolder.h"

// Callback
class DisplayListCallBack : public IADLXDisplayListChangedListener
{
    public:

        adlx_bool OnDisplayListChanged(IADLXDisplayList *pNewDisplay) override {
            std::vector<IADLXDisplayPtr> list;
            for (adlx_uint s = pNewDisplay->Begin(); s != pNewDisplay->End(); s++) {
                IADLXDisplayPtr item;
                pNewDisplay->At(s, &item);
                list.emplace_back(item);
            }
            if (m_call) {
                return m_call(list);
            }
            return true;
        }

        std::function<bool(std::vector<IADLXDisplayPtr>)> m_call;
};

PYBIND11_MODULE(_adlx_pybind, m) {

    m.doc() = "ADLX python binding for display & displayListChangedEvent";
    // At the beginning of your PYBIND11_MODULE function where you define module attributes
    m.attr("IID_IADLXGPUMetricsSupport2") = py::str("IADLXGPUMetricsSupport2");
    m.attr("IID_IADLXGPUMetrics2") = py::str("IADLXGPUMetrics2");

    // Add these enums before the IADLXGPU class binding
    // Add all necessary enums before the class bindings
    py::enum_<ADLX_RESULT>(m, "ADLX_RESULT")
        .value("ADLX_OK", ADLX_RESULT::ADLX_OK)
        .value("ADLX_ALREADY_ENABLED", ADLX_RESULT::ADLX_ALREADY_ENABLED)
        .value("ADLX_ALREADY_INITIALIZED", ADLX_RESULT::ADLX_ALREADY_INITIALIZED)
        .value("ADLX_FAIL", ADLX_RESULT::ADLX_FAIL)
        .value("ADLX_INVALID_ARGS", ADLX_RESULT::ADLX_INVALID_ARGS)
        .value("ADLX_BAD_VER", ADLX_RESULT::ADLX_BAD_VER)
        .value("ADLX_UNKNOWN_INTERFACE", ADLX_RESULT::ADLX_UNKNOWN_INTERFACE)
        .value("ADLX_TERMINATED", ADLX_RESULT::ADLX_TERMINATED)
        .value("ADLX_ADL_INIT_ERROR", ADLX_RESULT::ADLX_ADL_INIT_ERROR)
        .value("ADLX_NOT_FOUND", ADLX_RESULT::ADLX_NOT_FOUND)
        .value("ADLX_INVALID_OBJECT", ADLX_RESULT::ADLX_INVALID_OBJECT)
        .value("ADLX_ORPHAN_OBJECTS", ADLX_RESULT::ADLX_ORPHAN_OBJECTS)
        .value("ADLX_NOT_SUPPORTED", ADLX_RESULT::ADLX_NOT_SUPPORTED)
        .value("ADLX_PENDING_OPERATION", ADLX_RESULT::ADLX_PENDING_OPERATION)
        .value("ADLX_GPU_INACTIVE", ADLX_RESULT::ADLX_GPU_INACTIVE)
        .value("ADLX_GPU_IN_USE", ADLX_RESULT::ADLX_GPU_IN_USE)
        .value("ADLX_TIMEOUT_OPERATION", ADLX_RESULT::ADLX_TIMEOUT_OPERATION)
        .value("ADLX_NOT_ACTIVE", ADLX_RESULT::ADLX_NOT_ACTIVE)
        .export_values();

    py::enum_<ADLX_GPU_TYPE>(m, "ADLX_GPU_TYPE")
        .value("GPUTYPE_UNDEFINED", ADLX_GPU_TYPE::GPUTYPE_UNDEFINED)
        .value("GPUTYPE_INTEGRATED", ADLX_GPU_TYPE::GPUTYPE_INTEGRATED)
        .value("GPUTYPE_DISCRETE", ADLX_GPU_TYPE::GPUTYPE_DISCRETE)
        .export_values();

    py::enum_<ADLX_ASIC_FAMILY_TYPE>(m, "ADLX_ASIC_FAMILY_TYPE")
        .value("ASIC_UNDEFINED", ADLX_ASIC_FAMILY_TYPE::ASIC_UNDEFINED)
        .value("ASIC_RADEON", ADLX_ASIC_FAMILY_TYPE::ASIC_RADEON)
        .value("ASIC_FIREPRO", ADLX_ASIC_FAMILY_TYPE::ASIC_FIREPRO)
        .value("ASIC_FIREMV", ADLX_ASIC_FAMILY_TYPE::ASIC_FIREMV)
        .value("ASIC_FIRESTREAM", ADLX_ASIC_FAMILY_TYPE::ASIC_FIRESTREAM)
        .value("ASIC_FUSION", ADLX_ASIC_FAMILY_TYPE::ASIC_FUSION)
        .value("ASIC_EMBEDDED", ADLX_ASIC_FAMILY_TYPE::ASIC_EMBEDDED)
        .export_values();

    py::enum_<ADLX_DISPLAY_TYPE>(m, "ADLX_DISPLAY_TYPE")
        .value("DISPLAY_TYPE_UNKOWN", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_UNKOWN)
        .value("DISPLAY_TYPE_MONITOR", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_MONITOR)
        .value("DISPLAY_TYPE_TELEVISION", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_TELEVISION)
        .value("DISPLAY_TYPE_LCD_PANEL", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_LCD_PANEL)
        .value("DISPLAY_TYPE_DIGITAL_FLAT_PANEL", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_DIGITAL_FLAT_PANEL)
        .value("DISPLAY_TYPE_COMPONENT_VIDEO", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_COMPONENT_VIDEO)
        .value("DISPLAY_TYPE_PROJECTOR", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_PROJECTOR)
        .export_values();

    py::enum_<ADLX_DISPLAY_CONNECTOR_TYPE>(m, "ADLX_DISPLAY_CONNECTOR_TYPE")
        .value("DISPLAY_CONTYPE_UNKNOWN", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_UNKNOWN)
        .value("DISPLAY_CONTYPE_VGA", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_VGA)
        .value("DISPLAY_CONTYPE_DVI_D", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_DVI_D)
        .value("DISPLAY_CONTYPE_DVI_I", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_DVI_I)
        .value("DISPLAY_CONTYPE_CVDONGLE_NTSC", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_CVDONGLE_NTSC)
        .value("DISPLAY_CONTYPE_CVDONGLE_JPN", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_CVDONGLE_JPN)
        .value("DISPLAY_CONTYPE_CVDONGLE_NONI2C_JPN", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_CVDONGLE_NONI2C_JPN)
        .value("DISPLAY_CONTYPE_CVDONGLE_NONI2C_NTSC", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_CVDONGLE_NONI2C_NTSC)
        .value("DISPLAY_CONTYPE_PROPRIETARY", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_PROPRIETARY)
        .value("DISPLAY_CONTYPE_HDMI_TYPE_A", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_HDMI_TYPE_A)
        .value("DISPLAY_CONTYPE_HDMI_TYPE_B", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_HDMI_TYPE_B)
        .value("DISPLAY_CONTYPE_SVIDEO", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_SVIDEO)
        .value("DISPLAY_CONTYPE_COMPOSITE", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_COMPOSITE)
        .value("DISPLAY_CONTYPE_RCA_3COMPONENT", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_RCA_3COMPONENT)
        .value("DISPLAY_CONTYPE_DISPLAYPORT", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_DISPLAYPORT)
        .value("DISPLAY_CONTYPE_EDP", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_EDP)
        .value("DISPLAY_CONTYPE_WIRELESSDISPLAY", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_WIRELESSDISPLAY)
        .value("DISPLAY_CONTYPE_USB_TYPE_C", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_USB_TYPE_C)
        .export_values();

    py::enum_<ADLX_DISPLAY_SCAN_TYPE>(m, "ADLX_DISPLAY_SCAN_TYPE")
        .value("PROGRESSIVE", ADLX_DISPLAY_SCAN_TYPE::PROGRESSIVE)
        .value("INTERLACED", ADLX_DISPLAY_SCAN_TYPE::INTERLACED)
        .export_values();

    py::enum_<ADLX_HG_TYPE>(m, "ADLX_HG_TYPE")
        .value("NONE", ADLX_HG_TYPE::NONE)
        .value("AMD", ADLX_HG_TYPE::AMD)
        .value("OTHER", ADLX_HG_TYPE::OTHER)
        .export_values();

    py::enum_<ADLX_PCI_BUS_TYPE>(m, "ADLX_PCI_BUS_TYPE")
        .value("UNDEFINED", ADLX_PCI_BUS_TYPE::UNDEFINED)
        .value("PCI", ADLX_PCI_BUS_TYPE::PCI)
        .value("AGP", ADLX_PCI_BUS_TYPE::AGP)
        .value("PCIE", ADLX_PCI_BUS_TYPE::PCIE)
        .value("PCIE_2_0", ADLX_PCI_BUS_TYPE::PCIE_2_0)
        .value("PCIE_3_0", ADLX_PCI_BUS_TYPE::PCIE_3_0)
        .value("PCIE_4_0", ADLX_PCI_BUS_TYPE::PCIE_4_0)
        .export_values();

    py::enum_<ADLX_DP_LINK_RATE>(m, "ADLX_DP_LINK_RATE")
        .value("DP_LINK_RATE_UNKNOWN", ADLX_DP_LINK_RATE::DP_LINK_RATE_UNKNOWN)
        .value("DP_LINK_RATE_RBR", ADLX_DP_LINK_RATE::DP_LINK_RATE_RBR)
        .value("DP_LINK_RATE_2_16GBPS", ADLX_DP_LINK_RATE::DP_LINK_RATE_2_16GBPS)
        .value("DP_LINK_RATE_2_43GBPS", ADLX_DP_LINK_RATE::DP_LINK_RATE_2_43GBPS)
        .value("DP_LINK_RATE_HBR", ADLX_DP_LINK_RATE::DP_LINK_RATE_HBR)
        .value("DP_LINK_RATE_4_32GBPS", ADLX_DP_LINK_RATE::DP_LINK_RATE_4_32GBPS)
        .value("DP_LINK_RATE_HBR2", ADLX_DP_LINK_RATE::DP_LINK_RATE_HBR2)
        .value("DP_LINK_RATE_HBR3", ADLX_DP_LINK_RATE::DP_LINK_RATE_HBR3)
        .value("DP_LINK_RATE_UHBR10", ADLX_DP_LINK_RATE::DP_LINK_RATE_UHBR10)
        .value("DP_LINK_RATE_UHBR13D5", ADLX_DP_LINK_RATE::DP_LINK_RATE_UHBR13D5)
        .value("DP_LINK_RATE_UHBR20", ADLX_DP_LINK_RATE::DP_LINK_RATE_UHBR20)
        .export_values();

    py::enum_<ADLX_DISPLAY_TIMING_POLARITY>(m, "ADLX_DISPLAY_TIMING_POLARITY")
        .value("POSITIVE", ADLX_DISPLAY_TIMING_POLARITY::POSITIVE)
        .value("NEGATIVE", ADLX_DISPLAY_TIMING_POLARITY::NEGATIVE)
        .export_values();

    py::enum_<ADLX_GAMUT_SPACE>(m, "ADLX_GAMUT_SPACE")
        .value("GAMUT_SPACE_CCIR_709", ADLX_GAMUT_SPACE::GAMUT_SPACE_CCIR_709)
        .value("GAMUT_SPACE_CCIR_601", ADLX_GAMUT_SPACE::GAMUT_SPACE_CCIR_601)
        .value("GAMUT_SPACE_ADOBE_RGB", ADLX_GAMUT_SPACE::GAMUT_SPACE_ADOBE_RGB)
        .value("GAMUT_SPACE_CIE_RGB", ADLX_GAMUT_SPACE::GAMUT_SPACE_CIE_RGB)
        .value("GAMUT_SPACE_CCIR_2020", ADLX_GAMUT_SPACE::GAMUT_SPACE_CCIR_2020)
        .value("GAMUT_SPACE_CUSTOM", ADLX_GAMUT_SPACE::GAMUT_SPACE_CUSTOM)
        .export_values();

    py::enum_<ADLX_WHITE_POINT>(m, "ADLX_WHITE_POINT")
        .value("WHITE_POINT_5000K", ADLX_WHITE_POINT::WHITE_POINT_5000K)
        .value("WHITE_POINT_6500K", ADLX_WHITE_POINT::WHITE_POINT_6500K)
        .value("WHITE_POINT_7500K", ADLX_WHITE_POINT::WHITE_POINT_7500K)
        .value("WHITE_POINT_9300K", ADLX_WHITE_POINT::WHITE_POINT_9300K)
        .value("WHITE_POINT_CUSTOM", ADLX_WHITE_POINT::WHITE_POINT_CUSTOM)
        .export_values();

    py::enum_<ADLX_GAMMA_TYPE>(m, "ADLX_GAMMA_TYPE")
        .value("UNKNOW", ADLX_GAMMA_TYPE::UNKNOW)
        .value("DEGAMMA_RAMP", ADLX_GAMMA_TYPE::DEGAMMA_RAMP)
        .value("REGAMMA_RAMP", ADLX_GAMMA_TYPE::REGAMMA_RAMP)
        .value("DEGAMMA_COEFFICIENTS", ADLX_GAMMA_TYPE::DEGAMMA_COEFFICIENTS)
        .value("REGAMMA_COEFFICIENTS", ADLX_GAMMA_TYPE::REGAMMA_COEFFICIENTS)
        .export_values();

    py::enum_<ADLX_ORIENTATION>(m, "ADLX_ORIENTATION")
        .value("ORIENTATION_LANDSCAPE", ADLX_ORIENTATION::ORIENTATION_LANDSCAPE)
        .value("ORIENTATION_PORTRAIT", ADLX_ORIENTATION::ORIENTATION_PORTRAIT)
        .value("ORIENTATION_LANDSCAPE_FLIPPED", ADLX_ORIENTATION::ORIENTATION_LANDSCAPE_FLIPPED)
        .value("ORIENTATION_PORTRAIT_FLIPPED", ADLX_ORIENTATION::ORIENTATION_PORTRAIT_FLIPPED)
        .export_values();

    // GPU binding
    py::class_<IADLXGPU, PyGPU, IADLXInterfacePtr_T<IADLXGPU>>(m, "IADLXGPU")
        .def(py::init<>())
        .def("Name", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            const char* name = nullptr;
            gpu->Name(&name);
            return py::str(name);
        })
        .def("DriverPath", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            const char* path = nullptr;
            gpu->DriverPath(&path);
            return py::str(path);
        })
        .def("PNPString", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            const char* pnp = nullptr;
            gpu->PNPString(&pnp);
            return py::str(pnp);
        })
        .def("HasDesktops", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            adlx_bool hasDesktops;
            gpu->HasDesktops(&hasDesktops);
            return hasDesktops != 0;
        })
        .def("TotalVRAM", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            adlx_uint vram;
            gpu->TotalVRAM(&vram);
            return vram;
        })
        .def("VRAMType", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            const char* vramType = nullptr;
            gpu->VRAMType(&vramType);
            return py::str(vramType);
        })
        .def("BIOSInfo", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            const char* biosInfo = nullptr;
            const char* biosVersion = nullptr;
            const char* biosDate = nullptr;
            gpu->BIOSInfo(&biosInfo, &biosVersion, &biosDate);
            return py::make_tuple(py::str(biosInfo), py::str(biosVersion), py::str(biosDate));
        })
        .def("DeviceId", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            const char* deviceId = nullptr;
            gpu->DeviceId(&deviceId);
            return py::str(deviceId);
        })
        .def("RevisionId", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            const char* revisionId = nullptr;
            gpu->RevisionId(&revisionId);
            return py::str(revisionId);
        })
        .def("VendorId", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            const char* vendorId = nullptr;
            gpu->VendorId(&vendorId);
            return py::str(vendorId);
        })
        .def("IsExternal", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            adlx_bool isExternal;
            gpu->IsExternal(&isExternal);
            return isExternal != 0;
        })
        .def("Type", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            ADLX_GPU_TYPE gpuType;
            gpu->Type(&gpuType);
            return gpuType;
        })
        .def("ASICFamilyType", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            ADLX_ASIC_FAMILY_TYPE asicType;
            gpu->ASICFamilyType(&asicType);
            return asicType;
        })
        .def("UniqueId", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            adlx_int uniqueId;  // Note: this is adlx_int, not adlx_uint
            gpu->UniqueId(&uniqueId);
            return uniqueId;
        })
    ;
    // Add this to your PYBIND11_MODULE function where other classes are registered
    py::class_<IADLXGPUList, PyGPUList, IADLXInterfacePtr_T<IADLXGPUList>>(m, "IADLXGPUList")
        .def(py::init<>())
        .def("Size", &IADLXGPUList::Size)
        .def("Empty", &IADLXGPUList::Empty)
        .def("Begin", &IADLXGPUList::Begin)
        .def("End", &IADLXGPUList::End)
        .def("Clear", &IADLXGPUList::Clear)
        .def("Remove_Back", &IADLXGPUList::Remove_Back)
        .def("At", [](IADLXGPUList& self, adlx_uint location) {
            IADLXGPUPtr gpu = nullptr;
            ADLX_RESULT res = self.At(location, &gpu);
            if (ADLX_SUCCEEDED(res)) {
                return gpu;
            }
            throw py::value_error("Failed to get GPU at specified location");
        }, py::return_value_policy::move)
        .def("__len__", &IADLXGPUList::Size)
        .def("__iter__", [](py::object self) {
            return py::make_iterator(
                GPUIterator(self.cast<IADLXGPUList*>(), true),
                GPUIterator(self.cast<IADLXGPUList*>(), false)
            );
        }, py::keep_alive<0, 1>());
    // And in the PYBIND11_MODULE section
    m.attr("IADLXGPUListFacade") = m.attr("IADLXGPUList");

    // Define the objects that get exposed to python

    py::class_<ADLXGPUHolder>(m, "ADLXGPUHolder")
        .def(py::init<IADLXSystem*>())
        .def("isValid", &ADLXGPUHolder::isValid)
        .def("getGPUList", &ADLXGPUHolder::getGPUList)
        .def("getGPU", &ADLXGPUHolder::getGPU);


    py::class_<GPUIterator>(m, "GPUIterator", py::dynamic_attr())
        .def("__iter__", &GPUIterator::iter)
        .def("__next__", &GPUIterator::next);

    // ADLX_helper
    py::class_<ADLXHelper>(m, "ADLXHelper")
        .def(py::init<>())
        .def("InitializeWithCallerAdl", &ADLXHelper::InitializeWithCallerAdl)
        .def("Initialize", &ADLXHelper::Initialize)
        .def("InitializeWithIncompatibleDriver", &ADLXHelper::InitializeWithIncompatibleDriver)
        .def("Terminate", &ADLXHelper::Terminate)
        .def("QueryVersion", &ADLXHelper::QueryVersion)
        .def("GetSystemServices", &ADLXHelper::GetSystemServices, py::return_value_policy::reference)
        .def("GetAdlMapping", &ADLXHelper::GetAdlMapping);

    // System
    py::class_<IADLXSystem, PySystem>(m, "IADLXSystem")
        .def(py::init<>())
        .def("GetDisplaysServices", [](py::object self) {
            IADLXSystem *sys = self.cast<IADLXSystem*>();
            IADLXDisplayServicesPtr displayService = nullptr;
            sys->GetDisplaysServices(&displayService);
            return displayService;
        }, py::return_value_policy::move)
        .def("GetGPUsEx", [](py::object self) {
            IADLXSystem* sys = self.cast<IADLXSystem*>();
            IADLXGPUListPtr gpuList;

            const auto res = sys->GetGPUs(&gpuList);
            if (!ADLX_SUCCEEDED(res) || gpuList == nullptr) {
                // Return an empty iterator
                return py::cast(new GPUIterator(), py::return_value_policy::take_ownership);
            }
            return py::cast(new GPUIterator(std::move(gpuList)), py::return_value_policy::take_ownership);
        })
        .def("GetGPUs", [](py::object self) {
            IADLXSystem* sys = self.cast<IADLXSystem*>();
            IADLXGPUListPtr gpuList = nullptr;

            // Get the GPU list from the system
            const ADLX_RESULT result = sys->GetGPUs(&gpuList);
            if (result != ADLX_OK || gpuList == nullptr) {
                return std::vector<IADLXGPUPtr>{};
            }

            // Use a container with the expected capacity to avoid reallocations
            std::vector<IADLXGPUPtr> gpus;
            const adlx_uint size = gpuList->Size();
            gpus.reserve(size);

            // Use structured binding with auto for cleaner iteration
            for (auto i = gpuList->Begin(); i != gpuList->End(); ++i) {
                IADLXGPUPtr gpu = nullptr;
                if (ADLX_SUCCEEDED(gpuList->At(i, &gpu)) && gpu) {
                    gpus.emplace_back(std::move(gpu));
                }
            }
            gpuList->Release();
            return gpus;
        }, py::return_value_policy::move)
        .def("GetNumberOfGPUs", [](py::object self) {
            IADLXSystem* sys = self.cast<IADLXSystem*>();
            IADLXGPUListPtr gpuList = nullptr;

            // Get the GPU list from the system
            const ADLX_RESULT result = sys->GetGPUs(&gpuList);
            if (result != ADLX_OK || gpuList == nullptr) {
                return (adlx_uint)0;
            }

            const adlx_uint size = gpuList->Size();
            gpuList->Release();
            return size;
        })
        .def("GetGPUByIndex", [](py::object self, const adlx_uint index) {
            IADLXSystem* sys = self.cast<IADLXSystem*>();
            IADLXGPUListPtr gpuList = nullptr;
            IADLXGPUPtr gpu;

            // Even if this code is valid, it's going to throw a huffing fit over the pointers. Not even
            // sure if `gpu` is a pointer into `gpuList`, or if we can copy it.  Perhaps return some
            // auto-destroying structure that takes care of everything?
            const ADLX_RESULT result = sys->GetGPUs(&gpuList);
            if (ADLX_SUCCEEDED(result)) {
                gpuList->At(index, &gpu);
                gpuList->Release();
            }
            return gpu;
        }, py::return_value_policy::move)

        .def("GetPerformanceMonitoringServices", [](py::object self) {
            IADLXSystem* sys = self.cast<IADLXSystem*>();
            IADLXPerformanceMonitoringServicesPtr perfService;
            sys->GetPerformanceMonitoringServices(&perfService);
            return perfService;
        }, py::return_value_policy::move)
    ;

    // displayService
    py::class_<IADLXDisplayServices, PyDisplayService, IADLXInterfacePtr_T<IADLXDisplayServices>>(m, "IADLXDisplayServices")
        .def(py::init<>())
        .def("GetNumberOfDisplays", [](py::object self) {
            IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
            adlx_uint num;
            disService->GetNumberOfDisplays(&num);
            return num;
        })
        .def("GetDisplays", [](py::object self) {
            IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
            IADLXDisplayListPtr displayList = nullptr;
            disService->GetDisplays(&displayList);
            if (displayList == nullptr) {
                return std::vector<IADLXDisplayPtr>{};
            }
            std::vector<IADLXDisplayPtr> list;
            for (adlx_uint s = displayList->Begin(); s != displayList->End(); s++) {
                IADLXDisplayPtr item;
                displayList->At(s, &item);
                list.emplace_back(std::move(item));
            }
            return list;
        }, py::return_value_policy::move)
        .def("GetDisplayChangedHandling", [](py::object self) {
            IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
            IADLXDisplayChangedHandlingPtr handler;
            disService->GetDisplayChangedHandling(&handler);
            return handler;
        }, py::return_value_policy::move)
    ;

    // Display
    py::class_<IADLXDisplay, PyDisplay, IADLXInterfacePtr_T<IADLXDisplay>>(m, "IADLXDisplay")
        .def(py::init<>())
        .def("name", [](py::object self) {
            const IADLXDisplay *display = self.cast<IADLXDisplay*>();
            const char *name = nullptr;
            display->Name(&name);
            return py::str(name);
        })
        .def("type", [](py::object self) {
            const IADLXDisplay *display = self.cast<IADLXDisplay*>();
            ADLX_DISPLAY_TYPE type;
            display->DisplayType(&type);
            return type;
        })
        .def("connectType", [](py::object self) {
            const IADLXDisplay *display = self.cast<IADLXDisplay*>();
            ADLX_DISPLAY_CONNECTOR_TYPE type;
            display->ConnectorType(&type);
            return type;
        })
        .def("ManufacturerID", [](py::object self) {
            const IADLXDisplay *display = self.cast<IADLXDisplay*>();
            adlx_uint id;
            display->ManufacturerID(&id);
            return id;
        })
        .def("EDID", [](py::object self) {
            const IADLXDisplay *display = self.cast<IADLXDisplay*>();
            const char* str = nullptr;
            display->EDID(&str);
            return std::string(str);
        })
        .def("resolution", [](py::object self) {
            const IADLXDisplay *display = self.cast<IADLXDisplay*>();
            adlx_int h, v;
            display->NativeResolution(&h, &v);
            return std::tuple<adlx_int, adlx_int>(h,v);
        })
        .def("RefreshRate", [](py::object self) {
            const IADLXDisplay *display = self.cast<IADLXDisplay*>();
            adlx_double value;
            display->RefreshRate(&value);
            return value;
        })
        .def("PixelClock", [](py::object self) {
            const IADLXDisplay *display = self.cast<IADLXDisplay*>();
            adlx_uint value;
            display->PixelClock(&value);
            return value;
        })
        .def("ScanType", [](py::object self) {
            const IADLXDisplay *display = self.cast<IADLXDisplay*>();
            ADLX_DISPLAY_SCAN_TYPE type;
            display->ScanType(&type);
            return type;
        })
        .def("UniqueId", [](py::object self) {
            IADLXDisplay* display = self.cast<IADLXDisplay*>();  // Correct cast to IADLXDisplay
            adlx_size uniqueId;  // Correct type (adlx_size, not adlx_int)
            display->UniqueId(&uniqueId);
            return uniqueId;
        })
        // Add this to the IADLXDisplay class binding
        .def("GetGPU", [](py::object self) {
             IADLXDisplay* display = self.cast<IADLXDisplay*>();
             IADLXGPUPtr gpu = nullptr;  // Properly declare the variable
             display->GetGPU(&gpu);
             return gpu;
         }, py::return_value_policy::move)
    ;

    // Display change handler
    py::class_<IADLXDisplayChangedHandling, PyDisplayChangeHandler, IADLXInterfacePtr_T<IADLXDisplayChangedHandling>>(m, "IADLXDisplayChangedHandling")
        .def(py::init<>())
        .def("AddDisplayListEventListener", [](py::object self, DisplayListCallBack* call) {
            IADLXDisplayChangedHandling *handler = self.cast<IADLXDisplayChangedHandling*>();
            return handler->AddDisplayListEventListener(call);
        })
        .def("RemoveDisplayListEventListener", [](py::object self, DisplayListCallBack* call) {
            IADLXDisplayChangedHandling *handler = self.cast<IADLXDisplayChangedHandling*>();
            return handler->RemoveDisplayListEventListener(call);
        })
    ;

    // Callback for displaylist
    py::class_<DisplayListCallBack>(m, "DisplayListCallBack")
        .def(py::init<>())
        .def_readwrite("call", &DisplayListCallBack::m_call);


    // GPU Metrics Support binding
    py::class_<IADLXGPUMetricsSupport, PyGPUMetricsSupport, IADLXInterfacePtr_T<IADLXGPUMetricsSupport>>(m, "IADLXGPUMetricsSupport")
        .def(py::init<>())
//        .def("QueryInterface", [](py::object self, const std::string& interfaceId) -> py::object {
//            try {
//                IADLXInterface* obj = self.cast<IADLXInterface*>();
//                if (interfaceId == "IADLXGPUMetricsSupport2") {
//                    IADLXGPUMetricsSupport2* support2 = nullptr;
//                    ADLX_RESULT res = obj->QueryInterface(L"IADLXGPUMetricsSupport2", reinterpret_cast<void**>(&support2));
//                    if (res == ADLX_OK && support2 != nullptr) {
//                        // Create and return a Python object from the C++ pointer
//                        return py::cast(support2, py::return_value_policy::take_ownership);
//                    }
//                }
//                // Return None for any other interface ID or if the query failed
//                return py::none();
//            }
//            catch (const std::exception&) {
//                // On error, also return None
//                return py::none();
//            }
//        })
        .def("IsSupportedGPUUsage", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_bool supported;
            support->IsSupportedGPUUsage(&supported);
            return supported != 0;
        })
        .def("IsSupportedGPUClockSpeed", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_bool supported;
            support->IsSupportedGPUClockSpeed(&supported);
            return supported != 0;
        })
        .def("IsSupportedGPUVRAMClockSpeed", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_bool supported;
            support->IsSupportedGPUVRAMClockSpeed(&supported);
            return supported != 0;
        })
        .def("IsSupportedGPUTemperature", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_bool supported;
            support->IsSupportedGPUTemperature(&supported);
            return supported != 0;
        })
        .def("IsSupportedGPUHotspotTemperature", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_bool supported;
            support->IsSupportedGPUHotspotTemperature(&supported);
            return supported != 0;
        })
        .def("IsSupportedGPUPower", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_bool supported;
            support->IsSupportedGPUPower(&supported);
            return supported != 0;
        })
        .def("IsSupportedGPUTotalBoardPower", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_bool supported;
            support->IsSupportedGPUTotalBoardPower(&supported);
            return supported != 0;
        })
        .def("IsSupportedGPUFanSpeed", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_bool supported;
            support->IsSupportedGPUFanSpeed(&supported);
            return supported != 0;
        })
        .def("IsSupportedGPUVRAM", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_bool supported;
            support->IsSupportedGPUVRAM(&supported);
            return supported != 0;
        })
        .def("IsSupportedGPUVoltage", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_bool supported;
            support->IsSupportedGPUVoltage(&supported);
            return supported != 0;
        })
        .def("IsSupportedGPUIntakeTemperature", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_bool supported;
            support->IsSupportedGPUIntakeTemperature(&supported);
            return supported != 0;
        })
        .def("GetGPUUsageRange", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_int minValue, maxValue;
            support->GetGPUUsageRange(&minValue, &maxValue);
            return py::make_tuple(minValue, maxValue);
        })
        .def("GetGPUClockSpeedRange", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_int minValue, maxValue;
            support->GetGPUClockSpeedRange(&minValue, &maxValue);
            return py::make_tuple(minValue, maxValue);
        })
        .def("GetGPUVRAMClockSpeedRange", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_int minValue, maxValue;
            support->GetGPUVRAMClockSpeedRange(&minValue, &maxValue);
            return py::make_tuple(minValue, maxValue);
        })
        .def("GetGPUTemperatureRange", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_int minValue, maxValue;
            support->GetGPUTemperatureRange(&minValue, &maxValue);
            return py::make_tuple(minValue, maxValue);
        })
        .def("GetGPUHotspotTemperatureRange", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_int minValue, maxValue;
            support->GetGPUHotspotTemperatureRange(&minValue, &maxValue);
            return py::make_tuple(minValue, maxValue);
        })
        .def("GetGPUPowerRange", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_int minValue, maxValue;
            support->GetGPUPowerRange(&minValue, &maxValue);
            return py::make_tuple(minValue, maxValue);
        })
        .def("GetGPUTotalBoardPowerRange", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_int minValue, maxValue;
            support->GetGPUTotalBoardPowerRange(&minValue, &maxValue);
            return py::make_tuple(minValue, maxValue);
        })
        .def("GetGPUFanSpeedRange", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_int minValue, maxValue;
            support->GetGPUFanSpeedRange(&minValue, &maxValue);
            return py::make_tuple(minValue, maxValue);
        })
        .def("GetGPUVRAMRange", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_int minValue, maxValue;
            support->GetGPUVRAMRange(&minValue, &maxValue);
            return py::make_tuple(minValue, maxValue);
        })
        .def("GetGPUVoltageRange", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_int minValue, maxValue;
            support->GetGPUVoltageRange(&minValue, &maxValue);
            return py::make_tuple(minValue, maxValue);
        })
        .def("GetGPUIntakeTemperatureRange", [](py::object self) {
            IADLXGPUMetricsSupport* support = self.cast<IADLXGPUMetricsSupport*>();
            adlx_int minValue, maxValue;
            support->GetGPUIntakeTemperatureRange(&minValue, &maxValue);
            return py::make_tuple(minValue, maxValue);
        })
        .def("GetGPUSharedMemoryRange", [](py::object self) -> py::object {
            // Use auto for type deduction
            auto* support = self.cast<IADLXGPUMetricsSupport*>();
            if (!support) {
                return py::none();
            }

            // Use the string literal directly
            IADLXGPUMetricsSupport2* gpuMetricsSupport2;
            const auto queryResult = support->QueryInterface(
                L"IADLXGPUMetricsSupport2",
                reinterpret_cast<void**>(&gpuMetricsSupport2)
            );

            // Use RAII with a custom scope
            if (queryResult == ADLX_OK && gpuMetricsSupport2) {
                // Use RAII with smart pointer semantics for automatic cleanup
                struct ReleaseGuard {
                    IADLXGPUMetricsSupport2* ptr;
                    ~ReleaseGuard() { if (ptr) ptr->Release(); }
                } guard{gpuMetricsSupport2};

                // Get range values
                adlx_int minValue = 0, maxValue = 0;
                const auto rangeResult = gpuMetricsSupport2->GetGPUSharedMemoryRange(&minValue, &maxValue);

                // Return tuple if successful
                if (ADLX_SUCCEEDED(rangeResult)) {
                    return py::make_tuple(minValue, maxValue);
                }
            }

            return py::none();
        })
    ;

    // For IADLXGPUMetricsSupport2
    py::class_<IADLXGPUMetricsSupport2, PyGPUMetricsSupport2, IADLXInterfacePtr_T<IADLXGPUMetricsSupport2>>(m, "IADLXGPUMetricsSupport2")
        .def("IsSupportedGPUSharedMemory", [](IADLXGPUMetricsSupport2& self) {
            adlx_bool supported = false;
            self.IsSupportedGPUSharedMemory(&supported);
            return supported != 0;
        })
        .def("GetGPUSharedMemoryRange", [](IADLXGPUMetricsSupport2& self) {
            adlx_int minValue = 0, maxValue = 0;
            self.GetGPUSharedMemoryRange(&minValue, &maxValue);
            return py::make_tuple(minValue, maxValue);
        });

    // For IADLXGPUMetrics2
    py::class_<IADLXGPUMetrics2, PyGPUMetrics2, IADLXInterfacePtr_T<IADLXGPUMetrics2>>(m, "IADLXGPUMetrics2")
        .def("GPUSharedMemory", [](IADLXGPUMetrics2& self) {
            adlx_int memory = 0;
            self.GPUSharedMemory(&memory);
            return memory;
        });;

    py::class_<IADLXGPUMetrics, PyGPUMetrics, IADLXInterfacePtr_T<IADLXGPUMetrics>>(m, "IADLXGPUMetrics")
        .def(py::init<>())
        // Add this method to properly expose Release
        .def("Release", [](py::object self) -> adlx_long {
            if (auto* metrics = self.cast<IADLXGPUMetrics*>()) {
                return metrics->Release();
            }
            return 0;
        })
        .def("QueryInterface", [](py::object self, const std::string& interfaceId) {
            try {
                IADLXGPUMetrics* metrics = self.cast<IADLXGPUMetrics*>();
                if (interfaceId == "IADLXGPUMetrics2") {
                    // For now, just return None as this interface isn't properly bound yet
                    return py::none();  // This returns a py::object
                }
                // Return None for any other interface ID
                return py::none();  // This returns a py::object
            }
            catch (const std::exception& e) {
                // On error, also return None
                return py::none();  // This returns a py::object
            }
        })
        .def("TimeStamp", [](py::object self) {
            IADLXGPUMetrics* metrics = self.cast<IADLXGPUMetrics*>();
            adlx_int64 timestamp;
            metrics->TimeStamp(&timestamp);
            return timestamp;
        })
        .def("GPUUsage", [](py::object self) {
            IADLXGPUMetrics* metrics = self.cast<IADLXGPUMetrics*>();
            adlx_double usage;
            metrics->GPUUsage(&usage);
            return usage;
        })
        .def("GPUClockSpeed", [](py::object self) {
            IADLXGPUMetrics* metrics = self.cast<IADLXGPUMetrics*>();
            adlx_int clockSpeed;
            metrics->GPUClockSpeed(&clockSpeed);
            return clockSpeed;
        })
        .def("GPUVRAMClockSpeed", [](py::object self) {
            IADLXGPUMetrics* metrics = self.cast<IADLXGPUMetrics*>();
            adlx_int vramClock;
            metrics->GPUVRAMClockSpeed(&vramClock);
            return vramClock;
        })
        .def("GPUTemperature", [](py::object self) {
            IADLXGPUMetrics* metrics = self.cast<IADLXGPUMetrics*>();
            adlx_double temp;
            metrics->GPUTemperature(&temp);
            return temp;
        })
        .def("GPUHotspotTemperature", [](py::object self) {
            IADLXGPUMetrics* metrics = self.cast<IADLXGPUMetrics*>();
            adlx_double temp;
            metrics->GPUHotspotTemperature(&temp);
            return temp;
        })
        .def("GPUPower", [](py::object self) {
            IADLXGPUMetrics* metrics = self.cast<IADLXGPUMetrics*>();
            adlx_double power;
            metrics->GPUPower(&power);
            return power;
        })
        .def("GPUTotalBoardPower", [](py::object self) {
            IADLXGPUMetrics* metrics = self.cast<IADLXGPUMetrics*>();
            adlx_double power;
            metrics->GPUTotalBoardPower(&power);
            return power;
        })
        .def("GPUIntakeTemperature", [](py::object self) {
            IADLXGPUMetrics* metrics = self.cast<IADLXGPUMetrics*>();
            adlx_double temp;
            metrics->GPUIntakeTemperature(&temp);
            return temp;
        })
        .def("GPUVRAM", [](py::object self) {
            IADLXGPUMetrics* metrics = self.cast<IADLXGPUMetrics*>();
            adlx_int vram;
            metrics->GPUVRAM(&vram);
            return vram;
        })
        .def("GPUVoltage", [](py::object self) {
            IADLXGPUMetrics* metrics = self.cast<IADLXGPUMetrics*>();
            adlx_int voltage;
            metrics->GPUVoltage(&voltage);
            return voltage;
        })
        .def("GPUFanSpeed", [](py::object self) {
            IADLXGPUMetrics* metrics = self.cast<IADLXGPUMetrics*>();
            adlx_int fanSpeed;
            metrics->GPUFanSpeed(&fanSpeed);
            return fanSpeed;
        })
        .def("GPUSharedMemory", [](py::object self) -> py::object {
               // Try to get the metrics object
               IADLXGPUMetrics* metrics = self.cast<IADLXGPUMetrics*>();
               if (!metrics) {
                   return py::none();
               }

               // Try to query for the IADLXGPUMetrics2 interface
               IADLXGPUMetrics2* metrics2;
               ADLX_RESULT res = metrics->QueryInterface(L"IADLXGPUMetrics2", reinterpret_cast<void**>(&metrics2));

               // If we successfully got the interface and it's not null
               if (res == ADLX_OK) {
                   // Get the shared memory value
                   adlx_int memory = 0;
                   res = metrics2->GPUSharedMemory(&memory);

                   // Release the interface when done
                   metrics2->Release();

                   // If we successfully got the memory value, return it
                   if (res == ADLX_OK) {
                       return py::cast(memory);
                   }
               }

               // If any step failed, return None
               return py::none();
           })
    ;

    // Performance Monitoring Services binding
    py::class_<IADLXPerformanceMonitoringServices, PyPerformanceMonitoringServices, IADLXInterfacePtr_T<IADLXPerformanceMonitoringServices>>(m, "IADLXPerformanceMonitoringServices")
        .def(py::init<>())
        .def("Release", [](py::object self) {
            IADLXPerformanceMonitoringServices* services = self.cast<IADLXPerformanceMonitoringServices*>();
            if (services) {
                return services->Release();
            }
            return static_cast<adlx_long>(0);
        })
        .def("GetSamplingIntervalRange", [](py::object self) {
            IADLXPerformanceMonitoringServices* services = self.cast<IADLXPerformanceMonitoringServices*>();
            ADLX_IntRange range;
            services->GetSamplingIntervalRange(&range);
            return py::make_tuple(range.minValue, range.maxValue, range.step);
        })
        .def("SetSamplingInterval", [](py::object self, const adlx_int interval) {
            IADLXPerformanceMonitoringServices* services = self.cast<IADLXPerformanceMonitoringServices*>();
            return services->SetSamplingInterval(interval);
        })
        .def("GetSamplingInterval", [](py::object self) {
            IADLXPerformanceMonitoringServices* services = self.cast<IADLXPerformanceMonitoringServices*>();
            adlx_int interval;
            services->GetSamplingInterval(&interval);
            return interval;
        })
        .def("GetMaxPerformanceMetricsHistorySizeRange", [](py::object self) {
            IADLXPerformanceMonitoringServices* services = self.cast<IADLXPerformanceMonitoringServices*>();
            ADLX_IntRange range;
            services->GetMaxPerformanceMetricsHistorySizeRange(&range);
            return py::make_tuple(range.minValue, range.maxValue, range.step);
        })
        .def("SetMaxPerformanceMetricsHistorySize", [](py::object self, const adlx_int sizeMB) {
            IADLXPerformanceMonitoringServices* services = self.cast<IADLXPerformanceMonitoringServices*>();
            return services->SetMaxPerformanceMetricsHistorySize(sizeMB);
        })
        .def("GetMaxPerformanceMetricsHistorySize", [](py::object self) {
            IADLXPerformanceMonitoringServices* services = self.cast<IADLXPerformanceMonitoringServices*>();
            adlx_int sizeMB;
            services->GetMaxPerformanceMetricsHistorySize(&sizeMB);
            return sizeMB;
        })
        .def("GetCurrentPerformanceMetricsHistorySize", [](py::object self) {
            IADLXPerformanceMonitoringServices* services = self.cast<IADLXPerformanceMonitoringServices*>();
            adlx_int sizeMB;
            services->GetCurrentPerformanceMetricsHistorySize(&sizeMB);
            return sizeMB;
        })
        .def("GetSupportedGPUMetrics", [](py::object self, py::object gpu) {
            IADLXPerformanceMonitoringServices* services = self.cast<IADLXPerformanceMonitoringServices*>();
            IADLXGPU* gpuPtr = gpu.cast<IADLXGPU*>();
            IADLXGPUMetricsSupportPtr support;
            services->GetSupportedGPUMetrics(gpuPtr, &support);
            return support;
        }, py::return_value_policy::move)
        .def("GetCurrentGPUMetrics", [](py::object self, py::object gpu) {
            IADLXPerformanceMonitoringServices* services = self.cast<IADLXPerformanceMonitoringServices*>();
            IADLXGPU* gpuPtr = gpu.cast<IADLXGPU*>();
            IADLXGPUMetricsPtr metrics;
            services->GetCurrentGPUMetrics(gpuPtr, &metrics);
            return metrics;
        }, py::return_value_policy::move)
        .def("StartPerformanceMetricsTracking", [](py::object self) {
            IADLXPerformanceMonitoringServices* services = self.cast<IADLXPerformanceMonitoringServices*>();
            return services->StartPerformanceMetricsTracking();
        })
        .def("StopPerformanceMetricsTracking", [](py::object self) {
            IADLXPerformanceMonitoringServices* services = self.cast<IADLXPerformanceMonitoringServices*>();
            return services->StopPerformanceMetricsTracking();
        })
        .def("ClearPerformanceMetricsHistory", [](py::object self) {
            IADLXPerformanceMonitoringServices* services = self.cast<IADLXPerformanceMonitoringServices*>();
            return services->ClearPerformanceMetricsHistory();
        })
        .def("GetSupportedGPUMetrics2", [](py::object self, py::object gpu) {
            // Most likely the functions ending in 2 do not work correctly, they're a real pain to code.
            IADLXPerformanceMonitoringServices* perfService = self.cast<IADLXPerformanceMonitoringServices*>();
            IADLXGPU* gpuObj = gpu.cast<IADLXGPU*>();
            IADLXGPUMetricsSupport2* metricsSupport;

            // Get metrics support using QueryInterface
            IADLXGPUMetricsSupport* baseSupport;
            ADLX_RESULT res = perfService->GetSupportedGPUMetrics(gpuObj, &baseSupport);
            if (res != ADLX_OK) {
                throw std::runtime_error("Failed to get GPU metrics support");
            }

            // QueryInterface for IADLXGPUMetricsSupport2
            res = baseSupport->QueryInterface(L"IADLXGPUMetricsSupport2", reinterpret_cast<void**>(&metricsSupport));
            baseSupport->Release();

            if (res != ADLX_OK) {
                throw std::runtime_error("GPU metrics support 2 not available");
            }

            return py::cast(metricsSupport);
        })
        .def("GetCurrentGPUMetrics2", [](py::object self, py::object gpu) {
            // Most likely the functions ending in 2 do not work correctly, they're a real pain to code.
            IADLXPerformanceMonitoringServices* perfService = self.cast<IADLXPerformanceMonitoringServices*>();
            IADLXGPU* gpuObj = gpu.cast<IADLXGPU*>();
            IADLXGPUMetrics2* metrics;

            // Get metrics using QueryInterface
            IADLXGPUMetrics* baseMetrics;
            ADLX_RESULT res = perfService->GetCurrentGPUMetrics(gpuObj, &baseMetrics);
            if (res != ADLX_OK) {
                throw std::runtime_error("Failed to get current GPU metrics");
            }

            // QueryInterface for IADLXGPUMetrics2
            res = baseMetrics->QueryInterface(L"IADLXGPUMetrics2", reinterpret_cast<void**>(&metrics));
            baseMetrics->Release();

            if (res != ADLX_OK) {
                throw std::runtime_error("GPU metrics 2 not available");
            }

            return py::cast(metrics);
        })
    ;
}
