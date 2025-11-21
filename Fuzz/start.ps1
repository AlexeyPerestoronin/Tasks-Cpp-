# Check if Python is installed
try {
    $pythonCmd = Get-Command python -ErrorAction Stop
} catch {
    Write-Host "Python not found. Please install Python from https://www.python.org/downloads/"
    Read-Host "Press Enter to continue"
    exit 1
}

# Check if pip is available
& python -m pip --version > $null 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Host "pip not available. Please ensure pip is installed."
    Read-Host "Press Enter to continue"
    exit 1
}

# Check if venv module is available, if not install virtualenv
& python -c "import venv" > $null 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Host "venv module not available. Installing virtualenv..."
    & python -m pip install virtualenv
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Failed to install virtualenv. Please check your Python installation."
        Read-Host "Press Enter to continue"
        exit 1
    }
    $USE_VENV = $false
} else {
    $USE_VENV = $true
}

# Create virtual environment if not exists
if (!(Test-Path .venv)) {
    Write-Host "Creating virtual environment..."
    if ($USE_VENV) {
        & python -m venv .venv
    } else {
        & virtualenv .venv
    }
}

# Activate virtual environment
. .\.venv\Scripts\Activate.ps1

# Install requirements
& python -m pip install -r requirements.txt

# print active invoke parameters
& invoke get-info

# List available invoke commands
& invoke --list
