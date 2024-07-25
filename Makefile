make:
	gcc compacta.c bitmap.c tree.c encoder.c -o compacta
	gcc descompacta.c bitmap.c tree.c decoder.c -o descompacta
run:
	valgrind ./compacta input.txt
	valgrind ./descompacta input.txt.comp
clean:
	rm -f compacta descompacta *.comp