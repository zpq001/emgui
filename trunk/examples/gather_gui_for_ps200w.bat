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
copy "%EXAMPLEFOLDER%\gui_top\guiMasterPanel.c" %OUTFOLDER%
copy "%EXAMPLEFOLDER%\gui_top\guiMasterPanel.h" %OUTFOLDER%
copy "%EXAMPLEFOLDER%\gui_top\guiSetupPanel.c" %OUTFOLDER%
copy "%EXAMPLEFOLDER%\gui_top\guiSetupPanel.h" %OUTFOLDER%
rem copy "%EXAMPLEFOLDER%\gui_top\guiTop.c" %OUTFOLDER%
rem copy "%EXAMPLEFOLDER%\gui_top\guiTop.h" %OUTFOLDER%

copy "%SOURCEFOLDER%\guiCore\guiEvents.h" %OUTFOLDER%\guiCore
copy "%SOURCEFOLDER%\guiCore\guiCore.h" %OUTFOLDER%\guiCore
copy "%SOURCEFOLDER%\guiCore\guiCore.c" %OUTFOLDER%\guiCore
copy "%SOURCEFOLDER%\guiWidgets_monochrome\guiWidgets.h" %OUTFOLDER%\guiWidgets
copy "%SOURCEFOLDER%\guiWidgets_monochrome\guiPanel.h" %OUTFOLDER%\guiWidgets
copy "%SOURCEFOLDER%\guiWidgets_monochrome\guiPanel.c" %OUTFOLDER%\guiWidgets
copy "%SOURCEFOLDER%\guiWidgets_monochrome\guiSpinBox.h" %OUTFOLDER%\guiWidgets
copy "%SOURCEFOLDER%\guiWidgets_monochrome\guiSpinBox.c" %OUTFOLDER%\guiWidgets
copy "%SOURCEFOLDER%\guiWidgets_monochrome\guiTextLabel.h" %OUTFOLDER%\guiWidgets
copy "%SOURCEFOLDER%\guiWidgets_monochrome\guiTextLabel.c" %OUTFOLDER%\guiWidgets
copy "%SOURCEFOLDER%\guiGraphics_monochrome\font_6x8_mono.c" %OUTFOLDER%\guiGraphics
copy "%SOURCEFOLDER%\guiGraphics_monochrome\font_h10.c" %OUTFOLDER%\guiGraphics
copy "%SOURCEFOLDER%\guiGraphics_monochrome\font_h10_bold.c" %OUTFOLDER%\guiGraphics
copy "%SOURCEFOLDER%\guiGraphics_monochrome\font_h11.c" %OUTFOLDER%\guiGraphics
copy "%SOURCEFOLDER%\guiGraphics_monochrome\font_h16.c" %OUTFOLDER%\guiGraphics
copy "%SOURCEFOLDER%\guiGraphics_monochrome\font_h32.c" %OUTFOLDER%\guiGraphics
copy "%SOURCEFOLDER%\guiGraphics_monochrome\guiFonts.h" %OUTFOLDER%\guiGraphics
copy "%SOURCEFOLDER%\guiGraphics_monochrome\widget_images.c" %OUTFOLDER%\guiGraphics
copy "%SOURCEFOLDER%\guiGraphics_monochrome\guiImages.h" %OUTFOLDER%\guiGraphics
copy "%SOURCEFOLDER%\guiGraphics_monochrome\guiGraphHAL.h" %OUTFOLDER%\guiGraphics
copy "%SOURCEFOLDER%\guiGraphics_monochrome\guiGraphHAL.c" %OUTFOLDER%\guiGraphics
copy "%SOURCEFOLDER%\guiGraphics_monochrome\guiGraphPrimitives.h" %OUTFOLDER%\guiGraphics
copy "%SOURCEFOLDER%\guiGraphics_monochrome\guiGraphPrimitives.c" %OUTFOLDER%\guiGraphics
copy "%SOURCEFOLDER%\guiGraphics_monochrome\guiGraphWidgets.h" %OUTFOLDER%\guiGraphics
copy "%SOURCEFOLDER%\guiGraphics_monochrome\guiGraphWidgets.c" %OUTFOLDER%\guiGraphics


