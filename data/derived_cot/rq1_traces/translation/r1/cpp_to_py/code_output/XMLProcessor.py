import tinyxml2

class XMLProcessor:
    def __init__(self, file_name):
        self.file_name = file_name
        self.doc = tinyxml2.XMLDocument()
    
    def read_xml(self):
        if self.doc.LoadFile(self.file_name) != tinyxml2.XML_SUCCESS:
            print(f"Error: Could not load XML file: {self.file_name}")
            return None
        return self.doc.RootElement()
    
    def write_xml(self, file_name):
        return self.doc.SaveFile(file_name) == tinyxml2.XML_SUCCESS
    
    def process_xml_data(self, file_name):
        root = self.doc.RootElement()
        if root is None:
            print("Error: No root element found.")
            return False
        
        element = root.FirstChildElement("item")
        while element is not None:
            text = element.GetText()
            if text is not None:
                upper_text = text.upper()
                element.SetText(upper_text)
            element = element.NextSiblingElement("item")
        
        return self.write_xml(file_name)
    
    def find_element(self, element_name):
        elements = []
        root = self.doc.RootElement()
        if root is None:
            return elements
        
        element = root.FirstChildElement(element_name)
        while element is not None:
            elements.append(element)
            element = element.NextSiblingElement(element_name)
        
        return elements