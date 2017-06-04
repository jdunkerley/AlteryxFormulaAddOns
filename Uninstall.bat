@echo off
powershell "Start-Process -FilePath powershell.exe -ArgumentList '%~fs0\..\Uninstaller.ps1' -verb RunAs -Wait"