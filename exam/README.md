# C++ Code Generator with Python Transformers in Windows Terminal (CPU-Only)

This project provides a lightweight setup to generate C++ code in the Windows terminal using the **Transformers** library in Python, leveraging the **CodeLlama-13B-Instruct** model for high-quality C++ code generation. The setup is optimized for CPU-only environments (no GPU required), requiring Python installation via the terminal, adding it to the PATH, and installing dependencies through a GitHub-connected package index (PyPI). Generated code is built and tested using **CMake** and **MinGW-w64**. The solution is designed for users with a GitHub connection for package downloads and a Windows environment without a GPU.

## Prerequisites

- **Python 3.10+**: Required for running the Transformers library, installed via terminal.
- **MinGW-w64**: C++ compiler for building generated code.
- **CMake**: For building the C++ code.
- **GitHub Connection**: Internet access to download Python packages from PyPI and model weights from Hugging Face.
- **Hardware**: 16GB RAM minimum (32GB recommended) for CPU inference of the CodeLlama-13B-Instruct model.
- **Windows Terminal or Command Prompt**: For executing commands.
- **curl or PowerShell**: For downloading the Python installer via terminal.

## Installation

### Install Python and Add to PATH via Terminal
1. **Download the Python Installer**:
   - Open Command Prompt or Windows Terminal.
   - Use `curl` to download the latest Python 3.10+ installer (e.g., Python 3.12.4):
     ```cmd
     curl -o python-installer.exe https://www.python.org/ftp/python/3.12.4/python-3.12.4-amd64.exe
     ```
   - Alternatively, use PowerShell if `curl` is unavailable:
     ```powershell
     Invoke-WebRequest -Uri https://www.python.org/ftp/python/3.12.4/python-3.12.4-amd64.exe -OutFile python-installer.exe
     ```

2. **Install Python Silently**:
   - Run the installer with command-line arguments to install Python and add it to the PATH:
     ```cmd
     python-installer.exe /quiet InstallAllUsers=1 PrependPath=1 Include_test=0
     ```
   - This installs Python to `C:\Program Files\Python312` (or similar) and adds it to the system PATH.
   - Wait for the installation to complete (may take a few minutes; no GUI will appear).

3. **Verify Installation**:
   - Restart your terminal to apply PATH changes (close and reopen Command Prompt).
   - Check the Python version:
     ```cmd
     python --version
     ```
   - Expected output: `Python 3.12.4` (or similar).
   - Verify pip:
     ```cmd
     pip --version
     ```
   - Expected output: `pip 24.0 from ...` (or similar).

4. **Troubleshooting**:
   - If `python` or `pip` is not recognized, manually add Python to PATH:
     - Open Windows Settings > System > About > Advanced system settings > Environment Variables.
     - Under **System variables**, edit `Path` and add:
       - `C:\Program Files\Python312`
       - `C:\Program Files\Python312\Scripts`
     - Restart your terminal and re-run verification.
   - If the download fails, ensure internet access and verify the URL at [python.org/downloads](https://www.python.org/downloads/).
   - If the installer fails, run with administrative privileges:
     ```cmd
     start /wait python-installer.exe /quiet InstallAllUsers=1 PrependPath=1 Include_test=0
     ```
   - Check [python.org](https://www.python.org/) for additional help.

### Install MinGW-w64 (C++ Compiler)
1. **Download MinGW-w64**:
   - Visit [sourceforge.net/projects/mingw-w64](https://sourceforge.net/projects/mingw-w64/) or [mingw-w64.org](http://mingw-w64.org/doku.php/download).
   - Download `mingw-w64-install.exe` from SourceForge under **Files**.
