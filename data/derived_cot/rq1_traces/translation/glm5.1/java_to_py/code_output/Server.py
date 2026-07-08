class Server:
    def __init__(self):
        self.white_list = []
        self.send_struct = {}
        self.receive_struct = {}

    def add_white_list(self, addr: int) -> list | None:
        if addr in self.white_list:
            return None
        else:
            self.white_list.append(addr)
            return self.white_list

    def del_white_list(self, addr: int) -> list | None:
        if addr not in self.white_list:
            return None
        else:
            self.white_list.remove(addr)
            return self.white_list

    def recv(self, info: dict | None) -> int | bool | str:
        if info is None or "addr" not in info or "content" not in info:
            return -1
        
        addr = int(info["addr"])
        content = info["content"]
        
        if addr not in self.white_list:
            return False
        else:
            self.receive_struct["addr"] = addr
            self.receive_struct["content"] = content
            return self.receive_struct["content"]

    def send(self, info: dict | None) -> str | None:
        if info is None or "addr" not in info or "content" not in info:
            return "info structure is not correct"
        
        self.send_struct["addr"] = info["addr"]
        self.send_struct["content"] = info["content"]
        return None

    def show(self, struct_type: str) -> dict | None:
        if struct_type == "send":
            return self.send_struct
        elif struct_type == "receive":
            return self.receive_struct
        else:
            return None