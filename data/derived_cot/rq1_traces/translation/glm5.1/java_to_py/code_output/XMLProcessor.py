import xml.dom.minidom as minidom
import xml.dom.Node as Node
import traceback

def _get_text_content(node):
    """Helper to mimic Java's Node.getTextContent()"""
    if node.nodeType in (Node.TEXT_NODE, Node.CDATA_SECTION_NODE):
        return node.data
    return "".join(_get_text_content(child) for child in node.childNodes)

def _set_text_content(node, text):
    """Helper to mimic Java's Node.setTextContent()"""
    # Remove all existing children
    while node.firstChild:
        node.removeChild(node.firstChild)
    # Append a new text node
    node.appendChild(node.ownerDocument.createTextNode(text))

class XMLProcessor:
    def __init__(self, file_name):
        self.file_name = file_name
        self.document = None

    def read_xml(self):
        try:
            self.document = minidom.parse(self.file_name)
            self.document.documentElement.normalize()
            return self.document
        except Exception as e:
            traceback.print_exc()
            return None

    def write_xml(self, file_name):
        if file_name is None or file_name == "":
            return False
        try:
            if self.document is None:
                return False

            with open(file_name, "w", encoding="utf-8") as f:
                # writexml replicates the default Java Transformer behavior
                self.document.writexml(f, indent="", addindent="", newl="")
            return True
        except Exception as e:
            traceback.print_exc()
            return False

    def process_xml_data(self, file_name):
        if self.document is None:
            return False

        items = self.document.getElementsByTagName("item")
        for i in range(len(items)):
            item = items[i]
            if item.nodeType == Node.ELEMENT_NODE:
                element = item
                text = _get_text_content(element)
                _set_text_content(element, text.upper())

        return self.write_xml(file_name)

    def find_element(self, element_name):
        elements = []
        if self.document is None:
            return elements

        node_list = self.document.getElementsByTagName(element_name)
        for i in range(len(node_list)):
            if node_list[i].nodeType == Node.ELEMENT_NODE:
                elements.append(node_list[i])
        return elements

    def get_document(self):
        return self.document

    def set_document(self, document):
        self.document = document