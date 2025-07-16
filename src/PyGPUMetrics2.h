// GPU Metrics2 Python class definition
class PyGPUMetrics2 : public IADLXGPUMetrics2
{
public:
    using IADLXGPUMetrics2::IADLXGPUMetrics2;

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
    
    // IADLXGPUMetrics methods (inherited)
    ADLX_RESULT TimeStamp(adlx_int64* time) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, TimeStamp);
    }

    ADLX_RESULT GPUUsage(adlx_double* usage) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUUsage);
    }

    ADLX_RESULT GPUClockSpeed(adlx_int* clockSpeed) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUClockSpeed);
    }

    ADLX_RESULT GPUVRAMClockSpeed(adlx_int* clockSpeed) override {
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

    ADLX_RESULT GPUFanSpeed(adlx_int* fanSpeed) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUFanSpeed);
    }

    ADLX_RESULT GPUVRAM(adlx_int* vram) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUVRAM);
    }

    ADLX_RESULT GPUVoltage(adlx_int* voltage) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUVoltage);
    }

    ADLX_RESULT GPUIntakeTemperature(adlx_double* temperature) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics, GPUIntakeTemperature);
    }

    // IADLXGPUMetrics1 methods (if needed)
    ADLX_RESULT GPUMemoryTemperature(adlx_double* temperature) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics1, GPUMemoryTemperature);
    }

    ADLX_RESULT NPUFrequency(adlx_int* frequency) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics1, NPUFrequency);
    }

    ADLX_RESULT NPUActivityLevel(adlx_int* level) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics1, NPUActivityLevel);
    }

    // IADLXGPUMetrics2 methods
    ADLX_RESULT GPUSharedMemory(adlx_int* memory) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics2, GPUSharedMemory);
    }
};