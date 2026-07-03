#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

#include "pugixml.hpp"

class XMLProcessor {
private:
    std::string file_name;
    pugi::xml_document doc;
    pugi::xml_node root;

public:
    XMLProcessor(const std::string& file_name)
        : file_name(file_name), root() {}

    // Reads the XML file and returns the root element.
    // Returns null node on failure (equivalent to None in Python).
    pugi::xml_node read_xml() {
        pugi::xml_parse_result result = doc.load_file(file_name.c_str());
        if (result) {
            root = doc.document_element();
            return root;
        } else {
            root = pugi::xml_node();   // null node
            return root;
        }
    }

    // Writes the XML data to the specified file.
    // Returns true on success, false on failure.
    bool write_xml(const std::string& file_name) {
        try {
            // If root is null, the Python code would raise an exception
            // which is caught and returns False.
            if (!root) {
                return false;
            }
            return doc.save_file(file_name.c_str());
        } catch (const std::exception&) {
            return false;
        }
    }

    // Modifies all <item> text to uppercase and writes the result to file_name.
    // Returns the result of write_xml. If root is null, throws (mimicking Python's AttributeError).
    bool process_xml_data(const std::string& file_name) {
        if (!root) {
            throw std::runtime_error("'NoneType' object has no attribute 'iter'");
        }

        // Select all descendant elements with tag "item" using XPath.
        pugi::xpath_node_set items = root.select_nodes("//item");
        for (pugi::xpath_node xitem : items) {
            pugi::xml_node item_node = xitem.node();
            std::string text = item_node.text().as_string();
            std::transform(text.begin(), text.end(), text.begin(), ::toupper);
            item_node.text().set(text.c_str());
        }

        return write_xml(file_name);
    }

    // Finds all elements with the given tag name.
    // Returns a vector of nodes. If root is null, throws (mimicking Python's AttributeError).
    std::vector<pugi::xml_node> find_element(const std::string& element_name) {
        if (!root) {
            throw std::runtime_error("'NoneType' object has no attribute 'findall'");
        }

        std::vector<pugi::xml_node> elements;
        std::string xpath_query = "//" + element_name;
        pugi::xpath_node_set nodes = root.select_nodes(xpath_query.c_str());
        for (pugi::xpath_node xnode : nodes) {
            elements.push_back(xnode.node());
        }
        return elements;
    }
};