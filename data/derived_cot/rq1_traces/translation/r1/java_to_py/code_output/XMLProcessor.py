import xml.etree.ElementTree as ET
import traceback

class XMLProcessor:
    def __init__(self, file_name):
        self.file_name = file_name
        self.tree = None

    def read_xml(self):
        try:
            self.tree = ET.parse(self.file_name)
            return self.tree
        except Exception as e:
            traceback.print_exc()
            return None

    def write_xml(self, file_name):
        if file_name is None or file_name == "":
            return False
        if self.tree is None:
            return False
        try:
            self.tree.write(file_name, encoding='utf-8', xml_declaration=True)
            return True
        except Exception as e:
            traceback.print_exc()
            return False

    def process_xml_data(self, file_name):
        if self.tree is None:
            return False
        
        root = self.tree.getroot()
        for item in root.iter('item'):
            full_text = ''.join(item.itertext())
            item.text = full_text.upper()
            for child in list(item):
                item.remove(child)
        
        return self.write_xml(file_name)

    def find_element(self, element_name):
        elements = []
        if self.tree is None:
            return elements
        
        root = self.tree.getroot()
        for elem in root.iter(element_name):
            elements.append(elem)
        
        return elements

    def get_document(self):
        return self.tree

    def set_document(self, tree):
        self.tree = tree