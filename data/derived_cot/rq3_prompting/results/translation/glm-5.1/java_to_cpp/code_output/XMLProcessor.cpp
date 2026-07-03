#pragma once

#include <pugixml.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>

class XMLProcessor {
private:
    std::string fileName;
    pugi::xml_document* document;

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

    static void setTextContent(const pugi::xml_node& node, const std::string& text) {
        while (pugi::xml_node child = node.first_child()) {
            node.remove_child(child);
        }
        node.append_child(pugi::node_pcdata).set_value(text.c_str());
    }

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

    ~XMLProcessor() {
        delete document;
    }

    XMLProcessor(const XMLProcessor&) = delete;
    XMLProcessor& operator=(const XMLProcessor&) = delete;

    pugi::xml_document* readXml() {
        try {
            delete document;
            document = new pugi::xml_document();
            pugi::xml_parse_result result = document->load_file(fileName.c_str());
            if (!result) {
                std::cerr << "XML parse error: " << result.description() << std::endl;
                delete document;
                document = nullptr;
                return nullptr;
            }
            return document;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            delete document;
            document = nullptr;
            return nullptr;
        }
    }

    bool writeXml(const std::string& fileName) {
        if (fileName.empty()) {
            return false;
        }
        if (document == nullptr) {
            return false;
        }
        try {
            return document->save_file(fileName.c_str());
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

    bool processXmlData(const std::string& fileName) {
        if (document == nullptr) {
            return false;
        }

        std::vector<pugi::xml_node> items;
        getElementsByTagName(document->root(), "item", items);
        for (auto& item : items) {
            std::string text = getTextContent(item);
            std::transform(text.begin(), text.end(), text.begin(), ::toupper);
            setTextContent(item, text);
        }
        return writeXml(fileName);
    }

    std::vector<pugi::xml_node> findElement(const std::string& elementName) {
        std::vector<pugi::xml_node> elements;
        if (document == nullptr) {
            return elements;
        }
        getElementsByTagName(document->root(), elementName, elements);
        return elements;
    }

    pugi::xml_document* getDocument() const {
        return document;
    }

    void setDocument(pugi::xml_document* doc) {
        delete document;
        document = doc;
    }
};