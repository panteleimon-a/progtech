# C++ Code Generator with Python Transformers in Windows Terminal (CPU-Only)

This project provides a lightweight setup to generate C++ code in the Windows terminal using the **Transformers** library in Python, leveraging the **CodeLlama-13B-Instruct** model (or **CodeLlama-7B-Instruct** as a fallback) for high-quality C++ code generation. The setup is optimized for CPU-only environments (no GPU required), requiring Python installation via the terminal, adding it to the PATH, and installing dependencies through a GitHub-connected package index (PyPI). A standalone Windows executable (`.exe`) is created to generate C++ code from user prompts. Generated code is built and tested using **CMake** and **MinGW-w64**. The `meta-llama/CodeLlama-13B-Instruct-hf` model requires Hugging Face authentication due to its gated access; the non-gated `codellama/CodeLlama-7B-Instruct-hf` is provided as an alternative.

## Prerequisites

- **Python 3.10+**: Required for running the Transformers library, installed via terminal.
- **MinGW-w64**: C++ compiler for building generated code.
- **CMake**: For building the C++ code.
- **GitHub Connection**: Internet access to download Python packages from PyPI and model weights from Hugging Face.
- **Hugging Face Account**: Required for `meta-llama/CodeLlama-13B-Instruct-hf` (gated model); optional for `codellama/CodeLlama-7B-Instruct-hf`.
- **Hardware**: 16GB RAM minimum (32GB recommended) for CodeLlama-13B; 8GB RAM sufficient for CodeLlama-7B.
- **Windows Terminal or Command Prompt**: For executing commands.
- **curl or PowerShell**: For downloading installers.

## Installation

### Install Python and Add to PATH via Terminal
1. **Download the Python Installer**:
   - Open Command Prompt or Windows Terminal.
   - Use `curl` to download Python 3.12.4:
     ```cmd
     curl -o python-installer.exe https://www.python.org/ftp/python/3.12.4/python-3.12.4-amd64.exe
     ```
   - Or PowerShell:
     ```powershell
     Invoke-WebRequest -Uri https://www.python.org/ftp/python/3.12.4/python-3.12.4-amd64.exe -OutFile python-installer.exe
     ```

2. **Install Python Silently**:
   - Run:
     ```cmd
     python-installer.exe /quiet InstallAllUsers=1 PrependPath=1 Include_test=0
     ```
   - Installs to `C:\Program Files\Python312` with PATH configured.
   - Wait a few minutes (no GUI).

3. **Verify Installation**:
   - Restart terminal.
   - Check:
     ```cmd
     python --version
     ```
     - Output: `Python 3.12.4`.
   - Verify pip:
     ```cmd
     pip --version
     ```
     - Output: `pip 24.0 from ...`.

