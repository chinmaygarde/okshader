.PHONY: clean build test update

TEST_FILTER?=.\*
PARALLEL_COUNT?=`sysctl -n hw.ncpu`

test: build
	ctest -j $(PARALLEL_COUNT) --output-on-failure --test-dir build -R $(TEST_FILTER)

build: build/build.ninja
	cmake --build build

build/build.ninja:
	cmake -B build -S . -G Ninja -DCMAKE_BUILD_TYPE=Debug

clean:
	rm -rf build

sync:
	git submodule update --init --recursive --jobs $(PARALLEL_COUNT)

stash_and_pull:
	git stash
	git pull --rebase origin main
	git stash pop

update: stash_and_pull sync
