import xml.etree.ElementTree as ET
import os

class XMLProcessor:
    def __init__(self, file_name):
        self.file_name = file_name
        self.tree = None
        self.root = None

    def read_xml(self):
        if self.tree is None:
            try:
                self.tree = ET.parse(self.file_name)
                self.root = self.tree.getroot()
            except Exception as e:
                print(f"Error: Could not load XML file: {self.file_name}: {str(e)}")
                return None
        return self.root

    def write_xml(self, file_name):
        if self.tree is None:
            return False
        try:
            self.tree.write(file_name, encoding="utf-8", xml_declaration=True)
            return True
        except Exception as e:
            print(f"Error: Could not write XML file: {file_name}: {str(e)}")
            return False

    def process_xml_data(self, file_name):
        root = self.read_xml()
        if root is None:
            return False

        for item_elem in root.findall("./item"):
            text = item_elem.text
            if text is not None:
                new_text = text.upper()
                item_elem.clear()
                item_elem.text = new_text
                item_elem.tail = None

        return self.write_xml(file_name)

    def find_element(self, element_name):
        if self.tree is None:
            return []
        return [child for child in self.root if child.tag == element_name]