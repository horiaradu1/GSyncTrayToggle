param (
    [Parameter(Mandatory = $true)]
    [string]$exePath
)

if (-not (Test-Path $exePath)) {
    Write-Error "Executable not found at path: $exePath"
    exit 1
}

# Get the user's Startup folder
$startupFolder = [Environment]::GetFolderPath("Startup")

# Define the shortcut path
$shortcutName = [System.IO.Path]::GetFileNameWithoutExtension($exePath) + ".lnk"
$shortcutPath = Join-Path $startupFolder $shortcutName

# Create a WScript.Shell COM object
$wshShell = New-Object -ComObject WScript.Shell

# Create the shortcut
$shortcut = $wshShell.CreateShortcut($shortcutPath)
$shortcut.TargetPath = $exePath
$shortcut.WorkingDirectory = Split-Path $exePath
$shortcut.WindowStyle = 1
$shortcut.Save()

Write-Host "Shortcut created in Startup folder: $shortcutPath"

# Example .\Add-ToStartup.ps1 -exePath "C:\Path\To\GSyncTrayToggle.exe"

