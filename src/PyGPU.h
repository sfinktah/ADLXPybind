// GPU Python class definition
class PyGPU : public IADLXGPU
{
public:
    using IADLXGPU::IADLXGPU;

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

    // IADLXGPU methods
    ADLX_RESULT VendorId(const char** vendorId) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, VendorId);
    }

    ADLX_RESULT ASICFamilyType(ADLX_ASIC_FAMILY_TYPE* asicFamilyType) const override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, ASICFamilyType);
    }

    ADLX_RESULT Type(ADLX_GPU_TYPE* gpuType) const override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, Type);
    }

    ADLX_RESULT IsExternal(adlx_bool* isExternal) const override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, IsExternal);
    }

    ADLX_RESULT Name(const char** name) const override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, Name);
    }

    ADLX_RESULT DriverPath(const char** driverPath) const override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, DriverPath);
    }

    ADLX_RESULT PNPString(const char** pnpString) const override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, PNPString);
    }

    ADLX_RESULT HasDesktops(adlx_bool* hasDesktops) const override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, HasDesktops);
    }

    ADLX_RESULT TotalVRAM(adlx_uint* vramMB) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, TotalVRAM);
    }

    ADLX_RESULT VRAMType(const char** type) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, VRAMType);
    }

    ADLX_RESULT BIOSInfo(const char** partNumber, const char** version, const char** date) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, BIOSInfo);
    }

    ADLX_RESULT DeviceId(const char** deviceId) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, DeviceId);
    }

    ADLX_RESULT RevisionId(const char** revisionId) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, RevisionId);
    }

    ADLX_RESULT SubSystemId(const char** subSystemId) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, SubSystemId);
    }

    ADLX_RESULT SubSystemVendorId(const char** subSystemVendorId) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, SubSystemVendorId);
    }

    ADLX_RESULT UniqueId(adlx_int* uniqueId) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, UniqueId);
    }
};