#!/bin/bash

# Helper function to print error messages and exit
function error_exit {
    echo "Error: $1" >&2
    exit 1
}

# Check if curl is installed
if ! command -v curl &>/dev/null; then
    error_exit "curl is not installed. Please install curl and try again."
fi

# Clone the WLED-Controller repository if not already cloned
if [ ! -d "WLED-Controller" ]; then
    git clone https://github.com/azaslavskis/WLED-Controller.git || error_exit "Failed to clone WLED-Controller repository."
fi

cd WLED-Controller || error_exit "WLED-Controller directory not found."

# Navigate to software/WLED-Git_patch
if [ ! -d "software/WLED-Git_patch" ]; then
    error_exit "Directory software/WLED-Git_patch not found. Please check the repository structure."
fi

cd software/WLED-Git_patch || error_exit "Failed to enter software/WLED-Git_patch."

# Install NVM (Node Version Manager)
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.1/install.sh | bash || error_exit "Failed to download and install NVM."

export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion

# Install Node.js using NVM
nvm install node || error_exit "Failed to install Node.js."

# Clone the WLED repository if not already cloned
if [ ! -d "WLED" ]; then
    git clone https://github.com/Aircoookie/WLED.git || error_exit "Failed to clone WLED repository."
fi

# Check if the patch file exists
if [ ! -f "wled_patch.patch" ]; then
    error_exit "wled_patch.patch not found in software/WLED-Git_patch."
fi

# Move the patch file to the WLED directory
mv wled_patch.patch ./WLED/wled_patch.patch || error_exit "Failed to move wled_patch.patch to WLED directory."

cd WLED || error_exit "Failed to enter WLED directory."

# Apply the patch
git apply --reject --whitespace=fix wled_patch.patch || error_exit "Failed to apply the patch."

# Install Node.js dependencies
npm install || error_exit "Failed to install Node.js dependencies."

# Build the project using PlatformIO
pio run -e esp32c3dev || error_exit "Failed to build the project using PlatformIO."

echo "Setup completed successfully!"
