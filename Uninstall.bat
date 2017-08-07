@echo off
powershell "Start-Process -FilePath powershell.exe -ArgumentList "%~dp0\Uninstaller.ps1" -verb RunAs -Wait"