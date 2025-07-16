# ADLXPybind

Python bindings for AMD Device Library Extra (ADLX) 1.4

This Python package allows developers to integrate with AMD's ADLX SDK seamlessly while leveraging Python's simplicity and flexibility.

This package automatically downloads and builds against ADLX V1.4 from the official AMD repository.

---

## **Features**
- Access and manage **display services** (e.g., connected displays, display properties).
- Interface with **performance monitoring services** (e.g., GPU metrics like usage, power, and VRAM usage).
- **GPU Tuning** capabilities for optimizing system performance.
- Built-in utilities for **initializing and managing ADLX services**.
- Designed for use alongside AMD systems and technologies.

## Supported Classes and Methods

### Currently Implemented Classes

#### Core System Classes
- **`ADLXHelper`** - Main initialization and system access
  - `Initialize()` - Initialize ADLX
  - `GetSystemServices()` - Get system services
  - `Terminate()` - Terminate ADLX
  - `QueryVersion()` - Get ADLX version
  - `InitializeWithCallerAdl()` - Initialize with caller ADL
  - `InitializeWithIncompatibleDriver()` - Initialize with incompatible driver
  - `GetAdlMapping()` - Get ADL mapping

#### GPU Management
- **`ADLXGPUHolder`** - GPU management utility
  - `getGPU()` - Get GPU instance
  - `getGPUList()` - Get GPU list
  - `isValid()` - Check if GPU holder is valid

#### Display Services
- **`IADLXDisplayServices`** - Display management
  - `GetDisplays()` - Get display list
  - `GetNumberOfDisplays()` - Get display count
  - `GetDisplayChangedHandling()` - Get display change handler

- **`IADLXDisplay`** - Individual display management
  - `name()` - Get display name
  - `type()` - Get display type
  - `connectType()` - Get connector type
  - `ManufacturerID()` - Get manufacturer ID
  - `EDID()` - Get EDID data
  - `resolution()` - Get display resolution
  - `RefreshRate()` - Get refresh rate
  - `PixelClock()` - Get pixel clock
  - `ScanType()` - Get scan type
  - `UniqueId()` - Get unique identifier

#### Performance Monitoring
- **`IADLXPerformanceMonitoringServices`** - Performance monitoring access
  - `GetSupportedGPUMetrics()` - Get supported GPU metrics
  - `GetCurrentGPUMetrics()` - Get current GPU metrics
  - `GetGPUMetricsHistory()` - Get GPU metrics history
  - `StartPerformanceMetricsTracking()` - Start metrics tracking
  - `StopPerformanceMetricsTracking()` - Stop metrics tracking
  - `ClearPerformanceMetricsHistory()` - Clear metrics history

- **`IADLXGPUMetricsSupport`** - GPU metrics support information
  - `IsSupportedGPUUsage()` - Check GPU usage support
  - `IsSupportedGPUClockSpeed()` - Check GPU clock speed support
  - `IsSupportedGPUVRAMClockSpeed()` - Check VRAM clock speed support
  - `IsSupportedGPUTemperature()` - Check GPU temperature support
  - `IsSupportedGPUHotspotTemperature()` - Check hotspot temperature support
  - `IsSupportedGPUPower()` - Check GPU power support
  - `IsSupportedGPUFanSpeed()` - Check fan speed support
  - `IsSupportedGPUVRAM()` - Check VRAM support
  - `IsSupportedGPUVoltage()` - Check voltage support
  - `IsSupportedGPUTotalBoardPower()` - Check total board power support
  - `IsSupportedGPUIntakeTemperature()` - Check intake temperature support

- **`IADLXGPUMetrics`** - Actual GPU metrics data
  - `GPUUsage()` - Get GPU usage percentage
  - `GPUClockSpeed()` - Get GPU clock speed
  - `GPUVRAMClockSpeed()` - Get VRAM clock speed
  - `GPUTemperature()` - Get GPU temperature
  - `GPUHotspotTemperature()` - Get hotspot temperature
  - `GPUPower()` - Get GPU power consumption
  - `GPUFanSpeed()` - Get fan speed
  - `GPUVRAM()` - Get VRAM usage
  - `GPUVoltage()` - Get GPU voltage
  - `GPUTotalBoardPower()` - Get total board power
  - `GPUIntakeTemperature()` - Get intake temperature
  - `TimeStamp()` - Get timestamp

