default:
	gcc -g hangman.c -o hangman

clean:	hangman hangman2
	rm hangman

new:	hangman hangman2
	rm hangman
	gcc -g hangman.c -o hangman
