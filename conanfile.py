# SPDX-License-Identifier: BSL-1.0

import re
import os

from conan import ConanFile
from conan.tools.files import load

required_conan_version = ">=1.50.0"


class ModernCircuitsJuceModules(ConanFile):
    name = "mc-juce"
    url = "https://github.com/ModernCircuits/mc-juce"
    description = "Modern Circuits JUCE Modules"
    license = "BSL-1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_find_package", "markdown"

    def set_version(self):
        path = os.path.join(self.recipe_folder, "CMakeLists.txt")
        content = load(self, path)
        regex = r"project\([^\)]+VERSION (\d+\.\d+\.\d+)[^\)]*\)"
        ver = re.search(regex, content).group(1)
        self.version = ver.strip()

    def requirements(self):
        self.requires("concurrentqueue/1.0.4")
        self.requires("fmt/9.1.0")
        self.requires("range-v3/0.12.0")

        if self.settings.os != "Emscripten":
            self.requires("boost/1.82.0")

    def build_requirements(self):
        self.test_requires("catch2/3.2.1")

    def config_options(self):
        self.options["boost"].header_only = True

    def imports(self):
        self.copy("license*", dst="licenses", folder=True, ignore_case=True)