#### Extended GPU Metrics (V2)
- **`IADLXGPUMetricsSupport2`** - Extended metrics support
  - `IsSupportedGPUSharedMemory()` - Check shared GPU memory support

- **`IADLXGPUMetrics2`** - Extended metrics data
  - `GPUSharedMemory()` - Get shared GPU memory usage

#### Event Handling
- **`DisplayListCallBack`** - Display change event callback
  - Event handling for display list changes
  - `OnDisplayListChanged()` - Callback for display changes

#### Enumerations
- **`ADLX_RESULT`** - Result codes for ADLX operations
- **`ADLX_DISPLAY_TYPE`** - Display type enumeration
- **`ADLX_DISPLAY_CONNECTOR_TYPE`** - Display connector type enumeration
- **`ADLX_DISPLAY_SCAN_TYPE`** - Display scan type enumeration
- **`ADLX_GPU_TYPE`** - GPU type enumeration
- **`ADLX_ASIC_FAMILY_TYPE`** - ASIC family type enumeration
- **`ADLX_HG_TYPE`** - Hybrid graphics type enumeration
- **`ADLX_PCI_BUS_TYPE`** - PCI bus type enumeration
- **`ADLX_DP_LINK_RATE`** - DisplayPort link rate enumeration

---

## Classes NOT Currently Implemented

This implementation covers only a **small subset** of ADLX's extensive functionality. The following major areas are **NOT implemented**:

### 3D Graphics Settings
- `IADLX3DAntiLag` - Anti-lag functionality
- `IADLX3DBoost` - Boost functionality
- `IADLX3DRSRSupport` - RSR support
- `IADLX3DAMDFluidMotionFrames` - Fluid motion frames
- `IADLX3DImageSharpenDesktop` - Image sharpening

### GPU Tuning
- `IADLXGPUTuningServices` - GPU tuning services
- `IADLXManualGraphicsTuning` - Manual graphics tuning
- `IADLXManualVRAMTuning` - Manual VRAM tuning
- `IADLXManualPowerTuning` - Manual power tuning
- `IADLXManualFanTuning` - Manual fan tuning
- `IADLXGPUPresetTuning` - Preset tuning
- `IADLXGPUAutoTuning` - Auto tuning

### Power Management
- `IADLXPowerTuningServices` - Power tuning services
- `IADLXSmartShiftMax` - SmartShift Max
- `IADLXSmartShiftEco` - SmartShift Eco
- `IADLXSmartAccessMemory` - Smart Access Memory

### Display Advanced Features
- `IADLXDisplayGamut` - Display gamut control
- `IADLXDisplayGamma` - Display gamma control
- `IADLXDisplay3DLUT` - 3D LUT functionality
- `IADLXDisplayFreeSync` - FreeSync control
- `IADLXDisplayConnectivityExperience` - Connectivity experience
- `IADLXDisplayBlanking` - Display blanking
- `IADLXDisplayDynamicRefreshRateControl` - Dynamic refresh rate
- `IADLXDisplayFreeSyncColorAccuracy` - FreeSync color accuracy

### System Information
- `IADLXSystemMetrics` - System metrics
- `IADLXDesktopServices` - Desktop services
- `IADLXI2C` - I2C interface
- `IADLXApplicationServices` - Application services

### Multi-Media
- `IADLXVideoUpscale` - Video upscale functionality
- Various video processing interfaces

### Collections and Utilities
- Most collection interfaces beyond basic GPU and display lists
- Advanced logging interfaces
- Event system beyond display changes

---

## Note

This implementation represents only a **fraction** of ADLX's full capabilities. ADLX provides extensive functionality for:
- Advanced GPU tuning and overclocking
- Display color management and calibration
- Power management and efficiency features
- 3D graphics optimization
- System monitoring and diagnostics
- Multi-GPU configurations
- And much more...

