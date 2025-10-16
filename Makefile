ifeq ($(shell pkg-config --exists opencv4 && echo yes || echo no), no)
all:
	@echo "OpenCV not installed. Use:"
	@echo "sudo apt install libopencv-dev"
else
all:
	clear
	g++ -std=c++17 -Wall RogaineTool/main.cpp RogaineTool/interactive.cpp RogaineTool/checkpoint.cpp RogaineTool/routePlanner.cpp -o rogaine `pkg-config --cflags --libs opencv4`
	./rogaine
endif
