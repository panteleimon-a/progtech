# C++ Code Generator with GitHub Copilot in Windows Terminal

This project provides a lightweight setup to generate C++ code in the Windows terminal using **GitHub Copilot’s Terminal Chat** in Windows Terminal Canary, with a connection to GitHub only and no Python dependencies. Terminal Chat assists in generating C++ code snippets or build commands via natural language queries. The generated code is built using **CMake** for a streamlined process.

The goal is to enable C++ code generation and building directly from Windows Terminal Canary with minimal setup, relying on your GitHub Copilot subscription (e.g., Copilot Plus/Pro, Business, or Enterprise).

## Prerequisites

- **Windows Terminal Canary**: Required for Terminal Chat with GitHub Copilot integration.
- **GitHub Copilot Subscription**: Active subscription (Copilot Plus/Pro, Business, or Enterprise) linked to your GitHub account.
- **C++ Compiler**: MinGW-w64 for lightweight setup or MSVC (via Visual Studio).
- **CMake**: For building the generated C++ code.
- **GitHub Connection**: Internet access to authenticate with GitHub.

## Installation

### Install CMake
1. **Download CMake**:
   - Visit [cmake.org/download](https://cmake.org/download/) and download the Windows x64 installer (e.g., `cmake-X.XX.X-windows-x86_64.msi`).
   - Run the installer and select “Add CMake to the system PATH for all users.”

2. **Verify Installation**:
   - Open Command Prompt or PowerShell and check the version:
     ```cmd
     cmake --version
     ```
   - Ensure the output shows the installed version (e.g., `cmake version 3.28.3`).

### Install MinGW-w64 (C++ Compiler)
1. **Download MinGW-w64**:
   - Install MinGW-w64 from [MinGW-W64 online installer](https://github.com/Vuniverse0/mingwInstaller/releases/download/1.2.1/mingwInstaller.exe).
   <br>
2. **Add MinGW-w64 to PATH**:
   - Open Windows Settings > System > About > Advanced system settings > Environment Variables.
   - Under **System variables**, find and edit the `Path` variable.
   - Click **New** and add `C:\MinGW\bin` (or `C:\MinGW-w64\bin` if you used a custom path).
   - Click **OK** to save changes.
   - Note: If you used WinLibs, the bin directory might be `C:\MinGW\mingw64\bin`; verify the path in your installation folder.

3. **Verify Installation**:
   - Open Command Prompt or PowerShell and run:
     ```cmd
     g++ --version
     ```
   - Confirm the output shows the compiler version (e.g., `g++ (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0`).
   - If the command is not recognized, double-check the PATH setting or restart your terminal to apply changes.
   - Test with a simple C++ program:
     ```cmd
     echo #include ^<iostream^> > test.cpp
     echo int main() { std::cout ^<^< "Hello, MinGW!\n"; return 0; } >> test.cpp
     g++ test.cpp -o test
     test.exe
     ```
   - Expected output: `Hello, MinGW!`

4. **Troubleshooting**:
   - If the installer fails, ensure you have a stable internet connection, as it downloads files during installation.
   - If `g++` is not found, verify the `bin` directory is correct in PATH (e.g., `C:\MinGW\bin` contains `g++.exe`).
   - For WinLibs, ensure the archive is fully extracted and the `mingw64\bin` directory is added to PATH.
   - Check the [MinGW-w64 wiki](http://mingw-w64.org/doku.php) or [WinLibs FAQ](https://winlibs.com/#faq) for additional help.

### Install and Set Up Terminal Chat in Windows Terminal Canary
1. **Install Windows Terminal Canary**:
   - Download the latest build from the [Windows Terminal GitHub repository](https://github.com/microsoft/terminal/releases).
   - Install the `.msixbundle` file by double-clicking it or using PowerShell:
     ```powershell
     Add-AppxPackage .\Microsoft.WindowsTerminalPreview_*.msixbundle
     ```

2. **Authenticate GitHub Copilot**:
   - Open Windows Terminal Canary (search for “Windows Terminal Preview” in the Start menu).
   - Open Settings from the dropdown menu (top bar).
   - Navigate to **Terminal Chat (Experimental)** under Settings.
   - Under **Service Providers**, select **GitHub Copilot** and click **Authenticate via GitHub**.
   - Sign in to your GitHub account with an active Copilot subscription.
   - Ensure **Set as active provider** is checked and click **Save**.
   - Note: If your organization disables Copilot features, you may not be able to use Terminal Chat. Check with your admin.

3. **Verify Setup**:
   - Open the **Terminal Chat (Experimental)** panel from the dropdown menu.
   - Type a test query (e.g., “How do I list all .cpp files?”) and press Enter.
   - Copilot should respond with a command (e.g., `dir *.cpp` for CMD or `ls *.cpp` for PowerShell).

## Usage

Use GitHub Copilot’s Terminal Chat to suggest C++ code snippets or CMake commands, which are then saved to files and built using CMake.

1. **Generate C++ Code**:
   - Open Windows Terminal Canary and select the **Terminal Chat (Experimental)** panel.
   - Type a query to generate a C++ code snippet, e.g.:
     ```
     Write a C++ class named MyClass with a constructor and a sayHello method
     ```
   - Copilot responds with a code snippet, e.g.:
     ```cpp
     #include <iostream>
     class MyClass {
     public:
         MyClass() { std::cout << "Constructor for MyClass\n"; }
         void sayHello() { std::cout << "Hello from MyClass\n"; }
     };
     ```
   - Copy the suggested code (click the suggestion to copy it to the input line) and save it to a file `MyClass.cpp` using a text editor or terminal command:
     ```cmd
     echo #include ^<iostream^> > MyClass.cpp
     echo class MyClass { >> MyClass.cpp
     echo public: >> MyClass.cpp
     echo     MyClass() { std::cout ^<^< "Constructor for MyClass\n"; } >> MyClass.cpp
     echo     void sayHello() { std::cout ^<^< "Hello from MyClass\n"; } >> MyClass.cpp
     echo }; >> MyClass.cpp
     ```

2. **Create a Main File**:
   - Create `main.cpp` to use the class by requesting a main function:
     ```
     Write a C++ main function that uses MyClass
     ```
   - Copilot may suggest:
     ```cpp
     #include "MyClass.hpp"
     int main() {
         MyClass obj;
         obj.sayHello();
         return 0;
     }
     ```
   - Save it as `main.cpp`:
     ```cmd
     echo #include "MyClass.hpp" > main.cpp
     echo int main() { >> main.cpp
     echo     MyClass obj; >> main.cpp
     echo     obj.sayHello(); >> main.cpp
     echo     return 0; >> main.cpp
     echo } >> main.cpp
     ```
   - Request a header file:
     ```
     Generate a C++ header file for MyClass
     ```
   - Save the response as `MyClass.hpp`:
     ```cpp
     #ifndef MYCLASS_HPP
     #define MYCLASS_HPP
     #include <iostream>
     class MyClass {
     public:
         MyClass();
         void sayHello();
     };
     #endif
     ```
   - Save it using a text editor or:
     ```cmd
     echo #ifndef MYCLASS_HPP > MyClass.hpp
     echo #define MYCLASS_HPP >> MyClass.hpp
     echo #include ^<iostream^> >> MyClass.hpp
     echo class MyClass { >> MyClass.hpp
     echo public: >> MyClass.hpp
     echo     MyClass(); >> MyClass.hpp
     echo     void sayHello(); >> MyClass.hpp
     echo }; >> MyClass.hpp
     echo #endif >> MyClass.hpp
     ```

3. **Create a CMakeLists.txt**:
   - Request a CMake file:
     ```
     Generate a CMakeLists.txt for a C++ project with MyClass.cpp and main.cpp
     ```
   - Copilot may suggest:
     ```cmake
     cmake_minimum_required(VERSION 3.10)
     project(MyProject)
     set(CMAKE_CXX_STANDARD 11)
     add_executable(MyClass main.cpp MyClass.cpp)
     ```
   - Save it as `CMakeLists.txt` in your project directory (e.g., `C:\codegen`) using a text editor or:
     ```cmd
     echo cmake_minimum_required(VERSION 3.10) > CMakeLists.txt
     echo project(MyProject) >> CMakeLists.txt
     echo set(CMAKE_CXX_STANDARD 11) >> CMakeLists.txt
     echo add_executable(MyClass main.cpp MyClass.cpp) >> CMakeLists.txt
     ```

4. **Build and Run**:
   - Navigate to your project directory in Windows Terminal Canary:
     ```cmd
     cd C:\codegen
     ```
   - Create a build directory and build:
     ```cmd
     mkdir build && cd build
     cmake .. -G "MinGW Makefiles"
     cmake --build .
     ```
   - Run the executable:
     ```cmd
     MyClass.exe
     ```

## Notes

- **GitHub-Only Connection**: Terminal Chat relies solely on GitHub authentication and Copilot’s cloud-based services, requiring no additional external services beyond GitHub.
- **Copilot Plus Subscription**: Your Copilot Plus (Pro) subscription grants unlimited access to Terminal Chat (unlike the Free plan’s 50-message/month limit). If you hit limits, verify your plan at [github.com](https://github.com).
- **No Python Dependencies**: This setup avoids Python entirely, using Copilot’s natural language processing for code generation.
- **CMake Flexibility**: Use `-G "NMake Makefiles"` instead of `-G "MinGW Makefiles"` if using MSVC. Ask Copilot for alternative generators if needed.
- **Safety**: Always review Copilot’s suggested code or commands, as they may contain errors. Terminal Chat does not auto-execute commands, giving you control.
- **Limitations**: Copilot is optimized for coding tasks. Non-coding queries may yield inaccurate responses. Use English for best results.
- **Troubleshooting**:
   - If Terminal Chat authentication fails, clear stored auth tokens in Settings and re-authenticate.
   - If MinGW-w64 commands fail, verify the PATH and test with a simple program as shown above.
   - Check the [Windows Terminal repository](https://github.com/microsoft/terminal) or [MinGW-w64 wiki](http://mingw-w64.org/doku.php) for additional help.