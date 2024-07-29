make:
	gcc -Wall -g compacta.c bitmap.c tree.c encoder.c -o compacta
	gcc -Wall -g descompacta.c bitmap.c tree.c decoder.c -o descompacta
clean:
	rm -f compacta descompacta *.comp