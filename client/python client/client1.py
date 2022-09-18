import webrequests as wrq
import json
import struct

if __name__ == '__main__':
    # st_size = struct.calcsize('IBBHpc1')
    byte_time = 30
    file_name_len = 3
    file_content_len = 10
    # header_size_str = f'1IBBH{file_name_len}s1I{file_content_len}s'
    header_size_str = f'1IBBH{file_name_len}s'
    struct1 = struct.Struct(header_size_str)



    header_size_prototype = f'BHH{file_name_len}s1I{12}s'
    struct2 = struct.Struct(header_size_prototype)







    # message = struct1.pack(100, 1, 200, file_name_len, b'CL2', file_content_len, b'KAKI')
    message = struct1.pack(100, 1, 200, file_name_len, b'CL1')
    # print(message)
    # print(struct1.format)
    # print(struct1.size)
    # print("struct 2 " + struct2.format)
    # print(struct2.size)
    # print(wrq.web_request(message))
    recv = wrq.web_request(message)
    print(f'struct2 format: {struct2.format} struct2 size: {struct2.size}')
    print(recv)
    # msg_recv = struct2.unpack(recv)

    a = struct.unpack(f'B1B2B3s', recv)

    print(a)
