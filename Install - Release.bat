@echo off
powershell "Start-Process -FilePath powershell.exe -ArgumentList '%~fs0\..\Installer.ps1', 'Release' -verb RunAs -Wait"