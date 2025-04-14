# run-at-startup.ps1

$AppName = "GSyncTrayToggle"
$ExePath = "$PSScriptRoot\GSyncTrayToggle.exe"

$ExePathQuoted = '"' + $ExePath + '"'

Set-ItemProperty -Path "HKCU:\Software\Microsoft\Windows\CurrentVersion\Run" `
                 -Name $AppName `
                 -Value $ExePathQuoted

Write-Host "$AppName added to startup."