@echo off
powershell "Start-Process -FilePath powershell.exe -ArgumentList '%~fs0\..\Installer.ps1', 'Debug' -verb RunAs -Wait"