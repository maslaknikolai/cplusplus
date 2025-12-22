# C++ Linting Setup

This project now includes comprehensive linting and code formatting tools to ensure consistent, high-quality C++ code.

## Tools Configured

### 1. Clang-Tidy (Static Analysis)
- **Purpose**: Identifies potential bugs, performance issues, and style violations
- **Configuration**: [.clang-tidy](.clang-tidy)
- **Categories enabled**:
  - Bug-prone patterns
  - Core guidelines compliance
  - Performance optimizations
  - Readability improvements
  - Modern C++ best practices

### 2. Clang-Format (Code Formatting)
- **Purpose**: Automatically formats C++ code for consistency
- **Configuration**: [.clang-format](.clang-format)
- **Standards**: C++17 with 4-space indentation, 100-character line limit

### 3. CMake Integration
- **Automatic linting**: Code is analyzed during build when clang-tidy is available
- **Compile commands**: `compile_commands.json` generated for better IDE support
- **Custom targets**: `make lint` for manual linting

## Usage

### Option 1: Using the Convenience Script (Recommended)
```bash
# Run both formatting and linting
./lint.sh

# Format code only
./lint.sh format

# Run linting checks only  
./lint.sh check
```

### Option 2: Using CMake Targets
```bash
# Build with automatic linting
cd build && make

# Run linting only
cd build && make lint
```

### Option 3: Manual Commands
```bash
# Format code
clang-format -i *.cpp *.h

# Run linting
clang-tidy --config-file=.clang-tidy main.cpp -- -std=c++17
```

## Integration with VS Code

### Recommended Extensions
1. **C/C++ Extension**: `ms-vscode.cpptools`
2. **Clang-Format**: `xaver.clang-format`
3. **Clang-Tidy**: `notskm.clang-tidy`

### VS Code Settings
Add to your `.vscode/settings.json`:
```json
{
    "C_Cpp.codeAnalysis.clangTidy.enabled": true,
    "C_Cpp.codeAnalysis.clangTidy.path": "/opt/homebrew/opt/llvm/bin/clang-tidy",
    "editor.formatOnSave": true,
    "C_Cpp.clang_format_path": "/opt/homebrew/opt/llvm/bin/clang-format"
}
```

## Common Linting Issues and Fixes

### 1. Unused Headers
**Issue**: `included header vector is not used directly`
**Fix**: Remove unused `#include` statements

### 2. Variable Initialization
**Issue**: `variable 'choice' is not initialized`
**Fix**: Initialize variables at declaration
```cpp
int choice = 0;
```

### 3. Input Validation
**Issue**: `the value returned by this function should not be disregarded`
**Fix**: Check return values or cast to void
```cpp
(void)fflush(stdin);  // If intentionally ignoring return value
```

### 4. Function Linkage
**Issue**: `function can be made static`
**Fix**: Add `static` keyword for internal functions
```cpp
static void ShowBalance(double balance);
```

### 5. Braces Around Statements
**Issue**: `statement should be inside braces`
**Fix**: Add braces around single statements
```cpp
if (condition) {
    statement;
}
```

## Installation Requirements

### macOS (using Homebrew)
```bash
brew install llvm
```

### Linux (Ubuntu/Debian)
```bash
sudo apt install clang-tidy clang-format
```

### Windows
- Install LLVM from official website or use vcpkg
- Update paths in CMakeLists.txt accordingly

## Configuration Customization

### Modifying Linting Rules
Edit [.clang-tidy](.clang-tidy) to:
- Enable/disable specific checks
- Adjust severity levels
- Configure naming conventions
- Set function complexity limits

### Adjusting Code Style
Edit [.clang-format](.clang-format) to:
- Change indentation style
- Modify line length limits
- Adjust brace placement
- Configure spacing preferences

## CI/CD Integration

For automated quality checks, add to your CI pipeline:
```bash
# In GitHub Actions, GitLab CI, etc.
./lint.sh check
# Exit with error if linting fails
```

## Troubleshooting

### Clang-Tidy Not Found
- Ensure LLVM is installed
- Check paths in CMakeLists.txt
- Verify PATH environment variable

### Configuration Errors
- Validate YAML syntax in .clang-tidy
- Check for duplicate keys in .clang-format
- Use online YAML validators if needed

### Performance Issues
- Exclude system headers with `-header-filter` for faster analysis
- Use `-j` flag for parallel execution
- Consider disabling expensive checks for large codebases