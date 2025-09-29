#!/bin/bash

# Script to convert .h and .cpp files to UTF-8 encoding

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "Checking and converting C++ files to UTF-8..."

# Find all .h and .cpp files
find . -type f \( -name "*.h" -o -name "*.cpp" \) | while read -r file; do
    # Check current encoding
    encoding=$(file -b --mime-encoding "$file")
    
    if [ "$encoding" != "utf-8" ] && [ "$encoding" != "us-ascii" ]; then
        echo -e "${YELLOW}Converting: $file (from $encoding)${NC}"
        
        # Backup original file
        cp "$file" "$file.bak"
        
        # Convert to UTF-8
        iconv -f "$encoding" -t UTF-8 "$file.bak" > "$file"
        
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}✓ Successfully converted: $file${NC}"
            rm "$file.bak"
        else
            echo -e "${RED}✗ Failed to convert: $file${NC}"
            mv "$file.bak" "$file"
        fi
    else
        echo -e "${GREEN}✓ Already UTF-8: $file${NC}"
    fi
done

echo "Done!"