@echo off

FOR /F "usebackq tokens=2,* skip=2" %%L IN (
    `reg query "HKLM\SOFTWARE\WOW6432Node\SRC\Alteryx" /v InstallDir64`
) DO SET alteryxPath=%%M

if "%alteryxPath%" NEQ "" (
    pushd "%~dp0"
    powershell -Command "gci . | Unblock-File"
    .\InstallAlteryxAbacus.exe "%~dp0\*.dll" "%~dp0\*.xml" "%alteryxPath%\RuntimeData\FormulaAddIn"
    echo FormulaAddIns installed to %alteryxPath%\RuntimeData\FormulaAddIn\
    popd
) else (
    echo Please copy "%~dp0*.xml" to $AlteryxInstallDir$\RuntimeData\FormulaAddIn\
    pause
)