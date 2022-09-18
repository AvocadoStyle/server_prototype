import socket

def web_request(req):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(('localhost', 8085))
    s.send(req)
    return s.recv(6533)