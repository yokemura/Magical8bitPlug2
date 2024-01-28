# Tools for Building and Installing Programs Based on JUCE Framework in Linux Using JUCE CMake API

* Since JUCE version 6.0.0, JUCE CMake API became available. [Read its official documentation about JUCE CMake API.](https://github.com/juce-framework/JUCE/blob/master/docs/CMake%20API.md)

* JUCE CMake API is useful to build executables and plugins in Linux, giving flexibility on adding features and optional building.

**Dependancies**

* Primary Dependencies for JUCE framework in Linux
  1. [Read its official documentation of dependencies in Linux](https://github.com/juce-framework/JUCE/blob/master/docs/Linux%20Dependencies.md)

* Additional Dependencies
  1. "git" - To Clone JUCE SDK
  2. "clang" - Portable Compiler over Processors and Architectures: I confirmed that version 11.0.1-2 in Raspberry Pi OS on Raspberry Pi 3B can compile a project with JUCE framework. GNU C/C++ compiler is the default compiler for Linux. However, the GNU compiler for arm-none-linux-gnueabi (version 10.2.1-6) needs to explicitly link libatomic which is implicitly linked in compilers for other processors. This issue may occur errors on compiling.
  3. "cmake" - Build Environment: Version 3.15 and Above
  4. "lv2-dev" - Development Tools for LV2 Plugin

**builder_linux.sh**

* This Bash script downloads JUCE framework and builds a standalone executable, a VST3 plugin, and a LV2 plugin.
  * Example to Build All: `./builder_linux.sh vst3 lv2`
  * A standalone executable is build without any argument.
  * If you select to build a LV2 plugin, the JUCE framework is downloaded from [the fork of the LV2 porting project](https://github.com/lv2-porting-project/JUCE/tree/lv2).
  * This script executes CMake with CMakeLists.txt in this folder. LLVM Clang is assigned as the C/C++ compiler.
  * Written by Kenta Ishii (JimmyKenMerchant.com) in January 2022

* Arguments (Orderless):
  1. "vst3" - Build VST3 Plugin
  2. "lv2" - Build LV2 Plugin
  3. "debug" - Build for Debugging
  4. "newjuce" - Reinstall Juce Framework: This's useful when you've already built without a LV2 plugin, but you want to build again for a LV2 plugin.

**installer_linux.sh**

* This Bash script helps to install an executable and plugins to your Linux system.
  * Example to Install All: `./installer_linux.sh standalone vst3 lv2`
  * Example to Uninstall Standalone: `./installer_linux.sh standalone uninstall`
  * This script needs the root privilege.
  * '/usr/local' is the prefix to destinations. Change the value of PREFIX_PATH in this script if you want to install an executable and plugins into other destinations.
  * Written by Kenta Ishii (JimmyKenMerchant.com) in January 2022

* Arguments (Orderless):
  1. "standalone" - Install/Uninstall Standalone Executable to PREFIX_PATH/bin
  2. "icons" - Install/Uninstall Small, Big, and Scalable Icons to PREFIX_PATH/share/icons/hicolor/ICON_SIZExICON_SIZE(or 'scalable')/apps: A .desktop (Desktop Entry) file is also installed to PREFIX_PATH/share/applications for linking icons to the standalone executable. Installed icons will appear after restarting you system.
  3. "vst3" - Install/Uninstall VST3 Plugin Package to PREFIX_PATH/lib/vst3
  4. "lv2" - Install/Uninstall LV2 Plugin Package to PREFIX_PATH/lib/lv2
  5. "uninstall" - Set Uninstall Mode

**History**

* February 26, 2022: Added GPLv3 License to "builder_linux.sh" and "installer_linux.sh".
* February 23, 2022: Modified "installer_linux.sh" about installing icons with imcomplete set of sizes.
* February 5, 2022: Added the "icons" arguments to "installer_linux.sh". Installing with lowercase letters.
* January 30, 2022: Added the "debug" and "newjuce" arguments to "builder_linux.sh".
* January 29, 2022: Published "builder_linux.sh", "installer_linux.sh", and "README.md" for the first time.
