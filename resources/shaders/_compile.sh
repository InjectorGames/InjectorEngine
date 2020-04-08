for f in *.frag
do
	glslc -c -O $f
done

read -p "Press any key to continue..."