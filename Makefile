HEADERS = src/main.c src/tasktool.c
COMPILER = gcc
TARGER = task
DATAFILE = .tasksdb

$(TARGER): $(HEADERS)
	@echo "compiling the code ..."
	@touch $(DATAFILE)
	$(COMPILER) $^ -o $@

clean:
	@echo "deleting the executables ..."
	rm -rf $(TARGER) $(DATAFILE)

.PHONY: clean
