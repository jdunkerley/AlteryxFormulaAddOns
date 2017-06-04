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
    exit -1
}

$root = Split-Path -Parent $PSCommandPath

foreach ($bin in $bins) {
    Write-Host "Running Unit Tests with $bin..."
    $exe = Join-Path $bin "AlteryxEngineCmd.exe"
    $tests = Join-Path $root "RunUnitTests.yxmd"

    & $exe $tests
    if ($LASTEXITCODE -eq 2) {
        $message = "Unit Tests failed: " + $LASTEXITCODE
        Write-Host $message
        exit -2
    }

    Write-Host "Unit Tests Passed."
}

exit 0