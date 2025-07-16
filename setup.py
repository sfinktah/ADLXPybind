import os
import sys
import subprocess
import shutil
from pathlib import Path

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import pybind11


class CustomBuildExt(build_ext):
    """Custom build extension that handles ADLX setup and stub generation."""

    def run(self):
        # Setup ADLX repository
        self._setup_adlx_repository()

        # Build extensions first
        super().run()

        # Generate stubs after building
        self._generate_stubs()

    def _setup_adlx_repository(self):
        """Clone and setup ADLX repository if needed."""
        adlx_dir = Path("ADLXPybind/ADLX")

        if not adlx_dir.exists():
            print("Cloning ADLX repository...")
            subprocess.run([
                "git", "clone",
                "https://github.com/GPUOpen-LibrariesAndSDKs/ADLX.git",
                str(adlx_dir)
            ], check=True)

            print("Checking out ADLX V1.4...")
            subprocess.run(["git", "checkout", "V1.4"],
                           cwd=str(adlx_dir), check=True)
        else:
            print(f"ADLX repository exists at {adlx_dir}")
            try:
                subprocess.run(["git", "fetch", "--tags"],
                               cwd=str(adlx_dir), check=True)
                subprocess.run(["git", "checkout", "V1.4"],
                               cwd=str(adlx_dir), check=True)
                print("Ensured ADLX V1.4 is checked out")
            except subprocess.CalledProcessError:
                print("Warning: Could not checkout V1.4, using existing version")

        # Verify the required files exist using pathlib for correct path handling
        required_files = [
            adlx_dir / "SDK" / "ADLXHelper" / "Windows" / "Cpp" / "ADLXHelper.cpp",
            adlx_dir / "SDK" / "ADLXHelper" / "Windows" / "Cpp" / "ADLXHelper.h",
            adlx_dir / "SDK" / "Platform" / "Windows" / "WinAPIs.cpp",
            adlx_dir / "SDK" / "Include"
        ]

        for file_path in required_files:
            if not file_path.exists():
                print(f"Looking for: {file_path}")
                print(f"Absolute path: {file_path.absolute()}")
                raise FileNotFoundError(f"Required ADLX file not found: {file_path}")
            else:
                print(f"Found: {file_path}")

        print("ADLX repository setup complete")

    def _generate_stubs(self):
        """Generate type stubs for the built extension."""
        try:
            import pybind11_stubgen

            # Create stubs directory
            stubs_dir = Path("stubs")
            stubs_dir.mkdir(exist_ok=True)

            print("Generating type stubs...")
            pybind11_stubgen.main([
                "-o", str(stubs_dir),
                "--root-suffix", "",
                "_adlx_pybind"
            ])

            print("Type stubs generated successfully")

        except ImportError:
            print("pybind11-stubgen not available, using existing stubs")
        except Exception as e:
            print(f"Warning: Could not generate stubs: {e}")
            print("Using existing stubs instead")

        # Copy stubs to package directory
        self._copy_stubs_to_package()

    def _copy_stubs_to_package(self):
        """Copy stub files to the package directory."""
        try:
            package_dir = Path("ADLXPybind")

            stubs_source_dir = Path("stubs/ADLXPybind")

            # Copy all .pyi files from stubs directory
            if stubs_source_dir.exists():
                for stub_file in stubs_source_dir.glob("*.pyi"):
                    dest_file = package_dir / stub_file.name
                    shutil.copy2(stub_file, dest_file)
                    print(f"Copied {stub_file} to {dest_file}")

            print("Stubs copied to package directory")

        except Exception as e:
            print(f"Warning: Could not copy stubs: {e}")


def create_extension():
    """Create the pybind11 extension module."""
    # Use ADLX from ADLXPybind directory with proper path separators
    adlx_path = Path("ADLXPybind/ADLX")

    # Convert paths to strings with proper separators for the build system
    sources = [
        "src/bind.cpp",
        "src/ADXLGPUHolder.cpp",
        "src/GPUIterator.cpp",
        str(adlx_path / "SDK" / "ADLXHelper" / "Windows" / "Cpp" / "ADLXHelper.cpp"),
        str(adlx_path / "SDK" / "Platform" / "Windows" / "WinAPIs.cpp"),
    ]

    include_dirs = [
        pybind11.get_include(),
        str(adlx_path / "SDK" / "ADLXHelper" / "Windows" / "Cpp"),
        str(adlx_path / "SDK" / "Include"),
    ]

    return Extension(
        "_adlx_pybind",
        sources=sources,
        include_dirs=include_dirs,
        define_macros=[
            ("ADLXPYBIND_EXPORTS", None),
            ("_WINDOWS", None),
            ("_USRDLL", None),
        ],
        language="c++",
        extra_compile_args=["/std:c++17"],
        libraries=["user32", "kernel32"],
    )


# Only run setup if called directly (not when imported)
if __name__ == "__main__":
    setup(
        packages=["ADLXPybind"],
        ext_modules=[create_extension()],
        cmdclass={
            "build_ext": CustomBuildExt,
        },
        zip_safe=False,
    )