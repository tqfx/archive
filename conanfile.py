from conans import ConanFile, CMake, tools


class aConan(ConanFile):
    name = "liba"
    version = "0.1.1"
    license = "MPL-2.0"
    author = "tqfx tqfx@foxmail.com"
    homepage = url = "https://github.com/tqfx/liba.git"
    description = "An algorithm library based on C/C++ language"
    topics = ("algorithm",)
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [1, 0], "fPIC": [1, 0], "ipo": [1, 0]}
    default_options = {"shared": 0, "fPIC": 1, "ipo": 0}
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
        CMakeLists_txt = str(tools.load("CMakeLists.txt"))
        if "conan_basic_setup" not in CMakeLists_txt:
            CMakeLists_txt = CMakeLists_txt.replace(
                "include(cmake/standard.cmake)\n",
                "include(cmake/standard.cmake)\n"
                "include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)\n"
                "conan_basic_setup()\n",
            )
        tools.save("CMakeLists.txt", CMakeLists_txt)

    def build(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_TESTING"] = 0
        if self.settings.build_type != "Debug":  # type: ignore
            cmake.definitions["LIBA_IPO"] = self.options.ipo  # type: ignore
        else:
            cmake.definitions["LIBA_IPO"] = 0
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
