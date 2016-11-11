#SERVER CREATOR
Base class on which servers can be created for various applications

Server class is the base abstract class which uses sockets underneath
to perform low-level binding and listen operations

It can be subclassed to create concrete server class and server logic 
inserted in the **communicate** method

The components that are required to be defined for each server are
* Message exchange mechanism using **recv(), send()**
* Behaviour for **polling** messages(sets for read,write to be handled manually)
* Logic to be executed on **establishment of new client connection**

A greeting server, that greets you on sending your name is given as 
an example to get started.

Compilation command can be seen in the **Makefile** 
