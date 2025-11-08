#!/bin/bash

# Check if commit message is provided
if [ -z "$1" ]; then
  echo "Usage: $0 \"commit message\""
  exit 1
fi

COMMIT_MSG="$1"
# FOLDER="vLLM-characterization"

# # Save current directory (repo root where you run the script)
# CURR_DIR=$(pwd)

# # Move into repo folder
# cd "../$FOLDER" || { echo "Folder $FOLDER not found!"; exit 1; }

# Pull latest changes
git pull

# Add all files inside the repo
git add .

# Commit with provided message
git commit -m "$COMMIT_MSG"

# Push changes
git push

# # Return to original directory
# cd "$CURR_DIR"
