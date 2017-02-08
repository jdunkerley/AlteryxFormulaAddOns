$version = "1.3"

$root = Split-Path -Parent $PSCommandPath

$output = "$root\AlteryxAbacus $version.zip"
Compress-Archive -Path ("$root\*Utils.xml", "$root\*.dll", "*nstall.bat") -DestinationPath $output -Verbose -Update

$output = "$root\AlteryxAbacus Tests $version.zip"
Compress-Archive -Path ("$root\*.Test", "$root\*.yxm*") -DestinationPath $output -Verbose -Update