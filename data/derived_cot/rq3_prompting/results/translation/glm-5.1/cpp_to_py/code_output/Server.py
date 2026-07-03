class Server:
    def __init__(self):
        self.white_list: list[int] = []
        self.send_struct: dict[str, str] = {}
        self.receive_struct: dict[str, str] = {}

    def add_white_list(self, addr: int) -> list[int]:
        if addr in self.white_list:
            return []
        else:
            self.white_list.append(addr)
            return self.white_list

    def del_white_list(self, addr: int) -> list[int]:
        if addr not in self.white_list:
            return []
        else:
            self.white_list.remove(addr)
            return self.white_list

    def recv(self, info: dict[str, str]) -> int:
        if "addr" not in info or "content" not in info:
            return -1
        addr = int(info["addr"])
        content = info["content"]

        if addr not in self.white_list:
            return 0
        else:
            self.receive_struct = {"addr": str(addr), "content": content}
            return 1

    def send(self, info: dict[str, str]) -> str:
        if "addr" not in info or "content" not in info:
            return "info structure is not correct"
        self.send_struct = {"addr": info["addr"], "content": info["content"]}
        return ""

    def show(self, type: str) -> dict[str, str]:
        if type == "send":
            return self.send_struct
        elif type == "receive":
            return self.receive_struct
        else:
            return {}