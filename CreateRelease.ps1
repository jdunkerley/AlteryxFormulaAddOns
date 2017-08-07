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

$version = [System.Diagnostics.FileVersionInfo]::GetVersionInfo("AlteryxAbacus.dll").FileVersion

Write-Host "Building ReadMe.docx ..."
& pandoc -f markdown_github -t docx README.md -o README.docx
if ($LASTEXITCODE -ne 0) {
    $message = "Documentation failed (you need pandoc): " + $LASTEXITCODE
    Write-Host $message
    Pop-Location
    exit -1
}

Write-Host "Running Word to create pdf ..."
$readMeDoc = Join-Path $root "Readme.docx"
$readMePdf = Join-Path $root "Readme.pdf"
$word = New-Object -ComObject "Word.Application"
$doc = $word.Documents.Open($readMeDoc)
$doc.ExportAsFixedFormat([string]$readMePdf, 17, 0)
$doc.Close(0)
$word.Quit([ref]0)
Remove-Item $readMeDoc

# Write-Host "Building Manual ..."
# $text = (Get-Content "$root\..\AlteryxFormulaAddOns.wiki\Function-List.md" -Raw) 

Write-Host "Removing bak files ..."
Remove-Item *.bak -Recurse

$output = "$root\AlteryxAbacus v$version.zip"
Compress-Archive -Path ("$root\*.dll", "$root\*Utils.xml", "$root\README.pdf", "$root\Install.bat", "$root\Installer.ps1", "$root\Uninstall.bat", "$root\Uninstaller.ps1") -DestinationPath $output -Verbose -Update
Remove-Item "$root\README.pdf"

$output = "$root\AlteryxAbacus v$version Tests.zip"
Compress-Archive -Path ("$root\*.Test", "$root\*.yxm*", "*.png") -DestinationPath $output -Verbose -Update

Pop-Location