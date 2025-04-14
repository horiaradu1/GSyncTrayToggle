# remove-from-startup.ps1

$AppName = "GSyncTrayToggle"
$RunKeyPath = "HKCU:\Software\Microsoft\Windows\CurrentVersion\Run"

if (Get-ItemProperty -Path $RunKeyPath -Name $AppName -ErrorAction SilentlyContinue) {
    Remove-ItemProperty -Path $RunKeyPath -Name $AppName
    Write-Host "$AppName has been removed from startup."
} else {
    Write-Host "$AppName is not currently set to run at startup."
}
