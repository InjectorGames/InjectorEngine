@echo off
echo Compiling shaders...
for %%f in (*.frag *.vert *.tesc *.tese *.geom *.comp) do glslc -c -O %%f
pause
