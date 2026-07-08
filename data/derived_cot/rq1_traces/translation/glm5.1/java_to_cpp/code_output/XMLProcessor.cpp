#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cctype>

// Requires the pugixml library (https://pugixml.org/)
#include <pugixml.hpp>

class XMLProcessor {
private:
    std::string fileName;
    std::unique_ptr<pugi::xml_document> document;

    // Helper to mimic Java's Element.getTextContent() 
    // which recursively concatenates all descendant text nodes.
    static std::string getTextContent(const pugi::xml_node& node) {
        std::string result;
        for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
            if (child.type() == pugi::node_pcdata || child.type() == pugi::node_cdata) {
                result += child.value();
            } else if (child.type() == pugi::node_element) {
                result += getTextContent(child);
            }
        }
        return result;
    }

    // Helper to mimic Java's Element.setTextContent() 
    // which removes all children and replaces them with a single text node.
    static void setTextContent(pugi::xml_node& node, const std::string& text) {
        while (pugi::xml_node child = node.first_child()) {
            node.remove_child(child);
        }
        node.append_child(pugi::node_pcdata).set_value(text.c_str());
    }

    // Helper to mimic Java's Document.getElementsByTagName() 
    // which finds all descendant elements with a given tag name.
    static void getElementsByTagName(const pugi::xml_node& root, const std::string& name, std::vector<pugi::xml_node>& result) {
        for (pugi::xml_node child = root.first_child(); child; child = child.next_sibling()) {
            if (child.type() == pugi::node_element) {
                if (child.name() == name) {
                    result.push_back(child);
                }
                getElementsByTagName(child, name, result);
            }
        }
    }

public:
    XMLProcessor(const std::string& fileName) : fileName(fileName), document(nullptr) {}

    pugi::xml_document* readXml() {
        try {
            document = std::make_unique<pugi::xml_document>();
            pugi::xml_parse_result result = document->load_file(fileName.c_str());
            
            if (!result) {
                std::cerr << "XML Parsing Error: " << result.description() << std::endl;
                document.reset();
                return nullptr;
            }
            
            // Java's normalize() merges adjacent text nodes and removes empty ones.
            // pugixml inherently handles this during parsing, so it's a no-op here 
            // but left as a comment for behavioral parity.
            // document->normalize(); 
            
            return document.get();
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            document.reset();
            return nullptr;
        }
    }

    bool writeXml(const std::string& fileName) {
        if (fileName.empty()) {
            return false;
        }
        if (!document) {
            return false;
        }

        try {
            // Java's default Transformer outputs indented XML.
            unsigned int flags = pugi::format_indent;
            if (!document->save_file(fileName.c_str(), "  ", flags, pugi::encoding_auto)) {
                std::cerr << "TransformerException: Failed to write XML file " << fileName << std::endl;
                return false;
            }
            return true;
        } catch (const std::exception& e) {
            std::cerr << "TransformerException: " << e.what() << std::endl;
            return false;
        }
    }

    bool processXmlData(const std::string& fileName) {
        if (!document) {
            return false;
        }

        std::vector<pugi::xml_node> items;
        getElementsByTagName(*document, "item", items);

        for (pugi::xml_node item : items) {
            std::string text = getTextContent(item);
            // Java's toUpperCase() is locale-specific. std::toupper handles ASCII.
            std::transform(text.begin(), text.end(), text.begin(),
                           [](unsigned char c){ return std::toupper(c); });
            setTextContent(item, text);
        }

        return writeXml(fileName);
    }

    std::vector<pugi::xml_node> findElement(const std::string& elementName) {
        std::vector<pugi::xml_node> elements;
        if (!document) {
            return elements;
        }

        getElementsByTagName(*document, elementName, elements);
        return elements;
    }

    pugi::xml_document* getDocument() {
        return document.get();
    }

    void setDocument(std::unique_ptr<pugi::xml_document> doc) {
        document = std::move(doc);
    }
};