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
            return self.white_list.copy()

    def del_white_list(self, addr):
        if addr in self.white_list:
            self.white_list.remove(addr)
            return self.white_list.copy()
        else:
            return []

    def recv(self, info):
        if "addr" not in info or "content" not in info:
            return -1
        try:
            addr = int(info["addr"])
        except ValueError:
            return -1
        content = info["content"]
        if addr in self.white_list:
            self.receive_struct = {"addr": str(addr), "content": content}
            return 1
        else:
            return 0

    def send(self, info):
        if "addr" not in info or "content" not in info:
            return "info structure is not correct"
        self.send_struct = {"addr": info["addr"], "content": info["content"]}
        return ""

    def show(self, type_str):
        if type_str == "send":
            return self.send_struct.copy()
        elif type_str == "receive":
            return self.receive_struct.copy()
        else:
            return {}