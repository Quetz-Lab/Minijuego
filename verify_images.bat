@echo off
echo Verificando imagenes de nodos...
echo.

set MISSING=0

for %%i in (n1 n2 n3 n4 n5 n6 n7 n8 n9 n10 n11) do (
    if exist "assets\%%i.png" (
        echo [OK] assets\%%i.png existe
    ) else (
        echo [ERROR] assets\%%i.png NO EXISTE
        set MISSING=1
    )
)

echo.
if %MISSING%==0 (
    echo Todas las imagenes de nodos estan presentes!
) else (
    echo ADVERTENCIA: Algunas imagenes faltan
)

pause
