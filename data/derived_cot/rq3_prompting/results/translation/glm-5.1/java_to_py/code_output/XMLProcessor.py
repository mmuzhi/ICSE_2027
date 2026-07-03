import xml.dom.minidom as minidom
from xml.dom import Node
import traceback

class XMLProcessor:
    def __init__(self, fileName):
        self.fileName = fileName
        self.document = None

    @staticmethod
    def _getTextContent(node):
        if node.nodeType == Node.TEXT_NODE:
            return node.data
        text = ""
        for child in node.childNodes:
            text += XMLProcessor._getTextContent(child)
        return text

    @staticmethod
    def _setTextContent(node, text):
        while node.firstChild:
            node.removeChild(node.firstChild)
        node.appendChild(node.ownerDocument.createTextNode(text))

    def readXml(self):
        try:
            self.document = minidom.parse(self.fileName)
            self.document.normalize()
            return self.document
        except Exception:
            traceback.print_exc()
            return None

    def writeXml(self, fileName):
        if fileName is None or fileName == "":
            return False
        try:
            if self.document is None:
                return False
            with open(fileName, "w", encoding="utf-8") as f:
                f.write(self.document.toxml())
            return True
        except Exception:
            traceback.print_exc()
            return False

    def processXmlData(self, fileName):
        if self.document is None:
            return False
        items = self.document.getElementsByTagName("item")
        for i in range(items.length):
            item = items.item(i)
            if item.nodeType == Node.ELEMENT_NODE:
                text = self._getTextContent(item)
                self._setTextContent(item, text.upper())
        return self.writeXml(fileName)

    def findElement(self, elementName):
        elements = []
        if self.document is None:
            return elements
        nodeList = self.document.getElementsByTagName(elementName)
        for i in range(nodeList.length):
            if nodeList.item(i).nodeType == Node.ELEMENT_NODE:
                elements.append(nodeList.item(i))
        return elements

    def getDocument(self):
        return self.document

    def setDocument(self, document):
        self.document = document