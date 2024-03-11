import socket
import multiprocessing
import sys
import time
import colorama

def handle_data(s):
    print(f"{colorama.Fore.LIGHTBLUE_EX}[DATA SOCKET] OPENED")
    buffer = b""
    while True:
        data = s.recv(1024)
        if not data:
            break
        buffer += data
    print(f"[DATA SOCKET] RECEIVED DATA:\n"
          f"[{colorama.Fore.GREEN}{buffer.decode()}"
          f"{colorama.Fore.LIGHTBLUE_EX}]")
    s.close()
    print(f"[DATA SOCKET] CLOSED {colorama.Style.RESET_ALL}")

def open_data_socket(host, port):
    time.sleep(0.5)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    #create thread to handle data

    thread = multiprocessing.Process(target=handle_data, args=(s,))
    thread.start()

    return s

def get_response(s, buffer):
    response = buffer
    remaining = b""
    while not b"\r\n" in response:
        data = s.recv(1024)
        response += data
        if b"\r\n" in response:
            response, remaining = response.split(b"\r\n", 1)
            response += b"\r\n"
            break
    return response, remaining

def connect_to_server(host, port, file, sleep_time=1.0):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    if s.connect((host, port)):
        print(f"PROCESS {multiprocessing.current_process().name} COULD NOT "
              f"CONNECT TO SERVER")
        return
    else:
        print(f"PROCESS {multiprocessing.current_process().name} CONNECTED TO "
              f"SERVER")

    time.sleep(0.1)

    remain = b""
    response, remain = get_response(s, remain)
    print(f"R: [{response.decode().strip()}]")

    with open(file) as f:
        while True:
            line = f.readline()
            if not line:
                break
            if line.endswith("\n"):
                line = line[:-1]
                line += "\r\n"
            elif not line.endswith("\n"):
                line += "\r\n"
            print(f"S: {line.encode()}")
            s.send(line.encode())
            time.sleep(0.1)
            response, remain = get_response(s, remain)

            if "150" in response.decode():
                print(f"R: [{response.decode().strip()}]")
                response, remain = get_response(s, remain)
            if "227 Entering Passive Mode" in response.decode():
                pasv_mode = response.decode().split("(")[1].split(")")[0].split(",")
                host = ".".join(pasv_mode[:4])
                port = int(pasv_mode[4]) * 256 + int(pasv_mode[5])
                data_socket = open_data_socket(host, port)

            print(f"R: [{response.decode().strip()}]")
            print()
    s.close()
    print(f"PROCESS {multiprocessing.current_process().name} FINISHED")

def start_client(host, port, file):
    connect_to_server(host, port, file)

if __name__ == "__main__":

    nb_clients = 1 # nb clients

    files = [sys.argv[3] for _ in range(nb_clients)]

    processes = [multiprocessing.Process(target=start_client, args=(sys.argv[1], int(sys.argv[2]), file)) for file in files]
    for p in processes:
        p.start()
    for p in processes:
        p.join()