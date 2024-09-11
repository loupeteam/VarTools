# set environment variables
$env:AS_VERSION_SHORT = 'AS411'
Get-ChildItem "$PWD" -Recurse -Filter *.exe | Foreach-Object { 
    Write-Output "installing $($_.Name)"; 
    Write-Verbose "Into C:\BrAutomation\$env:AS_VERSION_SHORT"; 
    & $_.FullName -G='C:\BrAutomation' -V="C:\BrAutomation\$env:AS_VERSION_SHORT" -R | Out-Null; 
    if($LASTEXITCODE -ne 0) { 
        Write-Error "Error installing $($_.Name). Exit code $LASTEXITCODE"; 
        exit 1; 
    } 
}