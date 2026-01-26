from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout


class DuplicateScanner(ConanFile):
    settings: tuple[str] = ("os", "compiler", "build_type", "arch")
    generators: tuple[str] = ("CMakeToolchain", "CMakeDeps")

    def requirements(self) -> None:
        self.requires("boost/1.89.0")

    def layout(self) -> None:
        cmake_layout(self)
