// PerformanceMonitoringServices Python class definition
class PyPerformanceMonitoringServices : public IADLXPerformanceMonitoringServices
{
public:
    using IADLXPerformanceMonitoringServices::IADLXPerformanceMonitoringServices;

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

    // IADLXPerformanceMonitoringServices methods
    ADLX_RESULT GetSamplingIntervalRange(ADLX_IntRange* range) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetSamplingIntervalRange);
    }

    ADLX_RESULT SetSamplingInterval(adlx_int intervalMs) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, SetSamplingInterval);
    }

    ADLX_RESULT GetSamplingInterval(adlx_int* intervalMs) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetSamplingInterval);
    }

    ADLX_RESULT GetMaxPerformanceMetricsHistorySizeRange(ADLX_IntRange* range) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetMaxPerformanceMetricsHistorySizeRange);
    }

    ADLX_RESULT SetMaxPerformanceMetricsHistorySize(adlx_int sizeMB) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, SetMaxPerformanceMetricsHistorySize);
    }

    ADLX_RESULT GetMaxPerformanceMetricsHistorySize(adlx_int* sizeMB) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetMaxPerformanceMetricsHistorySize);
    }

    ADLX_RESULT GetCurrentPerformanceMetricsHistorySize(adlx_int* sizeMB) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetCurrentPerformanceMetricsHistorySize);
    }

    ADLX_RESULT GetSupportedGPUMetrics(IADLXGPU* pGPU, IADLXGPUMetricsSupport** ppMetricsSupport) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetSupportedGPUMetrics);
    }

    ADLX_RESULT GetCurrentGPUMetrics(IADLXGPU* pGPU, IADLXGPUMetrics** ppMetrics) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetCurrentGPUMetrics);
    }

    ADLX_RESULT GetGPUMetricsHistory(IADLXGPU* pGPU, adlx_int startPositionMs, adlx_int endPositionMs, IADLXGPUMetricsList** ppMetricsList) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetGPUMetricsHistory);
    }

    ADLX_RESULT GetAllMetricsHistory(adlx_int startPositionMs, adlx_int endPositionMs, IADLXAllMetricsList** ppMetricsList) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetAllMetricsHistory);
    }

    ADLX_RESULT GetCurrentAllMetrics(IADLXAllMetrics** ppMetrics) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetCurrentAllMetrics);
    }

    ADLX_RESULT GetFPSHistory(adlx_int startPositionMs, adlx_int endPositionMs, IADLXFPSList** ppFPSList) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetFPSHistory);
    }

    ADLX_RESULT GetCurrentFPS(IADLXFPS** ppFPS) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetCurrentFPS);
    }

    ADLX_RESULT StartPerformanceMetricsTracking() override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, StartPerformanceMetricsTracking);
    }

    ADLX_RESULT StopPerformanceMetricsTracking() override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, StopPerformanceMetricsTracking);
    }

    ADLX_RESULT ClearPerformanceMetricsHistory() override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, ClearPerformanceMetricsHistory);
    }

    ADLX_RESULT GetSupportedSystemMetrics(IADLXSystemMetricsSupport** ppMetricsSupport) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetSupportedSystemMetrics);
    }

    ADLX_RESULT GetCurrentSystemMetrics(IADLXSystemMetrics** ppMetrics) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetCurrentSystemMetrics);
    }

    ADLX_RESULT GetSystemMetricsHistory(adlx_int startPositionMs, adlx_int endPositionMs, IADLXSystemMetricsList** ppMetricsList) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetSystemMetricsHistory);
    }
};