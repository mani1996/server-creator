import cmd
import socket
import sys

class GreetClient(cmd.Cmd):
	''' A simple shell to type your name and get greeted by the GreetServer :) '''

	prompt = '>>> '
	intro = '''
	GREET-CLIENT
	A simple shell to type your name and get greeted by the GreetServer :)'
	'''
	doc_header = 'Commands'
	ruler = '-'


	def __init__(self, port):
		cmd.Cmd.__init__(self)
		self.nameSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
		self.nameSocket.connect(('localhost',int(port)))


	def emptyline(self):
		pass


	def default(self, line):
		self.stdout.write('ERROR : Unrecognised command "%s"\n'%line)


	def do_name(self, name):
		'Displays a greeting message, given the name.\nCommand is : name <your_name>'
		try:
			length = self.nameSocket.send(name)
			response = self.nameSocket.recv(1000)
			print response
		except Exception as e:
			print 'Error : '+e.message


	def do_EOF(self, line):
		return True


if __name__ == '__main__':
	if len(sys.argv) > 1:
		GreetClient(sys.argv[1]).cmdloop()
	else:
		raise Exception('usage: greet-client.py <port> ')