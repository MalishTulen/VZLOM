# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -o3

# Имя исполняемого файла
TARGET = crackme_patch

# Исходные файлы
SRCS = main.cpp crack.cpp graffic.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = crack.h graffic.h

# Цель по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Компиляция .cpp в .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS) $(TARGET)

# Запуск (опционально)
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
