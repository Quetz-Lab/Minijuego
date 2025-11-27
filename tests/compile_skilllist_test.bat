@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
cl /EHsc /std:c++17 /I"..\src" test_skilllist_properties.cpp ..\src\SkillList.cpp ..\src\Node.cpp /Fe:test_skilllist_properties.exe
