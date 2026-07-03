import xml.etree.ElementTree as ET
import sys
import traceback
from typing import List, Optional


class XMLProcessor:
    def __init__(self, file_name: str):
        self.file_name = file_name
        self.document = None  # type: Optional[ET.ElementTree]

    def read_xml(self) -> Optional[ET.ElementTree]:
        try:
            self.document = ET.parse(self.file_name)
            self.document.getroot()  # ensures the file was parsed (raises if invalid)
            return self.document
        except Exception:
            traceback.print_exc()
            return None

    def write_xml(self, file_name: str) -> bool:
        if file_name is None or file_name == "":
            return False
        try:
            if self.document is None:
                return False
            self.document.write(file_name, encoding="utf-8", xml_declaration=True)
            return True
        except Exception:
            traceback.print_exc()
            return False

    def process_xml_data(self, file_name: str) -> bool:
        if self.document is None:
            return False

        for item in self.document.iter("item"):
            if item.text:
                item.text = item.text.upper()
        return self.write_xml(file_name)

    def find_element(self, element_name: str) -> List[ET.Element]:
        if self.document is None:
            return []
        return list(self.document.iter(element_name))

    def get_document(self) -> Optional[ET.ElementTree]:
        return self.document

    def set_document(self, document: ET.ElementTree) -> None:
        self.document = document