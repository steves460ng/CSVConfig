TARGET = csvConfigTest
OBJS = main.o CSVConfig.o
CFLAG = -w -O2 -g

$(TARGET): $(OBJS)
	g++ -o $@ $(OBJS)

main.o : main.cpp CSVConfig.h
	g++ -c $< $(CFLAG)
	
CSVConfig.o : CSVConfig.cpp  CSVConfig.h
	g++ -c $< $(CFLAG)

clean :
	rm -rf *.o
	rm -rf $(TARGET).exe
