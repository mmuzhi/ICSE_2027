#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <tinyxml2.h>

class XMLProcessor {
private:
    std::string file_name;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* root;

    // Helper to recursively iterate over all descendants, mimicking Python's root.iter()
    void process_items_recursive(tinyxml2::XMLElement* element) {
        if (!element) return;
        
        // Check if the current element's tag is "item"
        if (std::string(element->Value()) == "item") {
            tinyxml2::XMLNode* first_child = element->FirstChild();
            
            // In Python, element.text is None if there's no text, and text.upper() would throw AttributeError.
            // We replicate this by throwing if the first child is not a text node.
            if (!first_child || !first_child->ToText()) {
                throw std::runtime_error("Element 'item' has no text node");
            }
            
            tinyxml2::XMLText* text_node = first_child->ToText();
            std::string str_text = text_node->Value();
            
            // Convert string to uppercase
            std::transform(str_text.begin(), str_text.end(), str_text.begin(), [](unsigned char c) {
                return std::toupper(c);
            });
            
            // Modify the text node directly. This preserves any child elements 
            // that might come after the text, identical to Python's element.text behavior.
            text_node->SetValue(str_text.c_str());
        }
        
        // Recursively process children
        for (tinyxml2::XMLElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
            process_items_recursive(child);
        }
    }

public:
    XMLProcessor(const std::string& file_name) : file_name(file_name), root(nullptr) {}

    /**
     * Reads the XML file and returns the root element.
     * Returns nullptr if the file cannot be parsed.
     */
    tinyxml2::XMLElement* read_xml() {
        if (doc.LoadFile(file_name.c_str()) != tinyxml2::XML_SUCCESS) {
            root = nullptr;
            return nullptr;
        }
        root = doc.RootElement();
        return root;
    }

    /**
     * Writes the XML data to the specified file.
     * Returns true if successful, false otherwise.
     */
    bool write_xml(const std::string& file_name) {
        if (!root) {
            return false;
        }
        try {
            return doc.SaveFile(file_name.c_str()) == tinyxml2::XML_SUCCESS;
        } catch (...) {
            return false;
        }
    }

    /**
     * Modifies the data in XML elements and writes the updated XML data to a new file.
     * Throws std::runtime_error if root is null or an item has no text.
     */
    bool process_xml_data(const std::string& file_name) {
        if (!root) {
            throw std::runtime_error("Root element is null");
        }
        process_items_recursive(root);
        return write_xml(file_name);
    }

    /**
     * Finds the XML elements with the specified name.
     * Searches only direct children, identical to Python's findall().
     * Throws std::runtime_error if root is null.
     */
    std::vector<tinyxml2::XMLElement*> find_element(const std::string& element_name) {
        if (!root) {
            throw std::runtime_error("Root element is null");
        }
        std::vector<tinyxml2::XMLElement*> elements;
        for (tinyxml2::XMLElement* child = root->FirstChildElement(element_name.c_str()); 
             child != nullptr; 
             child = child->NextSiblingElement(element_name.c_str())) {
            elements.push_back(child);
        }
        return elements;
    }
};