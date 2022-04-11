$mydocuments = [environment]::getfolderpath("mydocuments")
$fullLibPath = $mydocuments + "/Arduino/libraries/"
$headerFiles = (Get-ChildItem -Filter *.h -Recurse).BaseName | Sort length -Descending
$cppFiles = (Get-ChildItem -Filter *.cpp -Recurse).BaseName | Sort length -Descending
$ignoredFiles = ".esp8266_controller.vsarduino"

foreach($header in $headerFiles)
{
    if ($ignoredFiles -contains $header) { continue }

    $fileName = $header + ".h"
    $fullDirPath = $fullLibPath + $header + "/"

    if (!(Test-Path $fullDirPath))
    {
       New-Item -path $fullLibPath -name $header -type "directory"
    }

    Copy-Item $fileName -Destination $fullDirPath
}

foreach($source in $cppFiles)
{
    if ($ignoredFiles -contains $source) { continue }

    $fileName = $source + ".cpp"
    $fullDirPath = $fullLibPath + $source + "/"

    Copy-Item $fileName -Destination $fullDirPath
}