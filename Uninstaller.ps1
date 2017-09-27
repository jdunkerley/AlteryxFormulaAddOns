$bins = @()
$ErrorActionPreference = "Stop"

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
    exit -1
}

$files = @()
$files += "RuntimeData\FormulaAddIn\Random.xml" 
$files += "RuntimeData\FormulaAddIn\MathUtils.xml" 
$files += "RuntimeData\FormulaAddIn\MiscUtils.xml" 
$files += "RuntimeData\FormulaAddIn\StringUtils.xml" 
$files += "RuntimeData\FormulaAddIn\DateUtils.xml" 
$files += "RuntimeData\FormulaAddIn\JDFormulaAddIn.dll" 
$files += "RuntimeData\FormulaAddIn\AlteryxAbacus.dll" 

foreach ($bin in $bins) {
    Write-Host "Uninstalling from $bin ..."
    foreach ($file in $files) {
        $target = Join-Path $bin $file
        if (Test-Path $target) {
            Remove-Item $target
        }
    }
}

exit 0