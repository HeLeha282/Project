@echo off
setlocal enabledelayedexpansion

echo Creating chaotic test directory structure...

REM === СОЗДАЕМ СТРУКТУРУ ПАПОК ===
mkdir scanDir
mkdir scanDir\system
mkdir scanDir\system\drivers
mkdir scanDir\system\drivers\audio
mkdir scanDir\system\config

mkdir scanDir\users
mkdir scanDir\users\john
mkdir scanDir\users\john\documents
mkdir scanDir\users\john\documents\work
mkdir scanDir\users\john\documents\personal
mkdir scanDir\users\john\downloads
mkdir scanDir\users\john\downloads\archive
mkdir scanDir\users\john\desktop
mkdir scanDir\users\john\desktop\temp

mkdir scanDir\users\admin
mkdir scanDir\users\admin\logs
mkdir scanDir\users\admin\scripts

mkdir scanDir\programs
mkdir scanDir\programs\browser
mkdir scanDir\programs\browser\plugins
mkdir scanDir\programs\browser\data
mkdir scanDir\programs\game
mkdir scanDir\programs\game\assets
mkdir scanDir\programs\game\assets\textures
mkdir scanDir\programs\game\assets\sounds
mkdir scanDir\programs\game\saves
mkdir scanDir\programs\utils

mkdir scanDir\temp
mkdir scanDir\temp\old_files

mkdir scanDir\logs
mkdir scanDir\logs\application
mkdir scanDir\logs\system

mkdir scanDir\config
mkdir scanDir\config\backup

echo Folder structure created!

REM === СОЗДАЕМ ФАЙЛЫ И НАПОЛНЯЕМ ИХ ТЕКСТОМ ===

REM Системные файлы
echo Windows Kernel Library version 10.0.19041 > scanDir\system\kernel32.dll
echo Network driver for Ethernet adapter > scanDir\system\drivers\network.sys
echo Audio driver configuration > scanDir\system\drivers\audio\sound.drv
echo [System Settings] > scanDir\system\config\system.ini
echo DisplayTimeout=300 >> scanDir\system\config\system.ini
echo SecurityLevel=high > scanDir\system\config\security.cfg

REM Пользовательские файлы John
echo Quarterly Report 2024 Q1 > scanDir\users\john\documents\work\report.docx
echo Project Budget: $15,000 > scanDir\users\john\documents\work\budget.xlsx
echo Personal notes: Meeting tomorrow at 10 AM > scanDir\users\john\documents\personal\notes.txt

echo Software installation package > scanDir\users\john\downloads\setup.exe
echo Vacation photo from Hawaii > scanDir\users\john\downloads\image.jpg
echo Archived project data > scanDir\users\john\downloads\archive\data1.zip
echo Backup from 2024-01-15 > scanDir\users\john\downloads\archive\backup.rar

echo Shortcut to main application > scanDir\users\john\desktop\shortcut.lnk
echo Temporary cache data > scanDir\users\john\desktop\temp\cache.tmp

REM Файлы админа
echo Application started at 2024-01-15 10:30:45 > scanDir\users\admin\logs\app.log
echo User login successful > scanDir\users\admin\logs\system.log

echo @echo off > scanDir\users\admin\scripts\deploy.bat
echo echo Deploying application... >> scanDir\users\admin\scripts\deploy.bat
echo xcopy app.exe C:\programs\ /Y >> scanDir\users\admin\scripts\deploy.bat

echo # Cleanup script > scanDir\users\admin\scripts\cleanup.ps1
echo Remove-Item C:\temp\*.tmp >> scanDir\users\admin\scripts\cleanup.ps1

REM Программные файлы
echo Main browser executable > scanDir\programs\browser\browser.exe
echo Flash player plugin > scanDir\programs\browser\plugins\flash.dll
echo Video playback plugin > scanDir\programs\browser\plugins\video.plugin
echo User settings and preferences > scanDir\programs\browser\data\settings.dat

echo Game launcher executable > scanDir\programs\game\game.exe
echo Character texture file > scanDir\programs\game\assets\textures\character.png
echo Background music track > scanDir\programs\game\assets\sounds\music.mp3
echo Player progress data > scanDir\programs\game\saves\progress.sav

echo Simple calculator utility > scanDir\programs\utils\calculator.exe
echo {"version": "1.0", "theme": "dark"} > scanDir\programs\utils\config.json

REM Временные файлы
echo Download in progress... > scanDir\temp\download.tmp
echo Session data for user123 > scanDir\temp\session.data
echo Old temporary file 1 > scanDir\temp\old_files\trash1.dat
echo Old log entries > scanDir\temp\old_files\trash2.log

REM Логи
echo 2024-01-15 INFO: Application started > scanDir\logs\application\app1.log
echo 2024-01-15 ERROR: Database connection failed > scanDir\logs\application\app2.log
echo System boot completed successfully > scanDir\logs\system\boot.log
echo ERROR: Disk space low > scanDir\logs\system\error.log

REM Конфиги
echo global_settings: > scanDir\config\global.cfg
echo language=en >> scanDir\config\global.cfg
echo timeout=30 >> scanDir\config\global.cfg

echo {"users": ["john", "admin"], "permissions": "read_write"} > scanDir\config\users.json
echo Backup of configuration > scanDir\config\backup\config.bak


echo.
echo ========================================
echo TEST STRUCTURE SUCCESSFULLY CREATED!
echo ========================================
echo.
echo Structure overview:
echo - Total folders: 25
echo - Total files: 35+
echo - Max nesting level: 5
echo.
echo File types created:
echo - .exe, .dll, .sys, .drv, .ini, .cfg
echo - .txt, .log, .bat, .ps1, .json
echo - .docx, .xlsx, .jpg, .png, .mp3
echo - .zip, .rar, .tmp, .dat, .lnk
echo.
