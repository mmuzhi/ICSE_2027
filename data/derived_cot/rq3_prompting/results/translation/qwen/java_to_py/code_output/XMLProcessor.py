import xml.etree.ElementTree as ET
from xml.etree.ElementTree import Element, QName, ElementPath

class XMLProcessor:
    def __init__(self, fileName):
        self.fileName = fileName
        self.document = None

    def readXml(self):
        try:
            tree = ET.parse(self.fileName)
            root = tree.getroot()
            self.document = tree
            return self.document
        except Exception as e:
            print(f"Error reading XML: {e}")
            return None

    def writeXml(self, fileName):
        if fileName is None or fileName.strip() == "":
            return False
        try:
            if self.document is None:
                return False
            tree = ET.ElementTree(self.document.getroot())
            with open(fileName, 'wb') as f:
                tree.write(f, encoding='utf-8', xml_declaration=True)
            return True
        except Exception as e:
            print(f"Error writing XML: {e}")
            return False

    def processXmlData(self, fileName):
        if self.document is None:
            return False
        root = self.document.getroot()
        for elem in self.document.findall(".//item"):
            if elem.text is not None:
                elem.text = elem.text.upper()
        return self.writeXml(fileName)

    def findElement(self, elementName):
        if self.document is None:
            return []
        elements = []
        for elem in self.document.findall(elementName):
            elements.append(elem)
        return elements

    def getDocument(self):
        return self.document

    def setDocument(self, document):
        self.document = document