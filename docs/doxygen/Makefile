SHELL := /bin/bash

SOURCE_FILES := $(shell find ../../modules -type f -name "mc_*.hpp" -or -name "mc_*.dox" | sed 's/ /\\ /g')

.PHONEY: clean

doc/index.html: build/mc_modules.dox Doxyfile
	doxygen

build/mc_modules.dox: process_source_files.py $(SOURCE_FILES)
	python $< ../../modules build

clean:
	rm -rf build doc
