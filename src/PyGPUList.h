// GPU List Python class definition
class PyGPUList : public IADLXGPUList
{
public:
    using IADLXGPUList::IADLXGPUList;

    // IADLXInterface methods
    adlx_long Acquire() override {
        PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
    }

    adlx_long Release() override {
        PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
    }

    ADLX_RESULT QueryInterface(const wchar_t* interfaceId, void** ppInterface) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
    }

    // IADLXList methods
    adlx_uint Size() override {
        PYBIND11_OVERRIDE_PURE(adlx_uint, IADLXList, Size);
    }

    adlx_bool Empty() override {
        PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXList, Empty);
    }

    adlx_uint Begin() override {
        PYBIND11_OVERRIDE_PURE(adlx_uint, IADLXList, Begin);
    }

    adlx_uint End() override {
        PYBIND11_OVERRIDE_PURE(adlx_uint, IADLXList, End);
    }

    ADLX_RESULT At(const adlx_uint location, IADLXInterface** ppItem) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXList, At);
    }

    ADLX_RESULT Clear() override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXList, Clear);
    }

    ADLX_RESULT Remove_Back() override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXList, Remove_Back);
    }

    ADLX_RESULT Add_Back(IADLXInterface* pItem) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXList, Add_Back);
    }

    // IADLXGPUList methods
    ADLX_RESULT At(const adlx_uint location, IADLXGPU** ppItem) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUList, At);
    }

    ADLX_RESULT Add_Back(IADLXGPU* pItem) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUList, Add_Back);
    }
};