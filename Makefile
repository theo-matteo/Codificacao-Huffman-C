make:
	gcc compacta.c bitmap.c tree.c utils.c -o compacta
	gcc descompacta.c bitmap.c tree.c utils.c -o descompacta
run:
	valgrind ./compacta figura.png
	valgrind ./descompacta figura.png.comp
clean:
	rm -f compacta descompacta *.comp