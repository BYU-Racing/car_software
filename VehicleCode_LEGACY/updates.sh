#!/bin/bash

iterate_to_vehiclecode() {
    while [ "$PWD" != "/" ]; do
        # Check if the current directory is "VehicleCode"
        if [ "$(basename "$PWD")" = "VehicleCode" ]; then
            return 0  # Reached "VehicleCode" directory, return success
        fi
        # Move up one directory
        cd ..
    done
    
    echo "Failed to find 'VehicleCode' directory."
    return 1  # "VehicleCode" directory not found, return failure
}


# Check if filename argument is provided
if [ $# -eq 0 ]; then
    echo "Please include the file name you would like to sync:"
    echo "Usage: $0 <file_path>"
    exit 1
fi

# Get the filename from command-line argument
desired_path="$1"
# echo "Desired Path: $desired_path"


# Check if the path exists and is a file
if [ ! -f "$desired_path" ]; then
    echo "Error: The provided path is not valid."
    exit 1
fi



# Check if the file exists in the current directory
filename=$(basename "$desired_path")
echo
echo "Desired File: $filename"
iterate_to_vehiclecode

if [ $? -eq 0 ]; then
    # Find and print full paths of all instances of the file
    file_paths=$(find . -type f -name "$filename" -exec realpath --relative-to="$PWD" {} \;)
    length=$(echo "$file_paths" | wc -l)
    ((length--))
    echo "-------------"
    find . -type f -name "$filename" -exec realpath --relative-to="$PWD" {} \;
    echo "-------------"
    
    # Ask for confirmation
    echo "Replacing the $length file(s) in this list (excluding the original)."
    read -p "This action cannot be undone. Continue? (y/n): " answer
    if [ "$answer" != "Y" ] && [ "$answer" != "y" ]; then
        echo "Canceled."
        exit 0
    fi
    echo
fi

# Iterate over each file path and replace the file
echo "$file_paths" | while IFS= read -r file_path; do
    echo "Replacing file: $file_path"
    cp "$desired_path" "$file_path"
done
echo "Done."
