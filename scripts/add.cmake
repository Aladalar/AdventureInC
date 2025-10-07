# Usage: cmake -DCLASS_NAME=Name [-DCLASS_PATH=path] [-DFLAG=-h|-cpp] -P add_class.cmake

if(NOT DEFINED CLASS_NAME)
    message(FATAL_ERROR "Usage: cmake -DCLASS_NAME=Name [-DCLASS_PATH=path] [-DFLAG=-h|-cpp] -P add_class.cmake")
endif()

# Default to root if no path provided
if(NOT DEFINED CLASS_PATH OR CLASS_PATH STREQUAL "")
    set(CLASS_PATH "")
    set(HEADER_FULL_PATH "include/${CLASS_NAME}.h")
    set(CPP_FULL_PATH "src/${CLASS_NAME}.cpp")
    set(INCLUDE_PATH "${CLASS_NAME}.h")
else()
    set(HEADER_FULL_PATH "include/${CLASS_PATH}/${CLASS_NAME}.h")
    set(CPP_FULL_PATH "src/${CLASS_PATH}/${CLASS_NAME}.cpp")
    set(INCLUDE_PATH "${CLASS_PATH}/${CLASS_NAME}.h")
endif()

# Show what will be created and ask confirmation
message(STATUS "")
message(STATUS "Will create:")
if(NOT DEFINED FLAG OR FLAG STREQUAL "")
    message(STATUS "  - ${HEADER_FULL_PATH}")
    message(STATUS "  - ${CPP_FULL_PATH}")
    message(STATUS "  - Register in CMakeLists.txt")
elseif(FLAG STREQUAL "-h")
    message(STATUS "  - ${HEADER_FULL_PATH}")
elseif(FLAG STREQUAL "-cpp")
    message(STATUS "  - ${CPP_FULL_PATH}")
    message(STATUS "  - Register in CMakeLists.txt")
endif()
message(STATUS "")
message(STATUS "Continue? (Press Enter or type 'yes')")

# Wait for user input
execute_process(
    COMMAND ${CMAKE_COMMAND} -E echo ""
)

# Read user confirmation (simplified - just proceeds)
# Note: CMake doesn't have easy interactive input, so this is a placeholder
# For real interactive prompt, use bash/powershell wrapper

# Determine what to create
set(CREATE_HEADER TRUE)
set(CREATE_CPP TRUE)
set(REGISTER_CMAKE FALSE)

if(DEFINED FLAG)
    if(FLAG STREQUAL "-h")
        set(CREATE_CPP FALSE)
    elseif(FLAG STREQUAL "-cpp")
        set(CREATE_HEADER FALSE)
        set(REGISTER_CMAKE TRUE)
    endif()
else()
    set(REGISTER_CMAKE TRUE)
endif()

# Create directories
if(CLASS_PATH)
    file(MAKE_DIRECTORY "include/${CLASS_PATH}")
    file(MAKE_DIRECTORY "src/${CLASS_PATH}")
endif()

# Create header
if(CREATE_HEADER)
    string(TOUPPER "${CLASS_NAME}_H" HEADER_GUARD)
    
    file(WRITE "${HEADER_FULL_PATH}" 
"#ifndef ${HEADER_GUARD}
#define ${HEADER_GUARD}

/* TODO: Auto-generated */

class ${CLASS_NAME} {
public:
    ${CLASS_NAME}();
    ~${CLASS_NAME}();
};

#endif
")
    message(STATUS "✓ Created ${HEADER_FULL_PATH}")
endif()

# Create cpp
if(CREATE_CPP)
    file(WRITE "${CPP_FULL_PATH}"
"#include \"${INCLUDE_PATH}\"

/* TODO: Auto-generated */

${CLASS_NAME}::${CLASS_NAME}() {
}

${CLASS_NAME}::~${CLASS_NAME}() {
}
")
    message(STATUS "✓ Created ${CPP_FULL_PATH}")
endif()

# Register in CMakeLists.txt
if(REGISTER_CMAKE)
    set(CMAKE_FILE "CMakeLists.txt")
    
    file(READ "${CMAKE_FILE}" CMAKE_CONTENT)
    
    string(FIND "${CMAKE_CONTENT}" "${CPP_FULL_PATH}" FOUND_POS)
    
    if(FOUND_POS EQUAL -1)
        string(REGEX MATCH "add_executable\\(\\$\\{PROJECT_NAME\\}[^)]*\\)" EXECUTABLE_SECTION "${CMAKE_CONTENT}")
        
        if(EXECUTABLE_SECTION)
            string(REPLACE ")" "\n    ${CPP_FULL_PATH}\n)" NEW_SECTION "${EXECUTABLE_SECTION}")
            string(REPLACE "${EXECUTABLE_SECTION}" "${NEW_SECTION}" NEW_CONTENT "${CMAKE_CONTENT}")
            
            file(WRITE "${CMAKE_FILE}" "${NEW_CONTENT}")
            message(STATUS "✓ Registered ${CPP_FULL_PATH} in CMakeLists.txt")
        else()
            message(WARNING "Could not find add_executable in CMakeLists.txt")
            message(STATUS "⚠ Manually add: ${CPP_FULL_PATH}")
        endif()
    else()
        message(STATUS "⚠ ${CPP_FULL_PATH} already in CMakeLists.txt")
    endif()
endif()