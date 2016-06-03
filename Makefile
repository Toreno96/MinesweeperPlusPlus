# Declaring file extensions.
SRCEXT = .cpp
HDREXT = .hpp
OBJEXT = .o
EXEEXT = .exe
DEPEXT = .d

.SUFFIXES:
.SUFFIXES: $(SRCEXT) $(OBJEXT)

# Build configuration, i.e. debug (the default one) or release.
# It influences compilation flags, and objects and executables
# directories paths.
CONFIG = debug

# Compiler and linker variables.
CXX = clang++
CXXSTD = -std=c++14
CXXW = -Wall -Wextra -Wpedantic -Wshadow
CXXINCLUDE = -I"D:/Programowanie/Studia/Semestr_2/JiPP/Projekt/Minesweeper++/src" -I"c:/Program Files (x86)/SFML/include" -I"C:/Boost/include/boost-1_60"
ifeq "$(CONFIG)" "debug"
	CXXCONFIG = -O0 -g
else \
ifeq "$(CONFIG)" "release"
	CXXCONFIG = -O3 -DNDEBUG
endif

CXXFLAGS = -c $(CXXCONFIG) $(CXXSTD) $(CXXW) $(CXXINCLUDE)
DEPFLAGS = -MMD -MT $@ -MF $(@:$(OBJEXT)=$(DEPEXT))
LDFLAGS = -L"C:/Program Files (x86)/SFML/lib" -L"C:/Boost/lib"
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
ifeq "$(CONFIG)" "debug"
	LDLIBS += -lboost_random-mgw53-mt-d-1_60 -lboost_system-mgw53-mt-d-1_60
else \
ifeq "$(CONFIG)" "release"
	LDLIBS += -lboost_random-mgw53-mt-1_60 -lboost_system-mgw53-mt-1_60
endif

# Objects, executables, and dependencies variables, directories, etc.
vpath %$(SRCEXT) GameLogic
vpath %$(HDREXT) GameLogic
vpath %$(SRCEXT) GameStates
vpath %$(HDREXT) GameStates
vpath %$(SRCEXT) HelperFunctions
vpath %$(HDREXT) HelperFunctions

ifeq "$(CONFIG)" "debug"
	OBJDIR = debug/build
	EXEDIR = debug/bin
else \
ifeq "$(CONFIG)" "release"
	OBJDIR = release/build
	EXEDIR = release/bin
endif

OBJNAMES = $(basename $(notdir $(shell dir *$(SRCEXT) /B /S)))
OBJ = $(addprefix $(OBJDIR)/,$(addsuffix $(OBJEXT),$(OBJNAMES)))
EXENAME = game
EXE = $(addprefix $(EXEDIR)/,$(addsuffix $(EXEEXT),$(EXENAME)))
DEP = $(OBJ:$(OBJEXT)=$(DEPEXT))

# Other variables.
DEL = del /F /S
MKDIR = mkdir $(subst /,\,$@)

# Fundamental rules.
$(EXE): $(OBJ) | $(EXEDIR)
	@echo.
	@echo Linking object files...
	$(CXX) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@
$(OBJDIR)/%$(OBJEXT): %$(SRCEXT) | $(OBJDIR)
	@echo.
	$(CXX) $< $(CXXFLAGS) $(DEPFLAGS) -o $@

-include $(DEP)

# Creating required directories.
$(EXEDIR):
	@echo.
	$(MKDIR)
$(OBJDIR):
	@echo.
	$(MKDIR)

# Phony targets.
.PHONY: clean clean_exe clean_build clean_obj clean_dep

clean: clean_exe clean_build

clean_exe:
	$(DEL) *$(EXEEXT)
clean_build: clean_obj clean_dep

clean_obj:
	$(DEL) *$(OBJEXT)
clean_dep:
	$(DEL) *$(DEPEXT)