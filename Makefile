BUILD_DIR ?= cmake-build-debug

.PHONY: tidy-check
tidy-check:
	 ./scripts/run-clang-tidy.py -clang-tidy-binary clang-tidy-12 -clang-apply-replacements-binary clang-apply-replacements-12 -j $(shell nproc) -quiet -p $(BUILD_DIR) -header-filter $(shell realpath ./modules) $(shell realpath ./modules)

.PHONY: tidy-fix
tidy-fix:
	 ./scripts/run-clang-tidy.py -clang-tidy-binary clang-tidy-12 -clang-apply-replacements-binary clang-apply-replacements-12 -j $(shell nproc) -fix -quiet -p $(BUILD_DIR) -header-filter $(shell realpath ./modules) $(shell realpath ./modules)


.PHONY: coverage
coverage:
	cmake -S. -GNinja -Bcmake-build-coverage -DCMAKE_BUILD_TYPE=Debug -DMODERN_CIRCUITS_BUILD_COVERAGE=TRUE
	cmake --build cmake-build-coverage
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
	@find modules -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs clang-format-11 -i

.PHONY: format-check
format-check:
	@find modules -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs -n 1 -P 1 -I{} -t sh -c 'clang-format-11 -style=file {} | diff - {}'
