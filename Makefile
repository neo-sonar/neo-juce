CXX_STD ?= 14

BUILD_DIR ?= cmake-build-debug

CLANG_FORMAT_BINARY ?= clang-format
CLANG_TIDY_BINARY ?= clang-tidy
CLANG_APPLY_BINARY ?= clang-apply-replacements

CLANG_TIDY_ARGS += -clang-tidy-binary ${CLANG_TIDY_BINARY}
CLANG_TIDY_ARGS += -clang-apply-replacements-binary ${CLANG_APPLY_BINARY}
CLANG_TIDY_ARGS += -j $(shell nproc)
CLANG_TIDY_ARGS += -quiet
CLANG_TIDY_ARGS += -p $(BUILD_DIR)

.PHONY: check
check:
	pre-commit run --all-files

.PHONY: tidy-check
tidy-check:
	 ./scripts/run-clang-tidy.py $(CLANG_TIDY_ARGS) -header-filter $(shell realpath ./modules) $(shell realpath ./modules)

.PHONY: tidy-fix
tidy-fix:
	 ./scripts/run-clang-tidy.py -fix $(CLANG_TIDY_ARGS) -header-filter $(shell realpath ./modules) $(shell realpath ./modules)

.PHONY: coverage
coverage:
	cmake -S. -GNinja -Bcmake-build-coverage -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_STANDARD=${CXX_STD} -DMC_BUILD_COVERAGE=TRUE
	cmake --build cmake-build-coverage
	ctest --test-dir cmake-build-coverage -C Debug --output-on-failure

.PHONY: coverage-html
coverage-html: coverage
	cd cmake-build-coverage && gcovr --html --html-details -e ".*test\.cpp" --exclude-unreachable-branches -o coverage.html -r ../modules -j ${shell nproc} -s .

.PHONY: coverage-xml
coverage-xml: coverage
	cd cmake-build-coverage && gcovr --xml-pretty -e ".*test\.cpp" --exclude-unreachable-branches -o coverage.xml  -r ../modules -j ${shell nproc} -s .


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
