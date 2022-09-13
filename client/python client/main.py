import webrequests as wrq
import json
import struct

if __name__ == '__main__':
    # st_size = struct.calcsize('IBBHpc1')
    byte_time = 30
    file_name_len = 10
    header_size_str = f'IBBHB{file_name_len}s'
    struct1 = struct.Struct(header_size_str)
    print(struct1.format)
    print(struct1.size)