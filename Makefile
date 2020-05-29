TARGET = csvConfigTest
OBJS = main.o

$(TARGET): $(OBJS)
	g++ -o $@ $<

$(OBJS) : main.cpp
	g++ -c $<

clean :
	rm -rf *.o
	rm -rf $(TARGET).exe
