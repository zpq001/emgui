set	OUTFOLDER=gui
set SOURCEFOLDER=..\source
set EXAMPLEFOLDER=QMenuSim - ps200w
rem if exist %OUTFOLDER% rmdir /s /q %OUTFOLDER%
mkdir %OUTFOLDER%
mkdir %OUTFOLDER%\guiCore
mkdir %OUTFOLDER%\guiWidgets
mkdir %OUTFOLDER%\guiGraphics
copy "%EXAMPLEFOLDER%\gui_top\guiConfig.h" %OUTFOLDER%
copy "%EXAMPLEFOLDER%\gui_top\guiMainForm.c" %OUTFOLDER%
copy "%EXAMPLEFOLDER%\gui_top\guiMainForm.h" %OUTFOLDER%

