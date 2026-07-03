#include <libxml/parser.h>
#include <libxml/tree.h>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>

class XMLProcessor {
private:
    std::string fileName;
    xmlDoc* document;

public:
    XMLProcessor(const std::string& fileName) : fileName(fileName), document(nullptr) {}

    ~XMLProcessor() {
        if (document != nullptr) {
            xmlFreeDoc(document);
        }
    }

    xmlDoc* readXml() {
        document = xmlParseFile(fileName.c_str());
        if (document == nullptr) {
            xmlPrintError(stderr);
            return nullptr;
        }
        return document;
    }

    bool writeXml(const std::string& fileName) {
        if (fileName.empty() || document == nullptr) {
            return false;
        }
        int ret = xmlSaveFormatFile(fileName.c_str(), document, 1);
        if (ret == -1) {
            xmlPrintError(stderr);
            return false;
        }
        return true;
    }

    bool processXmlData(const std::string& fileName) {
        if (document == nullptr) {
            return false;
        }

        xmlNodePtr root_node = xmlDocGetRootElement(document);
        if (root_node == nullptr) {
            xmlPrintError(stderr);
            return false;
        }

        xmlNodePtr cur_node = nullptr;
        for (cur_node = root_node->children; cur_node; cur_node = cur_node->next) {
            if (cur_node->type == XML_ELEMENT_NODE && !xmlStrcmp(cur_node->name, BAD_CAST"item")) {
                xmlNodePtr text_node = cur_node->children;
                if (text_node != nullptr && text_node->type == XML_TEXT_NODE) {
                    char* text = (char*)xmlNodeGetContent(text_node);
                    if (text != nullptr) {
                        for (char* c = text; *c; ++c) {
                            *c = std::toupper(*c);
                        }
                        xmlNodeSetContent(text_node, text);
                        free(text);
                    }
                }
            }
        }

        return writeXml(fileName);
    }

    std::vector<xmlNode*> findElement(const std::string& elementName) {
        if (document == nullptr) {
            return {};
        }

        xmlNodePtr root = xmlDocGetRootElement(document);
        if (root == nullptr) {
            return {};
        }

        xmlNodePtr node = nullptr;
        std::vector<xmlNode*> elements;

        for (node = root->children; node != nullptr; node = node->next) {
            if (node->type == XML_ELEMENT_NODE && !xmlStrcmp(node->name, BAD_CAST elementName.c_str())) {
                elements.push_back(node);
            }
        }

        return elements;
    }

    xmlDoc* getDocument() {
        return document;
    }

    void setDocument(xmlDoc* doc) {
        document = doc;
    }
};