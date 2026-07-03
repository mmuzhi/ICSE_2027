import xml.etree.ElementTree as ET
from xml.dom import minidom
import os

class XMLProcessor:

    def __init__(self, fileName):
        self.fileName = fileName
        self.document = None

    def read_xml(self):
        try:
            tree = ET.parse(self.fileName)
            self.document = tree.getroot()
            return self.document
        except Exception as e:
            print(e)
            return None

    def write_xml(self, fileName):
        if self.document is None or fileName is None or fileName.strip() == '':
            return False
        try:
            rough_string = ET.tostring(self.document, encoding='utf-8').decode('utf-8')
            reparsed = minidom.parseString(rough_string)
            pretty_xml_as_string = reparsed.toprettyxml(indent='  ')
            with open(fileName, 'w') as f:
                f.write(pretty_xml_as_string)
            return True
        except Exception as e:
            print(e)
            return False

    def process_xml_data(self, fileName):
        if self.document is None:
            return False
        for elem in self.document.iter('item'):
            if elem.text is not None:
                elem.text = elem.text.upper()
        return self.write_xml(fileName)

    def find_element(self, elementName):
        if self.document is None:
            return []
        elements = self.document.findall('.//' + elementName)
        return elements

    def getDocument(self):
        return self.document

    def setDocument(self, document):
        self.document = document