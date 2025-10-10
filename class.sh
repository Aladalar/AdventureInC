#!/bin/bash

# class.sh - Class management tool for AdventureInC project
# Usage: ./class.sh <command> [flags] <ClassName> <path>

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# ============================================
# UTILITY FUNCTIONS
# ============================================

# Capitalize first letter: input -> Input
capitalize() {
    echo "$1" | sed 's/^./\U&/'
}

# Lowercase: Input -> input
lowercase() {
    echo "$1" | tr '[:upper:]' '[:lower:]'
}

# Ask for confirmation
confirm() {
    local message="$1"
    echo -e "${YELLOW}${message} [y/N]${NC}"
    read -r response
    case "$response" in
        [yY][eE][sS]|[yY]) 
            return 0
            ;;
        *)
            echo -e "${RED}Cancelled.${NC}"
            return 1
            ;;
    esac
}

# Create header file
create_header() {
    local class_name="$1"
    local path="$2"
    local filename=$(lowercase "$class_name")
    local header_guard=$(echo "${class_name}_H" | tr '[:lower:]' '[:upper:]')
    local capitalized=$(capitalize "$class_name")
    
    local header_path="include/${path}/${filename}.h"
    
    # Create directory if needed
    mkdir -p "include/${path}"
    
    # Generate header content
    cat > "$header_path" << EOF
#ifndef ${header_guard}
#define ${header_guard}

/* TODO: Auto-generated */

class ${capitalized} {
public:
    ${capitalized}();
    ~${capitalized}();
};

#endif
EOF
    
    echo -e "${GREEN}✓ Created${NC} $header_path"
}

# Create cpp file
create_cpp() {
    local class_name="$1"
    local path="$2"
    local filename=$(lowercase "$class_name")
    local capitalized=$(capitalize "$class_name")
    
    local cpp_path="src/${path}/${filename}.cpp"
    local include_path="${path}/${filename}.h"
    
    # Create directory if needed
    mkdir -p "src/${path}"
    
    # Generate cpp content
    cat > "$cpp_path" << EOF
#include "${include_path}"
#include "utilities/logger.h"

/* TODO: Auto-generated */

${capitalized}::${capitalized}() {
}

${capitalized}::~${capitalized}() {
}
EOF
    
    echo -e "${GREEN}✓ Created${NC} $cpp_path"
    echo "$cpp_path"  # Return path for CMake registration
}

# Add cpp file to CMakeLists.txt
add_to_cmake() {
    local cpp_path="$1"
    local cmake_file="CMakeLists.txt"
    
    # Check if already in CMakeLists
    if grep -q "$cpp_path" "$cmake_file"; then
        echo -e "${YELLOW}⚠ Already in CMakeLists.txt${NC}"
        return
    fi
    
    # Find add_executable and add before closing parenthesis
    if grep -q "add_executable" "$cmake_file"; then
        # Use sed to add before the last closing parenthesis of add_executable
        sed -i "/add_executable/,/)/{
            /)/i\\    $cpp_path
        }" "$cmake_file"
        echo -e "${GREEN}✓ Added to CMakeLists.txt${NC}"
    else
        echo -e "${RED}✗ Could not find add_executable in CMakeLists.txt${NC}"
        echo -e "${YELLOW}  Please manually add: $cpp_path${NC}"
    fi
}

# Remove cpp file from CMakeLists.txt
remove_from_cmake() {
    local cpp_path="$1"
    local cmake_file="CMakeLists.txt"
    
    if grep -q "$cpp_path" "$cmake_file"; then
        sed -i "\|$cpp_path|d" "$cmake_file"
        echo -e "${GREEN}✓ Removed from CMakeLists.txt${NC}"
    else
        echo -e "${YELLOW}⚠ Not found in CMakeLists.txt${NC}"
    fi
}

# ============================================
# COMMAND FUNCTIONS
# ============================================

