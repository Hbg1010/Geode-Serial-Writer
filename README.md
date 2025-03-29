# serialWrite
<img src="logo.png" width="150" alt="the mod's logo" />

This mod should only work on windows machines.

This simple mod allows the user to communicate with an arduino over a shared Serial port when the player dies (for now)


Credits:
https://github.com/dmicha16/simple_serial_port for the serial port writer (that didnt make me mess around with windows.h for an hour, thanks asio)

Planning for V2 of the lib:
- Complete rewrite as an API
- Mac Support via switching to an already established library
- Bluetooth Serial Support?
- Encoding decoding
- Create a manager for Serial writers; allow multiple serial writers to exist as refrences / derefs
  - Create a data structure to hold different serial ports
  - Create each object as an async listener, which will send data back on event / allow stuff to be sent through it
  - Have a control system to set things as exclusive and stuff
  - Have some conflict system
- Create a system based off of event listening / writing to geode nodes and stuff
- 
