class Server:
    def __init__(self):
        self.white_list = []
        self.send_struct = {}
        self.receive_struct = {}

    def add_white_list(self, addr):
        if addr in self.white_list:
            return []
        else:
            self.white_list.append(addr)
            # Return a copy to mimic C++ return-by-value semantics (prevents external modification)
            return self.white_list.copy()

    def del_white_list(self, addr):
        if addr not in self.white_list:
            return []
        else:
            self.white_list.remove(addr)
            # Return a copy to mimic C++ return-by-value semantics (prevents external modification)
            return self.white_list.copy()

    def recv(self, info):
        if "addr" not in info or "content" not in info:
            return -1
        
        # std::stoi throws std::invalid_argument if conversion fails.
        # Python's int() throws ValueError, which is the idiomatic equivalent.
        addr = int(info["addr"])
        content = info["content"]

        if addr not in self.white_list:
            return 0
        else:
            self.receive_struct = {"addr": str(addr), "content": content}
            return 1

    def send(self, info):
        if "addr" not in info or "content" not in info:
            return "info structure is not correct"
        
        self.send_struct = {"addr": info["addr"], "content": info["content"]}
        return ""

    def show(self, type):
        if type == "send":
            # Return a copy to mimic C++ return-by-value semantics (prevents external modification)
            return self.send_struct.copy()
        elif type == "receive":
            # Return a copy to mimic C++ return-by-value semantics (prevents external modification)
            return self.receive_struct.copy()
        else:
            return {}