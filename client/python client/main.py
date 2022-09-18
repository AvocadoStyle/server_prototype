import webrequests as wrq
import json
import struct

if __name__ == '__main__':
    # st_size = struct.calcsize('IBBHpc1')
    byte_time = 30
    file_name_len = 3
    file_content_len = 10
    header_size_str = f'1IBBH{file_name_len}s1I{file_content_len}s'
    struct1 = struct.Struct(header_size_str)
    message = struct1.pack(100, 1, 100, file_name_len, b'SASA', file_content_len, b'ABCDEFGHIJK')
    print(message)
    print(struct1.format)
    print(struct1.size)
    print(wrq.web_request(message))
    
    
