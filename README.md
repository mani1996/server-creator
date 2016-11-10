#SERVER CREATOR
Base class on which servers can be created for various applications

Server class is the base abstract class which uses sockets underneath
to perform low-level binding and listen operations

It can be subclassed to create concrete server class and server logic 
inserted in the **communicate** method

The 2 main functions required in the **communicate** method  are 
**recv** and **send** . Their **man** pages can be accessed in Linux 
systems.

A greeting server, that greets you on sending your name is given as 
an example to get started.

Compilation command can be seen in the **Makefile** 
