#!/bin/bash

iterate_to_vehiclecode() {
    while [ "$PWD" != "/" ]; do
        # Check if the current directory is "VehicleCode"
        if [ "$(basename "$PWD")" = "VehicleCode" ]; then
            echo "Reached 'VehicleCode' directory."
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
    echo "Usage: $0 <filename>"
    exit 1
fi

# Get the filename from command-line argument
filename="$1"



# Check if the file exists in the current directory
if [ -e "$filename" ]; then
    iterate_to_vehiclecode

    if [ $? -eq 0 ]; then
        # Find and print full paths of all instances of the file
        find . -type f -name "$filename" -exec readlink -f {} \;
    
        # Ask for confirmation
        read -p "We will replace these files. Continue? (Y/N): " answer
        if [ "$answer" != "Y" ] && [ "$answer" != "y" ]; then
            echo "Exiting."
            exit 0
    fi

    # Replace instances of the file name in all subdirectories
    find . -type f -exec sed -i "s/$filename/$(basename "$filename")/g" {} +
else
    echo "File '$filename' does not exist in the current directory."
fi
