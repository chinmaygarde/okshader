.PHONY: clean build test

test: build
	ctest --output-on-failure --test-dir build -R $(TEST_FILTER)

build: build/build.ninja
	cmake --build build

build/build.ninja:
	cmake -B build -S . -G Ninja

clean:
	rm -rf build

sync:
	git submodule update --init --recursive --jobs 8

stash_and_pull:
	git stash
	git pull --rebase origin main
	git stash pop

update: stash_and_pull sync
