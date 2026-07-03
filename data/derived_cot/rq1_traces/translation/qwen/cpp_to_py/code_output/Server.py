from typing import List, Dict

class Server:
    def __init__(self):
        self.white_list: List[int] = []
        self.send_struct: Dict[str, str] = {}
        self.receive_struct: Dict[str, str] = {}

    def add_white_list(self, addr: int) -> List[int]:
        if addr in self.white_list:
            return []
        else:
            self.white_list.append(addr)
            return self.white_list[:]

    def del_white_list(self, addr: int) -> List[int]:
        if addr not in self.white_list:
            return []
        else:
            self.white_list.remove(addr)
            return self.white_list[:]

    def recv(self, info: Dict[str, str]) -> int:
        if "addr" not in info or "content" not in info:
            return -1
        try:
            addr = int(info["addr"])
        except ValueError:
            raise ValueError("Invalid integer for addr")
        if addr not in self.white_list:
            return 0
        self.receive_struct = {"addr": str(addr), "content": info["content"]}
        return 1

    def send(self, info: Dict[str, str]) -> str:
        if "addr" not in info or "content" not in info:
            return "info structure is not correct"
        self.send_struct = {"addr": info["addr"], "content": info["content"]}
        return ""

    def show(self, type_str: str) -> Dict[str, str]:
        if type_str == "send":
            return self.send_struct.copy()
        elif type_str == "receive":
            return self.receive_struct.copy()
        else:
            return {}