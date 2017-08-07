@echo off
powershell "Start-Process -FilePath powershell.exe -ArgumentList "%~dp0\Installer.ps1" -verb RunAs -Wait"