make:
	gcc compacta.c bitmap.c tree.c utils.c -o compacta
	gcc descompacta.c bitmap.c tree.c utils.c -o descompacta
clean:
	rm -f compacta descompacta