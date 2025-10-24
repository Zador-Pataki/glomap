# setup.py
from setuptools import setup
from setuptools.command.build_py import build_py as _build_py
import glob, os, shutil


class build_py(_build_py):
    def run(self):
        super().run()
        # 1) Find the freshly-built extension (built by your CMake step)
        candidates = glob.glob("build_python/pyglomap/*.so") + glob.glob(
            "build/pyglomap/*.so"
        )
        if not candidates:
            raise RuntimeError(
                "No built extension .so found in build_python/pyglomap or build/pyglomap"
            )
        so_path = max(candidates, key=os.path.getmtime)

        # 2) Copy it into the package in the build/lib tree so it lands in the wheel
        dest_dir = os.path.join(self.build_lib, "pyglomap")
        os.makedirs(dest_dir, exist_ok=True)
        shutil.copy2(so_path, dest_dir)


setup(
    name="pyglomap",
    version="1.0.0",
    author="Linfei Pan",
    author_email="linfei.pan@inf.ethz.ch",
    description="Pybind11 bindings for GLOMAP",
    packages=["pyglomap"],
    package_data={"pyglomap": ["*.so"]},  # include the copied .so
    cmdclass={"build_py": build_py},
    zip_safe=False,
)