**Pull requests are welcome!** If you need additional ADLX functionality, contributions to expand this binding are greatly appreciated. The ADLX SDK documentation provides comprehensive information about all available interfaces and their capabilities.

---

## **Installation**

### Prerequisites
- Python 3.6 or higher.
- AMD drivers supporting ADLX SDK.

### Install Using `pip`

```
pip install ADLXPybind
```
---

## **Usage Example**

### **Retrieving Detailed Display Information**

This example fetches details for all connected displays:
```python
import ADLXPybind as ADLX

# Iterate display and display event:plug and unplug the display
def displayDemo():
    # Get ADLXHelp and ADLX initialization
    adlxHelper = ADLX.ADLXHelper()
    ret = adlxHelper.Initialize()

    if ret == ADLX.ADLX_RESULT.ADLX_OK:
        # Get system services
        system = adlxHelper.GetSystemServices()

        if system is not None:
            # Get display services
            displayService = system.GetDisplaysServices()

            if displayService is not None:
                # Iterate through the display list
                count = displayService.GetNumberOfDisplays()
                print("display count: {}".format(count))
                disList = displayService.GetDisplays()
                if disList is not None:
                    for index, display in enumerate(disList):
                        if display is not None:
                            name = display.name()
                            type = display.type()
                            connectType = display.connectType()
                            mid = display.ManufacturerID()
                            edid = display.EDID()
                            h,v = display.resolution()
                            refreshRate = display.RefreshRate()
                            pclock = display.PixelClock()
                            scanType = display.ScanType()
                            id = display.UniqueId()
                            print("\nThe display [{}]:".format(index))
                            print("\tName: {}".format(name))
                            print("\tType: {}".format(type))
                            print("\tConnector type: {}".format(connectType))
                            print("\tManufacturer id: {}".format(mid))
                            print("\tEDID: {}".format(edid))
                            print("\tResolution:  h: {}  v: {}".format(h,v))
                            print("\tRefresh rate: {}".format(refreshRate))
                            print("\tPixel clock: {}".format(pclock))
                            print("\tScan type: {}".format(scanType))
                            print("\tUnique id: {}".format(id))
                            # Release display interface
                            del display

                    # Release displayList interface
                    del disList

                # Release displayService interface
                del displayService

    # Terminate ADLX
    ret = adlxHelper.Terminate()
    print("ADLX Terminate ret is: {}".format(ret))

displayDemo()
```
---

## **Documentation**

For detailed documentation about ADLX and its capabilities, visit the official [GPUOpen ADLX SDK page](https://www.gpuopen.com/adlx).

---

## **License**

This project is distributed under the license included in the ADLX SDK. See the `ADLX SDK License Agreement.pdf` at https://github.com/GPUOpen-LibrariesAndSDKs/ADLX for more details.

---

## **Attribution**

- AMD, the AMD Arrow logo, Radeon, Crossfire, and combinations thereof are either registered trademarks or trademarks of Advanced Micro Devices, Inc. in the United States and/or other countries.
- Microsoft, Visual Studio, and Windows are either registered trademarks or trademarks of Microsoft Corporation in the United States and/or other countries.

## **Stashed Notes**

```
strings /c/Windows/System32/amdxc64.so | grep -i :gfx
NAVI10:gfx1010
NAVI12:gfx1011
NAVI14:gfx1012
NAVI21:gfx1030
NAVI22:gfx1031
NAVI23:gfx1032
NAVI24:gfx1034
VANGOGH:gfx1033
REMBRANDT:gfx1035
RAPHAEL:gfx1036
NAVI31:gfx1100
NAVI32:gfx1101
NAVI33:gfx1102
PHOENIX1:gfx1103
PHOENIX2:gfx1103
STRIX1:gfx1150
KRACKAN1:gfx1152
STRIX_HALO:gfx1151
NAVI44:gfx1200
NAVI48:gfx1201
```