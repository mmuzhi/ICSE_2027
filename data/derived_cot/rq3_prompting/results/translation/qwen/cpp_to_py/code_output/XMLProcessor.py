import sys
import xml.etree.ElementTree as ET

class XMLProcessor:
    def __init__(self, file_name):
        self.file_name = file_name
        self.root = None

    def read_xml(self):
        if self.root is None:
            try:
                tree = ET.parse(self.file_name)
                self.root = tree.getroot()
            except ET.ParseError as e:
                sys.stderr.write(f"Error: Could not load XML file: {self.file_name}: {e}\n")
                self.root = None
                return None
        return self.root

    def write_xml(self, file_name):
        if self.root is None:
            return False
        try:
            tree = ET.ElementTree(self.root)
            tree.write(file_name, encoding='utf-8', xml_declaration=True)
            return True
        except Exception as e:
            sys.stderr.write(f"Error: Could not write XML file: {file_name}: {e}\n")
            return False

    def process_xml_data(self, file_name):
        root = self.read_xml()
        if root is None:
            return False

        for item in root.findall('item'):
            text = item.text
            if text is not None:
                item.text = None
                for child in list(item):
                    item.remove(child)
                item.text = text.upper()

        return self.write_xml(file_name)

    def find_element(self, element_name):
        if self.root is None:
            return []
        return self.root.findall(element_name)