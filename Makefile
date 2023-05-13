all: folders server client

server: bin/monitor

client: bin/tracer

folders:
	@mkdir -p src obj bin tmp include

bin/monitor: obj/monitor.o
	gcc -g obj/monitor.o -o bin/monitor

obj/monitor.o: src/monitor.c include/monitor.h
	gcc -Wall -g -c src/monitor.c -o obj/monitor.o

bin/tracer: obj/tracer.o
	gcc -g obj/tracer.o -o bin/tracer

obj/tracer.o: src/tracer.c include/tracer.h
	gcc -Wall -g -c src/tracer.c -o obj/tracer.o

clean:
	rm -f obj/* tmp/* bin/{tracer,monitor}