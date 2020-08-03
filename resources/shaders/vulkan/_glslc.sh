echo "Compiling shaders..."

for f in *.frag *.vert *.tesc *.tese *.geom *.comp *.rgen *.rahit *.rchit *.rmiss *.rint *.rcall *.task *.mesh
do
	glslc -c -O $f
done

read -p "Press any key to continue..."
