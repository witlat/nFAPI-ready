# nFAPI-ready

A prototype transmitter-receiver pair meant to handle the sending of 5G nFAPI PNF_READY.indication message on a local connection.

### Usage prerequisites

To compile and run the C++ portion of this project, you need to have an SCTP devkit appropriate for your unix distribution. For debian and its derivatives you will need
> libsctp-dev

while redhat derivatives will need 
> lksctp-tools-devel

The compiliation process will also need some version of Cmake installed. The Python script was run and tested using Python 3.10, it was not tested on 2.x

### Running the project

Clone the repository to an empty folder of your choice.
> git clone https://github.com/witlat/nFAPI-ready.git

The VNF component is a simple script, so it is ready to use right away. Simply run it with your Python interpreter. It will then listen on the displayed IP and port.
> python VNF.py

Open a second terminal instance (in the same folder) to prepare and run the PNF component. Create and navigate to a build directory
> mkdir build

> cd build

Then, prepare and execute the Cmake script

> cmake ..

> make

You should now have a compiled executable simply called PNF. Execute it while the VNF.py is running (otherwise the connection will fail) by passing to it the local IP and port that VNF is listening on
> ./PNF 127.0.0.1 22222

This should print out the message contents received by VNF in the first terminal instance. Both components should then terminate.