build: main.c
	gcc main.c tasks.c stacks.c lists.c queues.c -o lanParty -lm
clean:
	rm -f lanParty
