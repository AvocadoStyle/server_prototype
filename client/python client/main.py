import webrequests as wrq
import json
import struct

if __name__ == '__main__':
    # st_size = struct.calcsize('IBBHpc1')
    byte_time = 30
    file_name_len = 3
    header_size_str = f'1IBBH{file_name_len}s'
    struct1 = struct.Struct(header_size_str)
    message = struct1.pack(311137434, 1, 100, 10, b'CL2')
    print(message)
    print(struct1.format)
    print(struct1.size)
    wrq.web_request(message)
    
    
