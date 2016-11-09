#SERVER CREATOR
Base class on which servers can be created for various applications

Server class is the base abstract class which uses sockets underneath
to perform low-level binding and listen operations

It can be subclassed and logic inserted in the "communication" function
of the subclass to create the new server

The 2 main functions required to create your own server are **recv** 
and **send** . Their **man** pages can be accessed in Linux systems.

A greeting server, that greets you on sending your name is given as 
an example to get started.

Compilation command can be seen in the **Makefile** 
