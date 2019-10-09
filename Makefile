relay: relay.c
	gcc -o $@ $< -lhidapi-hidraw

