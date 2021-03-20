BUILD_DIR ?= cmake-build-debug

CLANG_FORMAT_BINARY ?= clang-format-12
CLANG_TIDY_BINARY ?= clang-tidy-12
CLANG_APPLY_BINARY ?= clang-apply-replacements-12

CLANG_TIDY_ARGS += -clang-tidy-binary ${CLANG_TIDY_BINARY}
CLANG_TIDY_ARGS += -clang-apply-replacements-binary ${CLANG_APPLY_BINARY}
CLANG_TIDY_ARGS += -j $(shell nproc)
CLANG_TIDY_ARGS += -quiet
CLANG_TIDY_ARGS += -p $(BUILD_DIR)

.PHONY: tidy-check
tidy-check:
	 ./scripts/run-clang-tidy.py $(CLANG_TIDY_ARGS) -header-filter $(shell realpath ./modules) $(shell realpath ./modules)

.PHONY: tidy-fix
tidy-fix:
	 ./scripts/run-clang-tidy.py -fix $(CLANG_TIDY_ARGS) -header-filter $(shell realpath ./modules) $(shell realpath ./modules)

.PHONY: coverage
coverage:
	cmake -S. -GNinja -Bcmake-build-coverage -DCMAKE_BUILD_TYPE=Debug -DMODERN_CIRCUITS_BUILD_COVERAGE=TRUE
	cmake --build cmake-build-coverage -- -j6
	cd cmake-build-coverage && lcov -c -i -d . --base-directory . -o base_cov.info
	cd cmake-build-coverage && ctest -j
	cd cmake-build-coverage && lcov -c -d . --base-directory . -o test_cov.info
	cd cmake-build-coverage && lcov -a base_cov.info -a test_cov.info -o cov.info
	lcov --remove cmake-build-coverage/cov.info "*cmake-build*" -o cmake-build-coverage/cov.info
	lcov --remove cmake-build-coverage/cov.info "*build_*" -o cmake-build-coverage/cov.info
	lcov --remove cmake-build-coverage/cov.info "*.conan/*" -o cmake-build-coverage/cov.info
	lcov --remove cmake-build-coverage/cov.info "*boost/*" -o cmake-build-coverage/cov.info
	lcov --remove cmake-build-coverage/cov.info "*gcc/*" -o cmake-build-coverage/cov.info
	lcov --remove cmake-build-coverage/cov.info "*3rd_party/*" -o cmake-build-coverage/cov.info
	lcov --remove cmake-build-coverage/cov.info "*c++*" -o cmake-build-coverage/cov.info
	lcov --remove cmake-build-coverage/cov.info "*v1*" -o cmake-build-coverage/cov.info
	lcov --remove cmake-build-coverage/cov.info "*Xcode.app*" -o cmake-build-coverage/cov.info
	lcov --remove cmake-build-coverage/cov.info "*ff_meters*" -o cmake-build-coverage/cov.info
	lcov --remove cmake-build-coverage/cov.info "*_test.cpp*" -o cmake-build-coverage/cov.info

.PHONY: report
report:
	cd cmake-build-coverage && genhtml cov.info --output-directory lcov

.PHONY: stats
stats:
	@cloc -by-file-by-lang --exclude-dir=3rd_party --exclude-ext=svg --vcs=git .

.PHONY: format
format:
	@find modules -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs ${CLANG_FORMAT_BINARY} -i

.PHONY: format-check
format-check:
	@find modules -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs -n 1 -P 1 -I{} -t sh -c '${CLANG_FORMAT_BINARY} -style=file {} | diff - {}'
