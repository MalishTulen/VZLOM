# ���������� � �����
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -o3

# ��� ������������ �����
TARGET = crackme_patch

# �������� �����
SRCS = main.cpp crack.cpp graffic.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = crack.h graffic.h

# ���� �� ���������
all: $(TARGET)

# ������ ������������ �����
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# ���������� .cpp � .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# �������
clean:
	rm -f $(OBJS) $(TARGET)

# ������ (�����������)
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
