LDLIBS = $(shell pkg-config --libs glew) $(shell pkg-config sfml-all --libs) 
MAIN = main
$(MAIN): clean
	g++ -Wall $(MAIN).cpp -o $(MAIN) $(LDLIBS);
	./$(MAIN)
debug: clean
	g++ -DLITTLEBUG -Wall $(MAIN).cpp -o $(MAIN) $(LDLIBS);
	./$(MAIN)
bench: clean
	g++ -DLITTLEBENCH -Wall $(MAIN).cpp -o $(MAIN) $(LDLIBS);
	./$(MAIN)
exec:
	./$(MAIN)
dnm:
	g++ -Wall dnm.cpp -o $(MAIN) $(LDLIBS);
clean:
	clear
	rm -f $(MAIN);