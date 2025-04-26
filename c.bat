@echo off
:: Toujours commencer dans le dossier du .bat
cd /d "%~dp0"

:: Définir les chemins source et destination
set SOURCE_DIR=%cd%\Simple_Engine\sfml\dll
set DEST_DIR=%cd%\x64\Debug

:: Vérifier que les dossiers existent
if not exist "%SOURCE_DIR%" (
    echo Erreur : Le dossier source "%SOURCE_DIR%" n'existe pas !
    pause
    exit /b
)

if not exist "%DEST_DIR%" (
    echo Erreur : Le dossier de destination "%DEST_DIR%" n'existe pas !
    pause
    exit /b
)

:: Copier les DLL
echo Copie des DLL de "%SOURCE_DIR%" vers "%DEST_DIR%"...
xcopy "%SOURCE_DIR%\*.*" "%DEST_DIR%\" /Y /E

echo Copie terminée !
exit