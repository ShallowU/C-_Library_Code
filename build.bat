cd .\build
del /f *
rmdir CMakeFiles /s /q
cmake ..
cmake --build .