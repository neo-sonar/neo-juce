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