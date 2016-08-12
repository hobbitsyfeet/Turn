CCC= g++
LOGFILE=$(LOGPATH)`date +'%h:%d:%Y:%l.%M%.%S%p'`

all : game
game : main.o unit.o item.o turn.o chart.o
	$(CCC) $^ -o $@


# $< = the corresponding .cc file
%.o : %.cc
	$(CCC) -c $<

clean:
	rm -f *.o *~ *% *# .#*

clean-all: clean
	rm -f game

run:
	./game

backup: clean
	cp -r ./ ../backups/"_$(LOGFILE)"
