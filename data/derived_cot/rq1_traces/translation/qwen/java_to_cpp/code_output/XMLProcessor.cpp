#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <memory>

// Define Element as xmlElementPtr for simplicity
using Element = xmlElementPtr;

class XMLProcessor {
private:
    std::string fileName;
    xmlDocPtr document;

    // Helper function to convert string to XML char*
    static xmlChar* stringToXmlChar(const std::string& str) {
        xmlChar* result = nullptr;
        if (!str.empty()) {
            result = xmlStrdup((const xmlChar*)str.c_str());
        }
        return result;
    }

    // Helper function to convert XML char* to std::string
    static std::string xmlCharToString(xmlChar* str) {
        if (str == nullptr) return "";
        std::string result((char*)str);
        xmlFree(str);
        return result;
    }

public:
    XMLProcessor(const std::string& fileName) : fileName(fileName), document(nullptr) {}

    ~XMLProcessor() {
        if (document != nullptr) {
            xmlFreeDoc(document);
        }
    }

    xmlDocPtr readXml() {
        if (fileName.empty()) {
            return nullptr;
        }

        try {
            document = xmlParseFile(fileName.c_str());
            if (document == nullptr) {
                throw std::runtime_error("Failed to parse XML file");
            }
            return document;
        } catch (const std::exception& e) {
            std::fprintf(stderr, "Error: %s\n", e.what());
            return nullptr;
        }
    }

    bool writeXml(const std::string& fileName) {
        if (fileName.empty() || document == nullptr) {
            return false;
        }

        try {
            xmlChar* outputFilename = stringToXmlChar(fileName);
            xmlSaveFormatFileEnc("UTF-8", document, outputFilename, 1);
            xmlFree(outputFilename);
            return true;
        } catch (const std::exception& e) {
            std::fprintf(stderr, "Error: %s\n", e.what());
            return false;
        }
    }

    bool processXmlData(const std::string& fileName) {
        if (document == nullptr) {
            return false;
        }

        try {
            // Process all "item" elements
            xmlNodePtr root = xmlDocGetRootElement(document);
            if (root == nullptr) {
                throw std::runtime_error("Document is empty");
            }

            for (xmlNodePtr node = root->children; node != nullptr; node = node->next) {
                if (node->type == XML_ELEMENT_NODE && xmlStrEqual(node->name, stringToXmlChar("item"))) {
                    xmlNodePtr textNode = xmlCopyNode(node->children, 1);
                    xmlChar* text = xmlNodeListGetString(textNode, 1);
                    if (text != nullptr) {
                        xmlChar* upperText = xmlStrup(text, -1);
                        xmlNodeSetContent(textNode, upperText);
                        xmlFree(upperText);
                    }
                    xmlFreeNode(textNode);
                }
            }

            // Write the modified document
            return writeXml(fileName);
        } catch (const std::exception& e) {
            std::fprintf(stderr, "Error: %s\n", e.what());
            return false;
        }
    }

    std::vector<Element> findElement(const std::string& elementName) {
        if (document == nullptr) {
            return {};
        }

        try {
            xmlChar* elemName = stringToXmlChar(elementName);
            xpathContext_t* xpathCtx = xpathNewContext(document);
            if (xpathCtx == nullptr) {
                throw std::runtime_error("Failed to create XPath context");
            }

            xpathObject_t* xpathObj = xpathEvalExpression(stringToXmlChar("//*[@tagname='" elemName "]"), xpathCtx);
            xpathFreeContext(xpathCtx);

            if (xpathObj == nullptr || xpathObj->type != XPATH_NODESET) {
                throw std::runtime_error("XPath evaluation failed");
            }

            int nodes = xpathObj->nodesetval->nodeNr;
            std::vector<Element> result;
            for (int i = 0; i < nodes; ++i) {
                if (xmlIsElement(xpathObj->nodesetval->nodeTab[i])) {
                    result.push_back((xmlElementPtr)xpathObj->nodesetval->nodeTab[i]);
                }
            }

            xpathFreeObject(xpathObj);
            return result;
        } catch (const std::exception& e) {
            std::fprintf(stderr, "Error: %s\n", e.what());
            return {};
        }
    }

    xmlDocPtr getDocument() {
        return document;
    }

    void setDocument(xmlDocPtr doc) {
        document = doc;
    }
};