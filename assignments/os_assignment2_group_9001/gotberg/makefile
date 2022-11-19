compile : main.c functions.c
		cc -o threads.out main.c functions.c -pthreads

debug : main.c functions.c
	   cc -o threads.debug.out -g main.c functions.c -pthreads

cleanup : 
		rm -fr threads.debug*

