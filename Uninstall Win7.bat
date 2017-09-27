@echo off

>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"

if '%errorlevel%' NEQ '0' (
    if '%1' NEQ 'ELEV' (
        echo Requesting administrative privileges...
        goto UACPrompt
    ) else (
        exit /B -1
    )
) else (
    goto gotAdmin
)

:UACPrompt
    echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
    echo UAC.ShellExecute "%~s0", "ELEV", "", "runas", 1 >> "%temp%\getadmin.vbs"
    "%temp%\getadmin.vbs"
    exit /B

:gotAdmin
    pushd %~dp0

    FOR %%A IN (*.xml *.dll) DO (echo.>%%A:Zone.Identifier)

    FOR /F "usebackq tokens=2,* skip=2" %%L IN (
        `reg query "HKLM\SOFTWARE\WOW6432Node\SRC\Alteryx" /v InstallDir64`
    ) DO SET alteryxPath=%%M

    IF "%alteryxPath%" NEQ "" (
      del /F "%alteryxPath%\RuntimeData\FormulaAddIn\Random.xml" 
      del /F "%alteryxPath%\RuntimeData\FormulaAddIn\MathUtils.xml" 
      del /F "%alteryxPath%\RuntimeData\FormulaAddIn\MiscUtils.xml" 
      del /F "%alteryxPath%\RuntimeData\FormulaAddIn\StringUtils.xml" 
      del /F "%alteryxPath%\RuntimeData\FormulaAddIn\DateUtils.xml" 
      del /F "%alteryxPath%\RuntimeData\FormulaAddIn\JDFormulaAddIn.dll" 
      del /F "%alteryxPath%\RuntimeData\FormulaAddIn\AlteryxAbacus.dll" 
    )

    FOR /F "usebackq tokens=2,* skip=2" %%L IN (
        `reg query "HKCU\SOFTWARE\SRC\Alteryx" /v InstallDir64`
    ) DO SET alteryxPath=%%M

    IF "%alteryxPath%" NEQ "" (
      del /F "%alteryxPath%\RuntimeData\FormulaAddIn\Random.xml" 
      del /F "%alteryxPath%\RuntimeData\FormulaAddIn\MathUtils.xml" 
      del /F "%alteryxPath%\RuntimeData\FormulaAddIn\MiscUtils.xml" 
      del /F "%alteryxPath%\RuntimeData\FormulaAddIn\StringUtils.xml" 
      del /F "%alteryxPath%\RuntimeData\FormulaAddIn\DateUtils.xml" 
      del /F "%alteryxPath%\RuntimeData\FormulaAddIn\JDFormulaAddIn.dll" 
      del /F "%alteryxPath%\RuntimeData\FormulaAddIn\AlteryxAbacus.dll" 
    )

    popd