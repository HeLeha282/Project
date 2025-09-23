rd /s /q C:\Users\Lesha\Desktop\TestTaskKaspersky\Project\build
mkdir build
cd build
cmake ..
cmake --build . --config Release  
cd Release
scanner_exe.exe --base text.csv --log report.log --path c:\folder
cd ..
cd ..