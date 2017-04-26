$ErrorActionPreference = "Stop"

$root = Split-Path -Parent $PSCommandPath
Push-Location $root

$vsPath = .\vswhere.exe -latest -requires 'Microsoft.Component.MSBuild' -property installationPath
if ($vsPath -eq $null) {
    Write-Host "Failed to find Visual Studio Install"
    Pop-Location
    exit -1
}
$vsPath = Join-Path $vsPath 'MSBuild\15.0\Bin\MSBuild.exe'

& $vsPath .\JDFormulaAddIn\JDFormulaAddIn.sln /t:Rebuild /p:Configuration=Release
if ($LASTEXITCODE -ne 0) {
    Write-Host "Build Failed"
    Pop-Location
    exit -1
}

Copy-Item .\JDFormulaAddIn\x64\Release\JDFormulaAddIn.dll .

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

$version = Read-Host "Enter version number (e.g. 1.3.2)"
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
}

Write-Host "Running Word to create pdf ..."
$word = New-Object -ComObject "Word.Application"
$doc = $word.Documents.Open("$root/Readme.docx")
$doc.ExportAsFixedFormat("$root/README.pdf", 17, 0)
$doc.Close(0)
$word.Quit([ref]0)
Remove-Item "$root\README.docx"

Write-Host "Building Manual ..."
$text = (Get-Content "$root\..\AlteryxFormulaAddOns.wiki\Function-List.md" -Raw) 

Write-Host "Removing bak files ..."
Remove-Item *.Test\*.bak

$output = "$root\AlteryxAbacus v$version.zip"
Compress-Archive -Path ("$root\*.dll", "$root\*Utils.xml", "$root\README.pdf", "$root\Install.bat", "$root\InstallAlteryxAbacus.exe", "$root\Install - Core.bat", "$root\Uninstall.bat") -DestinationPath $output -Verbose -Update
Remove-Item "$root\README.pdf"

$output = "$root\AlteryxAbacus v$version Tests.zip"
Compress-Archive -Path ("$root\*.Test", "$root\*.yxm*", "*.png") -DestinationPath $output -Verbose -Update

Pop-Location