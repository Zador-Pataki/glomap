# setup PYTHON_EXECUTABLE

# Find Python interpreter and development libraries (needed for version info)
# Using the newer FindPython module is generally preferred if available
find_package(Python 3.8 COMPONENTS Interpreter Development REQUIRED)
message(STATUS "Using Python Executable: ${Python_EXECUTABLE}")
message(STATUS "Using Python Include Directories: ${Python_INCLUDE_DIRS}")
message(STATUS "Using Python Library: ${Python_LIBRARIES}")

# Add pybind11 submodule and find the package
add_subdirectory(pybind11) # Assumes pybind11 is a subdirectory
find_package(pybind11 CONFIG REQUIRED)

# Find COLMAP dependency
find_package(colmap REQUIRED)

# Find all .cc source files recursively in the current directory (pyglomap/)
file(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cc")
message(STATUS "Source files for pyglomap: ${SOURCE_FILES}")

# Create the Python module using pybind11's function
pybind11_add_module(pyglomap MODULE ${SOURCE_FILES})

# Link the module against required libraries
target_link_libraries(pyglomap PRIVATE 
    glomap          # Link against the main glomap library
    pybind11::module # Link against pybind11
    colmap::colmap  # Link against colmap
    Eigen3::Eigen   # Link against Eigen
    ${CERES_LIBRARIES} # Link against Ceres
)

# Ensure C++17 standard is used
target_compile_features(pyglomap PRIVATE cxx_std_17)



# Python_SITELIB is typically the correct site-packages directory found by CMake
message(STATUS "Python module install destination: ${Python_SITELIB}/pyglomap")

# Install the compiled Python module (.so file)
install(TARGETS pyglomap
        LIBRARY DESTINATION "${Python_SITELIB}/pyglomap" # <-- USE Python_SITELIB
        )

# Install the __init__.py file to make it a package
# Check if the file exists in the source directory first
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py")
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py"
            DESTINATION "${Python_SITELIB}/pyglomap" # <-- USE Python_SITELIB
            )
    message(STATUS "Installing __init__.py to ${Python_SITELIB}/pyglomap")
else()
    message(WARNING "__init__.py not found - Python package might not be importable correctly.")
endif()
# --- ^^^ END OF CORRECTED INSTALL RULES ^^^ ---