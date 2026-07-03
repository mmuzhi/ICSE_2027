import sys
import xml.etree.ElementTree as ET


class XMLProcessor:
    def __init__(self, file_name: str):
        self.file_name = file_name
        self.doc = None   # will hold the parsed ElementTree
        self._root = None # cached root element (convenience)

    def read_xml(self):
        """Load the XML file and return the root element (or None on failure)."""
        try:
            tree = ET.parse(self.file_name)
            root = tree.getroot()
            self.doc = tree
            self._root = root
            return root
        except (ET.ParseError, FileNotFoundError, IOError) as e:
            print(f"Error: Could not load XML file: {self.file_name}", file=sys.stderr)
            return None

    def write_xml(self, file_name: str) -> bool:
        """Save the current document to the given file name. Returns True on success."""
        if self.doc is None:
            return False
        try:
            self.doc.write(file_name, encoding="utf-8", xml_declaration=True)
            return True
        except (IOError, OSError):
            return False

    def process_xml_data(self, file_name: str) -> bool:
        """Convert the text of all <item> children to uppercase and save to file."""
        root = self._root
        if root is None:
            print("Error: No root element found.", file=sys.stderr)
            return False

        # Iterate over direct child elements with tag "item"
        for child in list(root):  # use list to avoid mutation issues if needed
            if child.tag == "item":
                text = child.text
                if text is not None:
                    upper_text = text.upper()
                    child.text = upper_text   # replace text content

        return self.write_xml(file_name)

    def find_element(self, element_name: str):
        """Return a list of direct child elements with the given tag name."""
        result = []
        root = self._root
        if root is None:
            return result
        for child in root:
            if child.tag == element_name:
                result.append(child)
        return result