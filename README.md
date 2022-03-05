# ctimer
CTimer library to create custom timers in linux.

###Build Steps
	git clone https://github.com/shashiwakale/ctimer.git
	cd ctimer
	make
	
### Run Example
	cd ctimer
	./bin/CTimer

### Output
	[CTimer]:timer ID is 5622ade6be70
	Timer 1 Callback, Data is Hello CTimer
	Timer 1 Callback, Data is Hello CTimer
	Timer 1 Callback, Data is Hello CTimer
	Timer 1 Callback, Data is Hello CTimer
	Timer 2 Callback, Data is Hello CTimer
	Timer 1 Callback, Data is Hello CTimer
	Timer 1 Callback, Data is Hello CTimer
	Timer 1 Callback, Data is Hello CTimer
	Timer 1 Callback, Data is Hello CTimer

## Integrate ctimer in existing project
Copy CTimer.h from include to your projects include directory and add -lrt while compiling.