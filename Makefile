TARGET = csvConfigTest
OBJS = main.o
CFLAG = -w -O2 -g

$(TARGET): $(OBJS)
	g++ -o $@ $<

$(OBJS) : main.cpp
	g++ -c $< $(CFLAG)

clean :
	rm -rf *.o
	rm -rf $(TARGET).exe
