class PyDisplayService : public IADLXDisplayServices
{
	public:
		using IADLXDisplayServices::IADLXDisplayServices;

		adlx_long  Acquire() override {
			PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
		}

		adlx_long  Release() override {
			PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
		}

		ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
		}

		ADLX_RESULT GetNumberOfDisplays(adlx_uint* numDisplays) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetNumberOfDisplays);
		}

		ADLX_RESULT GetDisplays(IADLXDisplayList** ppDisplay) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetDisplays);
		}

		ADLX_RESULT Get3DLUT(IADLXDisplay* pDisplay, IADLXDisplay3DLUT** ppDisp3DLUT) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, Get3DLUT);
		}

		ADLX_RESULT GetGamut(IADLXDisplay* pDisplay, IADLXDisplayGamut** ppDispGamut) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetGamut);
		}

		ADLX_RESULT GetGamma(IADLXDisplay* pDisplay, IADLXDisplayGamma** ppDispGamma) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetGamma);
		}

		ADLX_RESULT GetDisplayChangedHandling(IADLXDisplayChangedHandling** ppDisplayChangeHandling) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetDisplayChangedHandling);
		}

		ADLX_RESULT  GetFreeSync(IADLXDisplay* pDisplay, IADLXDisplayFreeSync** ppFreeSync) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetFreeSync);
		}

		ADLX_RESULT  GetVirtualSuperResolution(IADLXDisplay* pDisplay, IADLXDisplayVSR** ppVSR) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetVirtualSuperResolution);
		}

		ADLX_RESULT  GetGPUScaling(IADLXDisplay* pDisplay, IADLXDisplayGPUScaling** ppGPUScaling) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetGPUScaling);
		}

		ADLX_RESULT  GetScalingMode(IADLXDisplay* pDisplay, IADLXDisplayScalingMode** ppScalingMode) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetScalingMode);
		}

		ADLX_RESULT  GetIntegerScaling(IADLXDisplay* pDisplay, IADLXDisplayIntegerScaling** ppIntegerScaling) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetIntegerScaling);
		}

		ADLX_RESULT  GetColorDepth(IADLXDisplay* pDisplay, IADLXDisplayColorDepth** ppColorDepth) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetColorDepth);
		}

		ADLX_RESULT  GetPixelFormat(IADLXDisplay* pDisplay, IADLXDisplayPixelFormat** ppPixelFormat) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetPixelFormat);
		}

		ADLX_RESULT  GetCustomColor(IADLXDisplay* pDisplay, IADLXDisplayCustomColor** ppCustomColor) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetCustomColor);
		}

		ADLX_RESULT  GetHDCP(IADLXDisplay* pDisplay, IADLXDisplayHDCP** ppHDCP) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetHDCP);
		}

		ADLX_RESULT  GetCustomResolution(IADLXDisplay* pDisplay, IADLXDisplayCustomResolution** ppCustomResolution) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetCustomResolution);
		}

		ADLX_RESULT  GetVariBright(IADLXDisplay* pDisplay, IADLXDisplayVariBright** ppVariBright) override {
			PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetVariBright);
		}
};
