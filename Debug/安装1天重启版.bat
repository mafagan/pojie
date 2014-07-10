IBSetupConsole.exe /install /COMPONENTS=[Agent],[Coordinator] /COORDINATOR=192.168.226.88:31104
sc create IncrediRestart binpath= "%cd%/PoJie1d.exe" 
sc start IncrediRestart
sc config IncrediRestart start= auto
pause
