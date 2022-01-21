CC = gcc
SUBDIRS = main\
		  airplane\
		  obj

OBJS = airplane.o main.o 
BIN = APP
OBJS_DIR = obj
BIN_DIR = bin
export CC OBJS BIN OBJS_DIR BIN_DIR

all: CHECK_DIR $(SUBDIRS)
CHECK_DIR:
	mkdir -p $(BIN_DIR)
$(SUBDIRS): ECHO
	make -C $@
ECHO:
	@echo $(SUBDIRS)
	@echo begin compile
CLEAN:
	@$(RM) $(OBJS_DIR)/*.obj
	@rm -rf $(BIN_DIR)