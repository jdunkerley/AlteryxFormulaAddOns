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
    FOR /F "usebackq tokens=2,* skip=2" %%L IN (
        `reg query "HKLM\SOFTWARE\WOW6432Node\SRC\Alteryx" /v InstallDir64`
    ) DO SET alteryxPath=%%M

    pushd "%~dp0"

    echo %alteryxPath%
    if "%alteryxPath%" NEQ "" (
        if exist "%alteryxPath%\RuntimeData\FormulaAddIn\Random.xml" (
            del "%alteryxPath%\RuntimeData\FormulaAddIn\Random.xml"
        )
        if exist "%alteryxPath%\RuntimeData\FormulaAddIn\MathUtils.xml" (
            del "%alteryxPath%\RuntimeData\FormulaAddIn\MathUtils.xml"
        )
        if exist "%alteryxPath%\RuntimeData\FormulaAddIn\MiscUtils.xml" (
            del "%alteryxPath%\RuntimeData\FormulaAddIn\MiscUtils.xml"
        )
        if exist "%alteryxPath%\RuntimeData\FormulaAddIn\StringUtils.xml" (
            del "%alteryxPath%\RuntimeData\FormulaAddIn\StringUtils.xml"
        )
        if exist "%alteryxPath%\RuntimeData\FormulaAddIn\DateUtils.xml" (
            del "%alteryxPath%\RuntimeData\FormulaAddIn\DateUtils.xml"
        )
        if exist "%alteryxPath%\RuntimeData\FormulaAddIn\JDFormulaAddIn.dll" (
            del "%alteryxPath%\RuntimeData\FormulaAddIn\JDFormulaAddIn.dll"
        )

        echo FormulaAddIns uninstalled from %alteryxPath%\RuntimeData\FormulaAddIn\
    ) else (
        echo Please delete from $AlteryxInstallDir$\RuntimeData\FormulaAddIn\ the following:
        echo - Random.xml
        echo - MathUtils.xml
        echo - MiscUtils.xml
        echo - StringUtils.xml
        echo - DateUtils.xml
        echo - JDFormulaAddIn.dll
    )

    popd
    pause
    
