@echo off
for %%f in (*.frag *.vert *.tesc *.tese *.geom *.comp) do glslc -c -O %%f
pause