4. **Troubleshooting**:
   - If commands fail, manually add to PATH:
     - Settings > System > About > Advanced system settings > Environment Variables.
     - Edit `Path` (System variables), add:
       - `C:\Program Files\Python312`
       - `C:\Program Files\Python312\Scripts`
     - Restart terminal.
   - If download fails, check [python.org/downloads](https://www.python.org/downloads/).
   - Run with admin privileges if needed:
     ```cmd
     start /wait python-installer.exe /quiet InstallAllUsers=1 PrependPath=1 Include_test=0
     ```
   - See [python.org](https://www.python.org/).

### Install MinGW-w64 (C++ Compiler)
1. **Download MinGW-w64**:
   - Run:
     ```cmd
     curl -o mingw-installer.exe https://sourceforge.net/projects/mingw-w64/files/latest/download
     ```
   - Or PowerShell:
     ```powershell
     Invoke-WebRequest -Uri https://sourceforge.net/projects/mingw-w64/files/latest/download -OutFile mingw-installer.exe
     ```

2. **Run the Installer**:
   - Run:
     ```cmd
     start mingw-installer.exe
     ```
   - Configure:
     - **Version**: Latest GCC (e.g., 8.1.0+).
     - **Architecture**: `x86_64`.
     - **Threads**: `posix`.
     - **Exception**: `seh`.
     - **Destination**: `C:\MinGW`.
     - **Components**: Select `gcc`, `g++`, `binutils`.
   - Click **Install**.

3. **Add to PATH**:
   - Settings > System > About > Advanced system settings > Environment Variables.
   - Edit `Path` (System variables), add `C:\MinGW\bin`.

4. **Verify Installation**:
   - Run:
     ```cmd
     g++ --version
     ```
     - Output: e.g., `g++ (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0`.
   - Test:
     ```cmd
     echo #include ^<iostream^> > test.cpp
     echo int main() { std::cout ^<^< "Hello, MinGW!\n"; return 0; } >> test.cpp
     g++ test.cpp -o test
     test.exe
     ```
     - Output: `Hello, MinGW!`.

5. **Troubleshooting**:
   - Ensure internet connectivity.
   - Verify `C:\MinGW\bin` contains `g++.exe`.
   - See [MinGW-w64 wiki](http://mingw-w64.org/doku.php).

### Install CMake
1. **Download CMake**:
   - Run:
     ```cmd
     curl -o cmake-installer.msi https://github.com/Kitware/CMake/releases/download/v3.28.3/cmake-3.28.3-windows-x86_64.msi
     ```
   - Or PowerShell:
     ```powershell
     Invoke-WebRequest -Uri https://github.com/Kitware/CMake/releases/download/v3.28.3/cmake-3.28.3-windows-x86_64.msi -OutFile cmake-installer.msi
     ```

2. **Install CMake Silently**:
   - Run:
     ```cmd
     msiexec /i cmake-installer.msi /quiet /norestart ADD_CMAKE_TO_PATH=System
     ```

3. **Verify Installation**:
   - Restart terminal and run:
     ```cmd
     cmake --version
     ```
     - Output: e.g., `cmake version 3.28.3`.

4. **Troubleshooting**:
   - Check URL at [cmake.org/download](https://cmake.org/download/).
   - Manually add `C:\Program Files\CMake\bin` to PATH.
   - Run with admin privileges:
     ```cmd
     start /wait msiexec /i cmake-installer.msi /quiet /norestart ADD_CMAKE_TO_PATH=System
     ```

### Set Up Hugging Face Authentication
1. **Create a Hugging Face Account**:
   - Visit [huggingface.co/join](https://huggingface.co/join) and sign up.
   - Verify your email.

2. **Request Access to CodeLlama-13B-Instruct**:
   - Go to [meta-llama/CodeLlama-13B-Instruct-hf](https://huggingface.co/meta-llama/CodeLlama-13B-Instruct-hf).
   - Click **Request Access** and agree to Meta AI’s terms (e.g., non-commercial use).
   - Wait for approval (typically instant to a few hours; check your email).

3. **Log In to Hugging Face**:
   - Install `huggingface_hub`:
     ```cmd
     pip install huggingface_hub
     ```
   - Log in via terminal:
     ```cmd
     huggingface-cli login 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
     ```
   - Paste your token and press Enter.
   - Verify login:
     ```cmd
     huggingface-cli whoami
     ```
     - Output: Your Hugging Face username.

5. **Troubleshooting**:
   - If access is denied, ensure you’ve accepted the model’s terms and received approval.
   - If login fails, regenerate the token or check [Hugging Face docs](https://huggingface.co/docs/hub/security-tokens).
   - If you prefer not to authenticate, use the non-gated `codellama/CodeLlama-7B-Instruct-hf` model (see Usage).

### Install Transformers, PyInstaller, and Dependencies
1. **Install Dependencies**:
   - Run:
     ```cmd
     pip install transformers torch pyinstaller huggingface_hub
     ```
   - Installs Transformers, PyTorch (CPU-only), PyInstaller, and `huggingface_hub`.

2. **Verify Installation**:
   - Test Transformers:
     ```cmd
     python -c "from transformers import pipeline; print('Transformers installed successfully')"
     ```
     - Output: `Transformers installed successfully`.
   - Test PyInstaller:
     ```cmd
     pyinstaller --version
     ```
     - Output: e.g., `PyInstaller 5.13.0`.

3. **Troubleshooting**:
   - If pip fails, update:
     ```cmd
     pip install --upgrade pip
     ```
   - See [Hugging Face docs](https://huggingface.co/docs/transformers) or [PyInstaller docs](https://pyinstaller.org/).

## Usage

Create a Python script to generate C++ code, convert it to a standalone `.exe` with Py
