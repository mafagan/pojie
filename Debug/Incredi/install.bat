IBSetupConsole.exe /uninstall
IBSetupConsole.exe /install /COMPONENTS=[Agent],[Coordinator] /COORDINATOR=192.168.226.71:31104
sc create IncrediTrailDelay binpath= "%cd%/Crack.exe" 
sc start IncrediTrailDelay
sc config IncrediTrailDelay start= auto
pause
