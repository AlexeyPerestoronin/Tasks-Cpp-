#!/bin/bash

# check OS has python3 (install if not)
if ! command -v python3 > /dev/null 2>&1; then
    echo "Python3 not found. Installing..."
    sudo apt update
    sudo apt install -y python3
fi

# check OS has python3-venv module for python (install if not)
if ! python3 -c "import venv" > /dev/null 2>&1; then
    echo "python3-venv not found. Installing..."
    sudo apt install -y python3-venv
fi

# create virtual environment for python if not created
if [ ! -d .venv ]; then
    echo "Creating virtual environment..."
    python3 -m venv .venv
fi

# activation python virtual environment if it is exists
source .venv/bin/activate
# check all requirements from requirements.txt (install if not)
pip install -r requirements.txt
# print active invoke parameters
invoke get-info
# print list of available invoke commands
invoke --list
