param([string]$mode = "ROOT")
$ErrorActionPreference = "Stop"

$root = Split-Path -Parent $PSCommandPath
Push-Location $root

$bins = @()

Write-Host "Finding Alteryx Admin Install Location..."
$reg = Get-ItemProperty HKLM:\SOFTWARE\WOW6432Node\SRC\Alteryx -ErrorAction SilentlyContinue
if ($reg -ne $null -and $reg.InstallDir64 -ne $null) {
    $bins += $reg.InstallDir64
}

Write-Host "Finding Alteryx User Install Location..."
$reg = Get-ItemProperty HKCU:\SOFTWARE\SRC\Alteryx -ErrorAction SilentlyContinue
if ($reg -ne $null -and $reg.InstallDir64 -ne $null) {
    $bins += $reg.InstallDir64
}

if ($bins.Count -eq 0) {
    Write-Host "Failed to find Alteryx Install"
    Pop-Location
    exit -1
}

$files = Get-ChildItem "$root\*.xml" | Select -ExpandProperty FullName
if ($files -is [string]) { $files = @($files) }
if ($mode.ToUpper() -eq "DEBUG") { $files += Get-ChildItem "$root\x64\Debug\*.dll" | Select -ExpandProperty FullName }
if ($mode.ToUpper() -eq "RELEASE") { $files += Get-ChildItem "$root\x64\Release\*.dll" | Select -ExpandProperty FullName }
if ($mode.ToUpper() -eq "ROOT") { $files += Get-ChildItem "$root\*.dll" | Select -ExpandProperty FullName }
Unblock-File $files

foreach ($bin in $bins) {
    if (Test-Path "$bin\RuntimeData\FormulaAddIn" -and Test-Path "$bin\AlteryxGui.exe")
    {
        Write-Host "Installing current version to $bin ..."
        Copy-Item $files -Destination "$bin\RuntimeData\FormulaAddIn" -Verbose
    }
}

Pop-Location
exit 0
