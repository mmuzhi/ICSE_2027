#include <pugixml.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <functional>
#include <cstring>

class XMLProcessor {
private:
    std::string fileName;
    pugi::xml_document document;

    std::string getTextContent(pugi::xml_node node) {
        switch (node.type()) {
            case pugi::node_pcdata:
            case pugi::node_cdata:
                return node.value();
            case pugi::node_document:
            case pugi::node_element: {
                std::string result;
                for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
                    result += getTextContent(child);
                }
                return result;
            }
            default:
                return "";
        }
    }

public:
    XMLProcessor(const std::string& fileName) : fileName(fileName) {}

    pugi::xml_document* readXml() {
        pugi::xml_parse_result result = document.load_file(fileName.c_str());
        if (result) {
            return &document;
        } else {
            std::cerr << "Error: " << result.description() << std::endl;
            return nullptr;
        }
    }

    bool writeXml(const std::string& fileName) {
        if (fileName.empty()) {
            return false;
        }
        if (document.empty()) {
            return false;
        }
        return document.save_file(fileName.c_str());
    }

    bool processXmlData(const std::string& fileName) {
        if (document.empty()) {
            return false;
        }

        std::vector<pugi::xml_node> items = findElement("item");
        for (pugi::xml_node item : items) {
            std::string text = getTextContent(item);
            std::transform(text.begin(), text.end(), text.begin(), 
                [](unsigned char c) { return std::toupper(c); });
            item.remove_children();
            item.append_child(pugi::node_pcdata).set_value(text.c_str());
        }

        return writeXml(fileName);
    }

    std::vector<pugi::xml_node> findElement(const std::string& elementName) {
        std::vector<pugi::xml_node> elements;
        if (document.empty()) {
            return elements;
        }

        std::function<void(pugi::xml_node)> traverse = [&](pugi::xml_node node) {
            if (node.type() == pugi::node_element) {
                if (elementName == "*" || std::strcmp(node.name(), elementName.c_str()) == 0) {
                    elements.push_back(node);
                }
            }
            for (pugi::xml_node child = node.first_child(); child; child = child.next_sibling()) {
                traverse(child);
            }
        };

        traverse(document);
        return elements;
    }

    pugi::xml_document* getDocument() {
        return &document;
    }

    void setDocument(const pugi::xml_document& doc) {
        document.reset(doc);
    }
};