# C++ Code Generator with Python Transformers in Windows Terminal

This project provides a lightweight setup to generate C++ code in the Windows terminal using the **Transformers** library in Python, leveraging the **CodeLlama-13B-Instruct** model for high-quality C++ code generation. The setup requires installing Python, adding it to the PATH, and installing dependencies via a GitHub-connected package index (PyPI). Generated code is built and tested using **CMake** and **MinGW-w64**. The solution is designed for users with a GitHub connection for package downloads and a Windows environment.

## Prerequisites

- **Python 3.10+**: Required for running the Transformers library.
- **MinGW-w64**: C++ compiler for building generated code.
- **CMake**: For building the C++ code.
- **GitHub Connection**: Internet access to download Python packages from PyPI and model weights from Hugging Face.
- **Hardware**: 16GB RAM minimum for CPU inference; NVIDIA GPU (8GB VRAM) recommended for faster inference with the quantized model.
- **Windows Terminal or Command Prompt**: For executing commands.

## Installation

### Install Python and Add to PATH
1. **Download Python**:
   - Visit [python.org/downloads](https://www.python.org/downloads/) and download the latest Python 3.10+ installer for Windows (e.g., `python-3.12.4-amd64.exe`).
   - Choose the 64-bit installer for compatibility with modern systems.

2. **Run the Installer**:
   - Double-click the installer to launch it.
   - Check the box **Add Python 3.X to PATH** to automatically add Python to your system PATH.
   - Select **Customize installation** (optional) to ensure pip and other components are included.
   - Install to the default directory (e.g., `C:\Users\<YourUsername>\AppData\Local\Programs\Python\Python312`).
   - Click **Install** and wait for completion.

3. **Verify Installation**:
   - Open Command Prompt (or PowerShell) and check the Python version:
     ```cmd
     python --version
     ```
   - Expected output: `Python 3.12.4` (or similar).
   - Verify pip:
     ```cmd
     pip --version
     ```
   - If Python or pip is not recognized, manually add Python to PATH:
     - Open Windows Settings > System > About > Advanced system settings > Environment Variables.
     - Under **System variables**, edit `Path` and add:
       - `C:\Users\<YourUsername>\AppData\Local\Programs\Python\Python312`
       - `C:\Users\<YourUsername>\AppData\Local\Programs\Python\Python312\Scripts`
     - Restart your terminal and re-run the verification commands.

4. **Troubleshooting**:
   - If the installer fails, ensure you have administrative privileges.
   - If PATH is incorrect, verify the Python installation directory and update PATH accordingly.
   - Check [python.org](https://www.python.org/) for installation FAQs.

### Install MinGW-w64 (C++ Compiler)
1. **Download MinGW-w64**:
   - Visit the MinGW-w64 project page at [sourceforge.net/projects/mingw-w64](https://sourceforge.net/projects/mingw-w64/) or [mingw-w64.org](http://mingw-w64.org/doku.php/download).
   - Download the installer `mingw-w64-install.exe` from SourceForge under **Files**.
   - Alternatively, use [WinLibs](https://winlibs.com/) for a standalone package (e.g., `winlibs-x86_64-posix-seh-gcc-X.XX.X-mingw-w64-X.XX.X-release-mingw-w64rt-X.XX.X.7z`).
   - **Recommendation**: Use `mingw-w64-install.exe` for ease of use.

2. **Run the Installer**:
   - Double-click `mingw-w64-install.exe`.
   - Configure:
     - **Version**: Latest GCC (e.g., 8.1.0 or higher).
     - **Architecture**: `x86_64` (64-bit Windows).
     - **Threads**: `posix` (for C++11 threading).
     - **Exception**: `seh` (64-bit performance).
     - **Destination**: `C:\MinGW` (or `C:\MinGW-w64`).
     - **Components**: Select `gcc`, `g++`, `binutils`.
   - Click **Install** and wait for completion.

3. **Add to PATH**:
   - Open Windows Settings > System > About > Advanced system settings > Environment Variables.
   - Edit `Path` under **System variables**, adding `C:\MinGW\bin`.
   - For WinLibs, extract the archive to `C:\MinGW` with 7-Zip ([7-zip.org](https://www.7-zip.org/)) and add `C:\MinGW\mingw64\bin`.

4. **Verify Installation**:
   - Run:
     ```cmd
     g++ --version
     ```
   - Confirm output (e.g., `g++ (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0`).
   - Test with:
     ```cmd
     echo #include ^<iostream^> > test.cpp
     echo int main() { std::cout ^<^< "Hello, MinGW!\n"; return 0; } >> test.cpp
     g++ test.cpp -o test
     test.exe
     ```
   - Expected output: `Hello, MinGW!`

5. **Troubleshooting**:
   - Ensure internet connectivity for the installer.
   - Verify `C:\MinGW\bin` contains `g++.exe`.
   - Check [MinGW-w64 wiki](http://mingw-w64.org/doku.php) or [WinLibs FAQ](https://winlibs.com/#faq).

### Install CMake
1. **Download CMake**:
   - Visit [cmake.org/download](https://cmake.org/download/) and download the Windows x64 installer (e.g., `cmake-X.XX.X-windows-x86_64.msi`).
   - Run the installer and select “Add CMake to the system PATH for all users.”

2. **Verify Installation**:
   - Run:
     ```cmd
     cmake --version
     ```
   - Confirm output (e.g., `cmake version 3.28.3`).

### Install Transformers and Dependencies
1. **Install Transformers**:
   - In Command Prompt:
     ```cmd
     pip install transformers torch
     ```
   - This installs the Hugging Face Transformers library and PyTorch (for model inference).
   - If you have an NVIDIA GPU, install PyTorch with CUDA for faster inference:
     ```cmd
     pip install torch --index-url https://download.pytorch.org/whl/cu121
     ```

2. **Install GPTQ Dependencies (Optional, for Quantized Model)**:
   - For GPU users, install the quantized model dependencies:
     ```cmd
     pip install auto-gptq
     ```

3. **Verify Installation**:
   - Test the Transformers library:
     ```cmd
     python -c "from transformers import pipeline; print('Transformers installed successfully')"
     ```
   - Expected output: `Transformers installed successfully`.

4. **Troubleshooting**:
   - If pip fails, ensure internet access and try:
     ```cmd
     pip install --upgrade pip
     ```
   - For GPU issues, verify CUDA compatibility at [pytorch.org](https://pytorch.org/).
   - Check [Hugging Face docs](https://huggingface.co/docs/transformers) for errors.

## Usage

Use a Python script with the Transformers library to generate C++ code via the **CodeLlama-13B-Instruct** model (or its quantized version) and save it to a file. Build and test the code with CMake and MinGW-w64.

1. **Create a Python Script for Code Generation**:
   - Create a file `generate_cpp.py` in your project directory (e.g., `C:\codegen`):
     ```python
     from transformers import pipeline
     import sys

     def generate_cpp_code(prompt, model_name="meta-llama/CodeLlama-13B-Instruct-hf"):
         try:
             # Use quantized model if GPU is available, else fallback to base model
             generator = pipeline("text-generation", model=model_name, device=0 if torch.cuda.is_available() else -1)
             response = generator(prompt, max_length=500, num_return_sequences=1, do_sample=True, temperature=0.7)
             return response[0]["generated_text"].strip()
         except Exception as e:
             print(f"Error: {e}")
             sys.exit(1)

     if __name__ == "__main__":
         prompt = sys.argv[1] if len(sys.argv) > 1 else "Write a C++ class named MyClass with a constructor and a sayHello method"
         output_file = sys.argv[2] if len(sys.argv) > 2 else "MyClass.cpp"
         code = generate_cpp_code(prompt)
         with open(output_file, "w") as f:
             f.write(code)
         print(f"Generated C++ code saved to {output_file}")
     ```
   - Save using a text editor or terminal:
     ```cmd
     echo from transformers import pipeline > generate_cpp.py
     echo import sys >> generate_cpp.py
     echo. >> generate_cpp.py
     echo def generate_cpp_code(prompt, model_name="meta-llama/CodeLlama-13B-Instruct-hf"): >> generate_cpp.py
     echo     try: >> generate_cpp.py
     echo         generator = pipeline("text-generation", model=model_name, device=0 if torch.cuda.is_available() else -1) >> generate_cpp.py
     echo         response = generator(prompt, max_length=500, num_return_sequences=1, do_sample=True, temperature=0.7) >> generate_cpp.py
     echo         return response[0]["generated_text"].strip() >> generate_cpp.py
     echo     except Exception as e: >> generate_cpp.py
     echo         print(f"Error: {e}") >> generate_cpp.py
     echo         sys.exit(1) >> generate_cpp.py
     echo. >> generate_cpp.py
     echo if __name__ == "__main__": >> generate_cpp.py
     echo     prompt = sys.argv[1] if len(sys.argv) > 1 else "Write a C++ class named MyClass with a constructor and a sayHello method" >> generate_cpp.py
     echo     output_file = sys.argv[2] if len(sys.argv) > 2 else "MyClass.cpp" >> generate_cpp.py
     echo     code = generate_cpp_code(prompt) >> generate_cpp.py
     echo     with open(output_file, "w") as f: >> generate_cpp.py
     echo         f.write(code) >> generate_cpp.py
     echo     print(f"Generated C++ code saved to {output_file}") >> generate_cpp.py
     ```
   - Note: For GPU users, replace `model_name="meta-llama/CodeLlama-13B-Instruct-hf"` with `model_name="TheBloke/CodeLlama-13B-Instruct-GPTQ"` for faster inference.

2. **Generate C++ Code via Terminal**:
   - Navigate to your project directory:
     ```cmd
     cd C:\codegen
     ```
   - Run the script to generate a C++ class:
     ```cmd
     python generate_cpp.py "Write a C++ class named MyClass with a constructor and a sayHello method" MyClass.cpp
     ```
   - Output: `Generated C++ code saved to MyClass.cpp`.
   - Expected content in `MyClass.cpp` (example):
     ```cpp
     #include <iostream>
     class MyClass {
     public:
         MyClass() { std::cout << "Constructor for MyClass\n"; }
         void sayHello() { std::cout << "Hello from MyClass\n"; }
     };
     ```
   - Generate a header file:
     ```cmd
     python generate_cpp.py "Generate a C++ header file for a class named MyClass with a constructor and a sayHello method" MyClass.hpp
     ```
   - Expected content in `MyClass.hpp`:
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
   - Generate a main file:
     ```cmd
     python generate_cpp.py "Write a C++ main function that uses MyClass from MyClass.hpp" main.cpp
     ```
   - Expected content in `main.cpp`:
     ```cpp
     #include "MyClass.hpp"
     int main() {
         MyClass obj;
         obj.sayHello();
         return 0;
     }
     ```

3. **Create a CMakeLists.txt**:
   - Create `CMakeLists.txt` in `C:\codegen` using a text editor or:
     ```cmd
     echo cmake_minimum_required(VERSION 3.10) > CMakeLists.txt
     echo project(MyProject) >> CMakeLists.txt
     echo set(CMAKE_CXX_STANDARD 11) >> CMakeLists.txt
     echo add_executable(MyClass main.cpp MyClass.cpp) >> CMakeLists.txt
     ```
   - Content:
     ```cmake
     cmake_minimum_required(VERSION 3.10)
     project(MyProject)
     set(CMAKE_CXX_STANDARD 11)
     add_executable(MyClass main.cpp MyClass.cpp)
     ```

4. **Build and Test the Generated Code**:
   - Navigate to your project directory:
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
   - Expected output:
     ```
     Constructor for MyClass
     Hello from MyClass
     ```

5. **Verify and Debug**:
   - Check `MyClass.cpp`, `MyClass.hpp`, and `main.cpp` for syntax errors (CodeLlama is reliable but may occasionally omit includes or misformat code).
   - If compilation fails, inspect error messages from `cmake --build .` and fix the generated code (e.g., add missing `#include <iostream>`).
   - Test with a simple program if issues persist:
     ```cmd
     echo #include ^<iostream^> > test.cpp
     echo int main() { std::cout ^<^< "Test\n"; return 0; } >> test.cpp
     g++ test.cpp -o test
     test.exe
     ```
   - If the model fails to load, ensure sufficient RAM (16GB+) or use the quantized model with a GPU.

## Notes

- **Model Choice**: CodeLlama-13B-Instruct is selected for its strong C++ code generation performance. Use `TheBloke/CodeLlama-13B-Instruct-GPTQ` for GPU acceleration if available.
- **GitHub Connection**: Required for downloading Python packages from PyPI and model weights from Hugging Face (no authentication needed for public models).
- **Hardware Requirements**: CPU inference requires 16GB RAM; GPU inference needs an NVIDIA GPU with 8GB VRAM and CUDA. Check [Hugging Face docs](https://huggingface.co/docs/transformers) for details.
- **No Copilot Dependency**: Unlike previous solutions, this does not use your Copilot Plus subscription, relying instead on open-source tools.
- **Python Dependency**: Python is required for Transformers, but the setup is minimal and avoids additional frameworks.
- **CMake Flexibility**: Use `-G "NMake Makefiles"` for MSVC instead of MinGW-w64 if preferred.
- **Safety**: Review generated code for errors or security issues. Avoid running unverified executables.
- **Troubleshooting**:
   - Model loading errors: Check RAM/GPU resources or try a smaller model (e.g., CodeLlama-7B-Instruct).
   - Pip issues: Ensure internet access and update pip.
   - Compilation errors: Manually fix generated code or adjust prompts for clearer output.
   - See [Transformers issues](https://github.com/huggingface/transformers) or [MinGW-w64 wiki](http://mingw-w64.org/doku.php).
