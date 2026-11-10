from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout


class DuplicateScanner(ConanFile):
    settings: tuple[str] = ("os", "compiler", "build_type", "arch")
    generators: tuple[str] = ("CMakeToolchain", "CMakeDeps")

    def requirements(self) -> None:
        self.requires("boost/1.89.0")
        self.requires("spdlog/1.17.0")

    def layout(self) -> None:
        cmake_layout(self)

    def configure(self) -> None:
        self.options["boost"].without_test = False
        self.options["boost"].shared = False
        self.options["boost"].without_graph = True
        self.options["boost"].without_log = True
        self.options["boost"].without_math = False
        self.options["boost"].without_wave = True
        self.options["boost"].without_cobalt = True
        self.options["boost"].without_locale = True
        self.options["boost"].without_stacktrace = True
        self.options["boost"].without_json = True
        self.options["boost"].without_iostreams = True
        self.options["boost"].without_program_options = False
        self.options["boost"].without_url = True
        self.options["boost"].without_nowide = True
        self.options["boost"].without_contract = True
        self.options["boost"].without_timer = True
        self.options["boost"].without_type_erasure = True
