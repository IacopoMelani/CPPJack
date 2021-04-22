
CC = g++

INCLUDES = main.cc \
	classes/*.cc \
	classes/**/*.cc \
	utils/*.cc \
	cli/*.cc \
	-I .

OUT_DEBUG = main
OUT_RELEASE = c++jack
	
debug:
	$(CC) -g $(INCLUDES) -o $(OUT_DEBUG) -D DEBUG

debug-auto:
	$(CC) -g $(INCLUDES) -o $(OUT_DEBUG) -D DEBUG -D AUTO

release:
	$(CC) $(INCLUDES) -o $(OUT_RELEASE) -D RELEASE
	
run-release:
	make release && ./c++jack

run-debug:
	make debug && ./$(OUT_DEBUG)

run-debug-auto:
	make debug-auto && ./$(OUT_DEBUG)

detect-leak-debug:
	rm -f valgrind-out.txt 2> /dev/null && \
	make debug && \
	valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind-out.txt \
			./$(OUT_DEBUG)

detect-leak-debug-auto:
	rm -f valgrind-out.txt 2> /dev/null && \
	make debug-auto && \
	valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind-out.txt \
			./$(OUT_DEBUG)

detect-leak-release:
	rm -f valgrind-out.txt 2> /dev/null && \
	make release && \
	valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind-out.txt \
			./$(OUT_RELEASE)