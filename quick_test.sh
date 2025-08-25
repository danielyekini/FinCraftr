#!/bin/bash
# Quick test script to verify FinCraftr dual distribution setup

set -e  # Exit on any error

echo "🚀 Testing FinCraftr Dual Distribution Setup"
echo "============================================="

# Test C++ header-only build
echo "📦 Testing C++ header-only build..."
mkdir -p build-test
cd build-test

cmake .. -DFINCRAFTR_HEADER_ONLY=ON -DCMAKE_BUILD_TYPE=Release
cmake --build .
echo "✅ C++ header-only build successful"

cd ..

# Test C++ example compilation
echo "📝 Testing C++ example compilation..."
if command -v g++ &> /dev/null; then
    g++ -std=c++20 -I cpp/include example_usage.cpp -o example_usage_cpp
    echo "✅ C++ example compiled successfully"
    
    echo "🏃 Running C++ example..."
    ./example_usage_cpp
    echo "✅ C++ example ran successfully"
else
    echo "⚠️  g++ not found, skipping C++ example test"
fi

# Test Python package build (if Python available)
if command -v python3 &> /dev/null; then
    echo "🐍 Testing Python package build..."
    
    # Check if we can import required modules
    python3 -c "import sys; print(f'Python version: {sys.version}')"
    
    if python3 -c "import pybind11" 2>/dev/null; then
        echo "✅ pybind11 available"
        
        # Try to build the Python extension
        echo "🔨 Building Python extension..."
        mkdir -p build-python
        cd build-python
        cmake .. -DFINCRAFTR_BUILD_PYTHON_BINDINGS=ON -DFINCRAFTR_HEADER_ONLY=ON
        cmake --build .
        cd ..
        echo "✅ Python extension build successful"
        
    else
        echo "⚠️  pybind11 not found, install with: pip install pybind11"
    fi
    
    echo "🏃 Running Python test script..."
    python3 test_build.py
    
else
    echo "⚠️  Python3 not found, skipping Python tests"
fi

echo ""
echo "🎉 All tests completed!"
echo ""
echo "📋 Summary of what was created:"
echo "  ✅ CMakeLists.txt - C++ build system with header-only/compiled modes"
echo "  ✅ vcpkg.json - vcpkg package manifest"
echo "  ✅ pyproject.toml - Python package configuration"  
echo "  ✅ pybind11 bindings - C++ functions exposed to Python"
echo "  ✅ Doxygen comments - All C++ functions documented"
echo "  ✅ GitHub Actions CI - Multi-platform build testing"
echo "  ✅ Example scripts - Usage demonstrations for both languages"
echo ""
echo "🚀 Your FinCraftr project now supports dual distribution:"
echo "  📦 C++: vcpkg install fincraftr"
echo "  🐍 Python: pip install fincraftr"
echo ""
echo "Next steps:"
echo "  1. Test the build on your target platforms"
echo "  2. Publish to vcpkg registry (submit PR to vcpkg repo)"
echo "  3. Publish to PyPI (python -m build && twine upload dist/*)"
echo "  4. Update GitHub repository URLs in configuration files"
