#Makefile at top of application tree
TOP = .
include $(TOP)/configure/CONFIG
DIRS := $(DIRS) configure
DIRS := $(DIRS) kinetixSupport
DIRS := $(DIRS) kinetixApp
kinetixApp_DEPEND_DIRS += kinetixSupport
ifeq ($(BUILD_IOCS), YES)
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard iocs))
iocs_DEPEND_DIRS += kinetixApp
endif
include $(TOP)/configure/RULES_TOP

uninstall: uninstall_iocs
uninstall_iocs:
	$(MAKE) -C iocs uninstall
.PHONY: uninstall uninstall_iocs

realuninstall: realuninstall_iocs
realuninstall_iocs:
	$(MAKE) -C iocs realuninstall
.PHONY: realuninstall realuninstall_iocs

bobfiles:
	pixi run make-bobfiles

# Generate parameter definitions and then immediately format with clang-format
paramdefs:
	pixi run make-paramdefs
	pixi run clang-format -i -style=file $(shell find kinetixApp -name '*.h' -o -name '*.cpp')

lint:
	pixi run lint

coverage-report:
	pixi run tests
	pixi run get-coverage-info
	pixi run make-coverage-report
