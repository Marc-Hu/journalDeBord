all: run

run: clearMain compile
	./journal

compile:
	gcc journal.c -Wall -o journal

clearMain:
	rm -rf journal