cmd_add() {
    local flag="$1"
    local class_name="$2"
    local path="$3"
    
    if [ -z "$class_name" ] || [ -z "$path" ]; then
        echo -e "${RED}Error: Missing arguments${NC}"
        echo "Usage: ./class.sh add [-h|-cpp] ClassName path/to/location"
        exit 1
    fi
    
    local create_h=true
    local create_cpp=true
    
    case "$flag" in
        -h)
            create_cpp=false
            ;;
        -cpp)
            create_h=false
            ;;
        *)
            # No flag or invalid flag, create both
            if [ -n "$flag" ] && [ "$flag" != "-h" ] && [ "$flag" != "-cpp" ]; then
                # Flag is actually the class name, shift arguments
                path="$class_name"
                class_name="$flag"
            fi
            ;;
    esac
    
    local cpp_path=""
    
    if [ "$create_h" = true ]; then
        create_header "$class_name" "$path"
    fi
    
    if [ "$create_cpp" = true ]; then
        cpp_path=$(create_cpp "$class_name" "$path")
        add_to_cmake "$cpp_path"
    fi
    
    echo -e "${GREEN}Done!${NC}"
}

cmd_remove() {
    local flag="$1"
    local class_name="$2"
    local path="$3"
    
    if [ -z "$class_name" ] || [ -z "$path" ]; then
        echo -e "${RED}Error: Missing arguments${NC}"
        echo "Usage: ./class.sh remove [-h|-cpp] ClassName path/to/location"
        exit 1
    fi
    
    local remove_h=true
    local remove_cpp=true
    
    case "$flag" in
        -h)
            remove_cpp=false
            ;;
        -cpp)
            remove_h=false
            ;;
        *)
            if [ -n "$flag" ] && [ "$flag" != "-h" ] && [ "$flag" != "-cpp" ]; then
                path="$class_name"
                class_name="$flag"
            fi
            ;;
    esac
    
    local filename=$(lowercase "$class_name")
    local header_path="include/${path}/${filename}.h"
    local cpp_path="src/${path}/${filename}.cpp"
    
    # Show what will be deleted
    echo -e "${YELLOW}Will remove:${NC}"
    [ "$remove_h" = true ] && [ -f "$header_path" ] && echo "  - $header_path"
    [ "$remove_cpp" = true ] && [ -f "$cpp_path" ] && echo "  - $cpp_path"
    [ "$remove_cpp" = true ] && echo "  - Entry in CMakeLists.txt"
    
    if ! confirm "Are you sure?"; then
        exit 0
    fi
    
    if [ "$remove_h" = true ] && [ -f "$header_path" ]; then
        rm "$header_path"
        echo -e "${GREEN}✓ Removed${NC} $header_path"
    fi
    
    if [ "$remove_cpp" = true ]; then
        if [ -f "$cpp_path" ]; then
            rm "$cpp_path"
            echo -e "${GREEN}✓ Removed${NC} $cpp_path"
        fi
        remove_from_cmake "$cpp_path"
    fi
    
    echo -e "${GREEN}Done!${NC}"
}

cmd_move() {
    local class_name="$1"
    local old_path="$2"
    local new_path="$3"
    
    if [ -z "$class_name" ] || [ -z "$old_path" ] || [ -z "$new_path" ]; then
        echo -e "${RED}Error: Missing arguments${NC}"
        echo "Usage: ./class.sh move ClassName old/path new/path"
        exit 1
    fi
    
    local filename=$(lowercase "$class_name")
    local old_header="include/${old_path}/${filename}.h"
    local old_cpp="src/${old_path}/${filename}.cpp"
    local new_header="include/${new_path}/${filename}.h"
    local new_cpp="src/${new_path}/${filename}.cpp"
    
    # Check if files exist
    if [ ! -f "$old_header" ] && [ ! -f "$old_cpp" ]; then
        echo -e "${RED}✗ No files found at $old_path${NC}"
        exit 1
    fi
    
    echo -e "${YELLOW}Will move:${NC}"
    [ -f "$old_header" ] && echo "  $old_header → $new_header"
    [ -f "$old_cpp" ] && echo "  $old_cpp → $new_cpp"
    
    if ! confirm "Continue?"; then
        exit 0
    fi
    
    # Create new directories
    mkdir -p "include/${new_path}"
    mkdir -p "src/${new_path}"
    
    # Move header
    if [ -f "$old_header" ]; then
        mv "$old_header" "$new_header"
        echo -e "${GREEN}✓ Moved${NC} header"
    fi
    
    # Move and update cpp
    if [ -f "$old_cpp" ]; then
        # Update include path in cpp file
        sed -i "s|#include \"${old_path}/${filename}.h\"|#include \"${new_path}/${filename}.h\"|" "$old_cpp"
        
        # Move file
        mv "$old_cpp" "$new_cpp"
        echo -e "${GREEN}✓ Moved${NC} cpp"
        
        # Update CMakeLists.txt
        remove_from_cmake "$old_cpp"
        add_to_cmake "$new_cpp"
    fi
    
    echo -e "${GREEN}Done!${NC}"
}

