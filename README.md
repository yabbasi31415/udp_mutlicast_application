# UDP Multi-cast Chat Application

### Install Dependencies and Make

* git submodule update --init --remote
* mkdir build && cd build
* cmake ..
* make


### To run 

* Udp multicast app with command line parsing support
    - cd build
    - ./examples/chat -l 192.168.2.100 -m 224.0.0.1 -p 20000
    - Run multiple instances of multicast_app in separate tabs simultaneously 
    - To send a message on the group, type on the console and press enter to send.
