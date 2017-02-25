@echo off

pushd "%~dp0"
powershell -Command "gci . | Unblock-File"

FOR /F "usebackq tokens=2,* skip=2" %%L IN (
    `reg query "HKLM\SOFTWARE\WOW6432Node\SRC\Alteryx" /v InstallDir64`
) DO SET alteryxPath=%%M

if "%alteryxPath%" NEQ "" (
    .\InstallAlteryxAbacus.exe "%~dp0\JDFormulaAddIn\x64\Debug\*.dll" %~dp0\*.xml" "%alteryxPath%\RuntimeData\FormulaAddIn"
    echo FormulaAddIns installed to %alteryxPath%\RuntimeData\FormulaAddIn\
)

FOR /F "usebackq tokens=2,* skip=2" %%L IN (
    `reg query "HKCU\SOFTWARE\SRC\Alteryx" /v InstallDir64`
) DO SET alteryxUserPath=%%M

if "%alteryxUserPath%" NEQ "" (
    .\InstallAlteryxAbacus.exe "%~dp0\JDFormulaAddIn\x64\Debug\*.dll" "%~dp0\*.xml" "%alteryxUserPath%\RuntimeData\FormulaAddIn"
    echo FormulaAddIns installed to %alteryxUserPath%\RuntimeData\FormulaAddIn\
)

if "%alteryxUserPath%%alteryxPath%" EQU "" (
    echo Please copy all xml and dll files from "%~dp0"  to $AlteryxInstallDir$\RuntimeData\FormulaAddIn\
    pause
)

popd
