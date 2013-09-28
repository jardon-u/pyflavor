### Makefile --- 

## Author: log0@UBOX
## Version: $Id: Makefile,v 0.0 2013/09/28 23:27:53 log0 Exp $
## Keywords: 
## X-URL: 

-include Makefile.rules

PROJ=
SOURCE=
BIN=
FILES= # src

# C++ only
VPATH=src:obj
OBJ=$(SRC:.cc=.o)

all:
	

test: runtest
	./runtest

runtest: ./tests/builtin.cc
	g++ ./tests/builtin.cc -Wall -std=c++0x -L /usr/src/gtest/ \
	-lgtest -lpthread -o runtest

doc:
	

clean:
	rm -f $(BIN)

dist: clean todo AUTHORS svn_check
	rm -rf $(PROJ)
	mkdir $(PROJ)
	cp -r Makefile AUTHORS TODO $(FILES) $(PROJ)
	-find $(PROJ) -name ".svn" -exec rm -rf {} \;
	-find $(PROJ) -name "*~" -exec rm -rf {} \;
	-find $(PROJ) -name "#*" -exec rm -rf {} \;
	tar cjvf $(PROJ).tar.bz2 $(PROJ)
	rm -rf $(PROJ)
	chmod 644 $(PROJ).tar.bz2

svn_check:
	@svn st | grep \? ; [ $$? = "1" ] \
	|| (echo "----------------------------------------------"\
	&& echo "SOME FILES ARE MISSING FROM THE SVN REPOSITORY"\
	&& echo "----------------------------------------------");

todo:
	grep "FIXME" -r . --exclude="Makefile" > TODO

.PHONY: doc check

### Makefile ends here