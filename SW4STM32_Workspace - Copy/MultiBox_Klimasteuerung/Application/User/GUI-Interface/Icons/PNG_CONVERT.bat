set datei=%~n1%


BmpCvtST.exe %datei%.png -convertintotranspalette -saveas%datei%.c,1,5,1
