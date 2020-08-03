echo "Compiling shaders..."

for f in *.vert *.tesc *.tese *.geom *.frag *.comp *.rgen *.rahit *.rchit *.rmiss *.rint *.rcall *.task *.mesh
do
	glslc -c -O $f
done

read -p "Press any key to continue..."
