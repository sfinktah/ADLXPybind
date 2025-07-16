// GPU Metrics Support Python class definition
class PyGPUMetricsSupport : public IADLXGPUMetricsSupport
{
public:
    using IADLXGPUMetricsSupport::IADLXGPUMetricsSupport;

    adlx_long Acquire() override {
        PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
    }

    adlx_long Release() override {
        PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
    }

    ADLX_RESULT QueryInterface(const wchar_t* interfaceId, void** ppInterface) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
    }

    ADLX_RESULT IsSupportedGPUUsage(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUUsage);
    }

    ADLX_RESULT IsSupportedGPUClockSpeed(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUClockSpeed);
    }

    ADLX_RESULT IsSupportedGPUVRAMClockSpeed(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUVRAMClockSpeed);
    }

    ADLX_RESULT IsSupportedGPUTemperature(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUTemperature);
    }

    ADLX_RESULT IsSupportedGPUHotspotTemperature(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUHotspotTemperature);
    }

    ADLX_RESULT IsSupportedGPUPower(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUPower);
    }

    ADLX_RESULT IsSupportedGPUTotalBoardPower(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUTotalBoardPower);
    }

    ADLX_RESULT IsSupportedGPUFanSpeed(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUFanSpeed);
    }

    ADLX_RESULT IsSupportedGPUVRAM(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUVRAM);
    }

    ADLX_RESULT IsSupportedGPUVoltage(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUVoltage);
    }

    ADLX_RESULT IsSupportedGPUIntakeTemperature(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUIntakeTemperature);
    }

    ADLX_RESULT GetGPUUsageRange(adlx_int* minValue, adlx_int* maxValue) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUUsageRange);
    }

    ADLX_RESULT GetGPUClockSpeedRange(adlx_int* minValue, adlx_int* maxValue) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUClockSpeedRange);
    }

    ADLX_RESULT GetGPUVRAMClockSpeedRange(adlx_int* minValue, adlx_int* maxValue) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUVRAMClockSpeedRange);
    }

    ADLX_RESULT GetGPUTemperatureRange(adlx_int* minValue, adlx_int* maxValue) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUTemperatureRange);
    }

    ADLX_RESULT GetGPUHotspotTemperatureRange(adlx_int* minValue, adlx_int* maxValue) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUHotspotTemperatureRange);
    }

    ADLX_RESULT GetGPUPowerRange(adlx_int* minValue, adlx_int* maxValue) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUPowerRange);
    }

    ADLX_RESULT GetGPUTotalBoardPowerRange(adlx_int* minValue, adlx_int* maxValue) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUTotalBoardPowerRange);
    }

    ADLX_RESULT GetGPUFanSpeedRange(adlx_int* minValue, adlx_int* maxValue) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUFanSpeedRange);
    }

    ADLX_RESULT GetGPUVRAMRange(adlx_int* minValue, adlx_int* maxValue) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUVRAMRange);
    }

    ADLX_RESULT GetGPUVoltageRange(adlx_int* minValue, adlx_int* maxValue) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUVoltageRange);
    }

    ADLX_RESULT GetGPUIntakeTemperatureRange(adlx_int* minValue, adlx_int* maxValue) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUIntakeTemperatureRange);
    }
};
