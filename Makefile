CXX = g++
CXXFLAGS = -pedantic -Wall
LDLIBS = -lm -lutil

SRCS = $(shell find src -type f \( -name '*.c' -o -name '*.cpp' \) | sort)
HDRS = $(shell find src -type f \( -name '*.h' -o -name '*.hpp' \) | sort)

TESTS = $(wildcard tests/*.in)

main: $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@ $(LDLIBS)

test: main
	@pass=0; fail=0; \
	for input in $(TESTS); do \
		expected=$${input%.in}.out; \
		if ./main < $$input | diff -u $$expected - > /dev/null; then \
			pass=$$((pass + 1)); \
		else \
			echo "FAIL: $$input"; \
			./main < $$input | diff -u $$expected - || true; \
			fail=$$((fail + 1)); \
		fi; \
	done; \
	echo "Passed: $$pass, Failed: $$fail"; \
	test $$fail -eq 0

run:
	$(MAKE) clean
	$(MAKE) main
	./main

clean:
	rm -f main

.PHONY: clean test run
