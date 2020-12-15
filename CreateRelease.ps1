$ErrorActionPreference = "Stop"

$root = Split-Path -Parent $PSCommandPath
Push-Location $root

$vsPath = .\vswhere.exe -latest -requires 'Microsoft.Component.MSBuild' -property installationPath
if ($vsPath -eq $null) {
    Write-Host "Failed to find Visual Studio Install"
    Pop-Location
    exit -1
}
$vsPath = Join-Path $vsPath 'MSBuild\Current\Bin\MSBuild.exe'

& $vsPath .\AlteryxAbacus.sln /t:Rebuild /p:Configuration=Release
if ($LASTEXITCODE -ne 0) {
    Write-Host "Build Failed"
    Pop-Location
    exit -1
}

Copy-Item .\x64\Release\AlteryxAbacus.dll .

& .\Install.bat
if ($LASTEXITCODE -ne 0) {
    Pop-Location
    exit -1
}

.\RunUnitTests.ps1
if ($LASTEXITCODE -ne 0) {
    Pop-Location
    exit -1
}

$dllFile = Join-Path $root "AlteryxAbacus.dll"
$version = [System.Diagnostics.FileVersionInfo]::GetVersionInfo($dllFile).FileVersion

Write-Host "Building ReadMe.pdf ..."
& pandoc -f gfm -t pdf README.md -o README.pdf
if ($LASTEXITCODE -ne 0) {
    $message = "Documentation failed (you need pandoc): " + $LASTEXITCODE
    Write-Host $message
    Pop-Location
    exit -1
}

$readMePdf = Join-Path $root "Readme.pdf"

Write-Host "Building Manual ..."
if (Test-Path  "$root\FunctionManual.md") {
    Remove-Item "$root\FunctionManual.md"
}

Get-Content "$root\..\AlteryxFormulaAddOns.wiki\Function-List.md" -Raw | Add-Content "$root\FunctionManual.md"
Get-ChildItem "$root\..\AlteryxFormulaAddOns.wiki\*.xml).md" | Get-Content -Raw | Add-Content "$root\FunctionManual.md"

$text = (Get-Content "$root\FunctionManual.md" -Raw)
$text = $text -replace "\[([^\]]+)\]\([^#]+#([^)]+)\)", '[$1](#$2)'
Set-Content "$root\FunctionManual.md" $text
& pandoc -f gfm -t pdf FunctionManual.md -o Manual.pdf
Remove-Item "$root\FunctionManual.md"

$readMePdf = Join-Path $root "Manual.pdf"

Write-Host "Removing bak files ..."
Remove-Item *.bak -Recurse

$output = "$root\AlteryxAbacus v$version.zip"
Compress-Archive -Path ("$root\*.dll", "$root\*Utils.xml", "$root\README.pdf", "$root\Manual.pdf", "$root\Install.bat", "$root\Install Win7.bat", "$root\Installer.ps1", "$root\Uninstall.bat", "$root\Uninstall Win7.bat", "$root\Uninstaller.ps1") -DestinationPath $output -Verbose -Update
Remove-Item "$root\README.pdf"
Remove-Item "$root\Manual.pdf"

$output = "$root\AlteryxAbacus v$version Tests.zip"
Compress-Archive -Path ("$root\*.Test", "$root\*.yxm*", "*.png") -DestinationPath $output -Verbose -Update

Pop-Location