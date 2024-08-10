.PHONY: clean build test

test: build
	ctest --test-dir build -R $(TEST_FILTER)

build: build/build.ninja
	@cmake --build build

build/build.ninja:
	@cmake -B build -S . -G Ninja

clean:
	@rm -rf build

sync:
	@git submodule update --init --recursive --jobs 8
