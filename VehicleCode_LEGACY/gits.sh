#!/bin/bash

# Check if argument is provided
if [ $# -eq 0 ]; then
    echo "Missing commit message:"
    echo "Usage: $0 <commit_message>"
    exit 1
fi

# Get the current branch name
branch=$(git rev-parse --abbrev-ref HEAD)
# Pull changes from the current branch
echo "Pulling from: $branch"
git pull origin "$branch"

# Add all changes
echo "Adding to the staging area"
git add .

# Commit changes with provided message
commit_message="$1"
echo
echo "Committing: '$commit_message'"
git commit -m "$commit_message"

# Push changes to the current branch
echo
echo "Pushing to branch: $branch"
git push origin "$branch"
