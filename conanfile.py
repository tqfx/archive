from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout


class aConan(ConanFile):
    name = "liba"
    version = "0.1.0"
    license = "MPL-2.0"
    author = "tqfx tqfx@foxmail.com"
    url = "https://github.com/tqfx/a.git"
    description = "An algorithm library based on C language."
    topics = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    exports_sources = "*"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure({"BUILD_TESTING": "OFF"})
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["a"]
