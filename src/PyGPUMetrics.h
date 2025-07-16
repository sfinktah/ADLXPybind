// GPU Metrics Python class definition
class PyGPUMetrics : public IADLXGPUMetrics
{
public:
    using IADLXGPUMetrics::IADLXGPUMetrics;

    adlx_long Acquire() override {
        PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
    }

    adlx_long Release() override {
        PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
    }

    ADLX_RESULT QueryInterface(const wchar_t* interfaceId, void** ppInterface) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
    }

    ADLX_RESULT TimeStamp(adlx_int64* ms) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, TimeStamp);
    }

    ADLX_RESULT GPUUsage(adlx_double* usage) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUUsage);
    }

    ADLX_RESULT GPUClockSpeed(adlx_int* gpuClock) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUClockSpeed);
    }

    ADLX_RESULT GPUVRAMClockSpeed(adlx_int* vramClock) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUVRAMClockSpeed);
    }

    ADLX_RESULT GPUTemperature(adlx_double* temperature) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUTemperature);
    }

    ADLX_RESULT GPUHotspotTemperature(adlx_double* temperature) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUHotspotTemperature);
    }

    ADLX_RESULT GPUPower(adlx_double* power) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUPower);
    }

    ADLX_RESULT GPUTotalBoardPower(adlx_double* power) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUTotalBoardPower);
    }

    ADLX_RESULT GPUIntakeTemperature(adlx_double* temperature) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUIntakeTemperature);
    }

    ADLX_RESULT GPUFanSpeed(adlx_int* fanSpeed) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUFanSpeed);
    }

    ADLX_RESULT GPUVRAM(adlx_int* vram) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUVRAM);
    }

    ADLX_RESULT GPUVoltage(adlx_int* voltage) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUVoltage);
    }
};
