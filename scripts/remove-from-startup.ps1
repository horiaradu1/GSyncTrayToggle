$shortcutPath = Join-Path ([Environment]::GetFolderPath("Startup")) "GSyncTrayToggle.lnk"
Remove-Item $shortcutPath -ErrorAction SilentlyContinue
Write-Host "GSyncTrayToggle shortcut removed from Startup."
