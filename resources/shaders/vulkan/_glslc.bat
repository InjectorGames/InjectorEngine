@echo off
echo Compiling shaders...
for %%f in (*.vert *.tesc *.tese *.geom *.frag *.comp *.rgen *.rahit *.rchit *.rmiss *.rint *.rcall *.task *.mesh) do glslc -c -O %%f
pause
