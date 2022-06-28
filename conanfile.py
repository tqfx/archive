from conans import ConanFile, CMake, tools


class aConan(ConanFile):
    name = "liba"
    version = "0.1.0"
    license = "MPL-2.0"
    author = "tqfx tqfx@foxmail.com"
    homepage = url = "https://github.com/tqfx/liba.git"
    description = "An algorithm library based on C language"
    topics = ("algorithm",)
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False], "ipo": [True, False]}
    default_options = {"shared": False, "fPIC": True, "ipo": False}
    exports_sources = (
        "CMakeLists.txt",
        "LICENSE.txt",
        "README.md",
        "include/*",
        "cmake/*",
        "src/*",
    )

    def config_options(self):
        if self.settings.os == "Windows":  # type: ignore
            del self.options.fPIC  # type: ignore

    def source(self):
        tools.replace_in_file(
            "CMakeLists.txt",
            "include(cmake/standard.cmake)",
            "include(cmake/standard.cmake)\n\n"
            "include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)\n"
            "conan_basic_setup()",
        )

    def build(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_TESTING"] = False
        if self.settings.build_type != "Debug":  # type: ignore
            cmake.definitions["ENABLE_IPO"] = self.options.ipo  # type: ignore
        else:
            cmake.definitions["ENABLE_IPO"] = False
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
