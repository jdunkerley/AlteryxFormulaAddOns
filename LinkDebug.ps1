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

$files = Get-ChildItem "$root\*.xml" 
if ($files -is [System.IO.FileSystemInfo]) {
    $files = @($files)
}
$files += Get-ChildItem "$root\x64\Debug\*.dll"

$cmd = ""
foreach ($dir in $bins) {
    $bin = Join-Path $dir "\RuntimeData\FormulaAddIn"
    Write-Host "Linking to $bin ..."
    $cmd = "$cmd pushd ""$bin"" &"

    foreach ($file in $files) {
        $name = Split-Path $file -leaf
        $path = Join-Path $bin $name

        if (Test-Path $path) {
            Write-Host "Removing Existing $path ..."
            $cmd = "$cmd del ""$path"" &"
        }

        Write-Host "Linking $path ..."
        $cmd = "$cmd mklink /H ""$path"" ""$file"" &"
    }

    $cmd = "$cmd popd &"
}

if ($cmd -ne "") {
    Start-Process cmd -ArgumentList "/c $cmd" -verb RunAs -wait
}

Pop-Location
exit 0