cmd_rename() {
    local old_name="$1"
    local new_name="$2"
    local path="$3"
    
    if [ -z "$old_name" ] || [ -z "$new_name" ] || [ -z "$path" ]; then
        echo -e "${RED}Error: Missing arguments${NC}"
        echo "Usage: ./class.sh rename OldName NewName path/to/location"
        exit 1
    fi
    
    local old_filename=$(lowercase "$old_name")
    local new_filename=$(lowercase "$new_name")
    local old_cap=$(capitalize "$old_name")
    local new_cap=$(capitalize "$new_name")
    
    local old_header="include/${path}/${old_filename}.h"
    local old_cpp="src/${path}/${old_filename}.cpp"
    local new_header="include/${path}/${new_filename}.h"
    local new_cpp="src/${path}/${new_filename}.cpp"
    
    if [ ! -f "$old_header" ] && [ ! -f "$old_cpp" ]; then
        echo -e "${RED}✗ No files found for $old_name at $path${NC}"
        exit 1
    fi
    
    echo -e "${YELLOW}Will rename:${NC}"
    echo "  $old_name → $new_name"
    [ -f "$old_header" ] && echo "  $old_header → $new_header"
    [ -f "$old_cpp" ] && echo "  $old_cpp → $new_cpp"
    
    if ! confirm "Continue?"; then
        exit 0
    fi
    
    # Rename and update header
    if [ -f "$old_header" ]; then
        # Update header guard and class name
        local old_guard=$(echo "${old_name}_H" | tr '[:lower:]' '[:upper:]')
        local new_guard=$(echo "${new_name}_H" | tr '[:lower:]' '[:upper:]')
        
        sed -i "s/${old_guard}/${new_guard}/g" "$old_header"
        sed -i "s/class ${old_cap}/class ${new_cap}/g" "$old_header"
        sed -i "s/${old_cap}::/${new_cap}::/g" "$old_header"
        sed -i "s/${old_cap}()/${new_cap}()/g" "$old_header"
        sed -i "s/~${old_cap}/~${new_cap}/g" "$old_header"
        
        mv "$old_header" "$new_header"
        echo -e "${GREEN}✓ Renamed${NC} header"
    fi
    
    # Rename and update cpp
    if [ -f "$old_cpp" ]; then
        # Update include path and class name
        sed -i "s|#include \"${path}/${old_filename}.h\"|#include \"${path}/${new_filename}.h\"|" "$old_cpp"
        sed -i "s/${old_cap}::/${new_cap}::/g" "$old_cpp"
        
        mv "$old_cpp" "$new_cpp"
        echo -e "${GREEN}✓ Renamed${NC} cpp"
        
        # Update CMakeLists.txt
        remove_from_cmake "$old_cpp"
        add_to_cmake "$new_cpp"
    fi
    
    echo -e "${GREEN}Done!${NC}"
}

# ============================================
# MAIN
# ============================================

show_usage() {
    cat << EOF
${GREEN}Class Management Tool${NC}

Usage:
  ./class.sh add [-h|-cpp] ClassName path/to/location
  ./class.sh remove [-h|-cpp] ClassName path/to/location
  ./class.sh move ClassName old/path new/path
  ./class.sh rename OldName NewName path/to/location

Commands:
  add       Create new class files
  remove    Delete class files (asks for confirmation)
  move      Move class to new location
  rename    Rename class files and update references

Flags (for add/remove):
  -h        Header only (.h)
  -cpp      Implementation only (.cpp)
  (none)    Both files

Examples:
  ./class.sh add Input managers
  ./class.sh add -h Region world
  ./class.sh remove TestScene world/testRegion/scenes
  ./class.sh move Input managers/old managers/new
  ./class.sh rename OldInput Input managers

EOF
}

# Parse command
case "$1" in
    add)
        shift
        cmd_add "$@"
        ;;
    remove)
        shift
        cmd_remove "$@"
        ;;
    move)
        shift
        cmd_move "$@"
        ;;
    rename)
        shift
        cmd_rename "$@"
        ;;
    -h|--help|help|"")
        show_usage
        ;;
    *)
        echo -e "${RED}Unknown command: $1${NC}"
        show_usage
        exit 1
        ;;
esac