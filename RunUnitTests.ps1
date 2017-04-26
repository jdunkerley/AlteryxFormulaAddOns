$root = Split-Path -Parent $PSCommandPath
Push-Location $root

$bins = @()

Write-Host "Finding Alteryx Admin Install Location..."
$reg = Get-ItemProperty HKLM:\SOFTWARE\WOW6432Node\SRC\Alteryx -ErrorAction SilentlyContinue
if ($reg -ne $null) {
    $bins += $reg.InstallDir64
}

Write-Host "Finding Alteryx User Install Location..."
$reg = Get-ItemProperty HKCU:\SOFTWARE\SRC\Alteryx -ErrorAction SilentlyContinue
if ($reg -ne $null) {
    $bins += $reg.InstallDir64
}

if ($bins.Count -eq 0) {
    Write-Host "Failed to find Alteryx Install"
    Pop-Location
    exit -1
}

foreach ($bin in $bins) {
    Write-Host "Running Unit Tests with $bin..."
    & "$bin\AlteryxEngineCmd.exe" "$root\RunUnitTests.yxmd"
    if ($LASTEXITCODE -eq 2) {
        $message = "Unit Tests failed: " + $LASTEXITCODE
        Write-Host $message
        Pop-Location
        exit -2
    }

    Write-Host "Unit Tests Passed."
}

Pop-Location
exit 0