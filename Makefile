#recursive makefile

SUBDIRS = Assignment1 Assignment3 Assignment4 Assignment5

.PHONY: all $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	rm Assignment1/a01.exe Assignment3/topography.exe Assignment4/rpn.exe Assignment5/maze.exe
	
