$ErrorActionPreference = "Stop"

$root = Split-Path -Parent $PSCommandPath
Push-Location $root

Write-Host "Finding Alteryx Install Location..."
$reg = Get-ItemProperty HKLM:\SOFTWARE\WOW6432Node\SRC\Alteryx
$bin = $reg.InstallDir64

Write-Host "Installing current version to $bin ..."
& .\InstallAlteryxAbacus.exe "$root\*.dll" "$root\*.xml" "$bin\RuntimeData\FormulaAddIn"
if ($LASTEXITCODE -ne 0) {
    $message = "Installation failed: " + $LASTEXITCODE
    Write-Host $message
    Pop-Location
    exit -1
}

Write-Host "Running Unit Tests..."
& "C:\Program Files\Alteryx\bin\AlteryxEngineCmd.exe" "$root\RunUnitTests.yxmd"
if ($LASTEXITCODE -eq 2) {
    $message = "Unit Tests failed: " + $LASTEXITCODE
    Write-Host $message
    Pop-Location
    exit -2
}

$version = Read-Host "Unit Tests Passed. Enter version number (e.g. 1.3.2)"
while ($version -notmatch '^\d+\.\d+\.?\d*$') {
    $version = Read-Host "Invalid Version. Enter version number (e.g. 1.3.2)"
}

Write-Host "Building ReadMe.docx ..."
& pandoc -f markdown_github -t docx README.md -o README.docx
if ($LASTEXITCODE -ne 0) {
    $message = "Documentation failed (you need pandoc): " + $LASTEXITCODE
    Write-Host $message
    Pop-Location
    exit -1
}pandoc 

Write-Host "Running Word to create pdf ..."
$word = New-Object -ComObject "Word.Application"
$doc = $word.Documents.Open("$root/Readme.docx")
$doc.ExportAsFixedFormat("$root/README.pdf", 17, 0)
$doc.Close(0)
$word.Quit([ref]0)
Remove-Item "$root\README.docx"

Write-Host "Building Manual ..."
$text = (Get-Content "$root\..\AlteryxFormulaAddOns.wiki\Function-List.md" -Raw) 

$output = "$root\AlteryxAbacus v$version.zip"
Compress-Archive -Path ("$root\*.dll", "$root\*Utils.xml", "$root\README.pdf", "$root\Install.bat", "$root\InstallAlteryxAbacus.exe") -DestinationPath $output -Verbose -Update
Remove-Item "$root\README.pdf"

$output = "$root\AlteryxAbacus v$version Tests.zip"
Compress-Archive -Path ("$root\*.Test", "$root\*.yxm*", "*.png") -DestinationPath $output -Verbose -Update

Pop-Location