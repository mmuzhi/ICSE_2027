#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlsave.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>   // for std::transform, std::toupper
#include <cctype>      // for ::toupper

// Helper to recursively collect element nodes with a given tag name
static void collectElementsByName(xmlNodePtr node,
                                  const std::string& name,
                                  std::vector<xmlNodePtr>& result) {
    if (!node) return;
    if (node->type == XML_ELEMENT_NODE && name == reinterpret_cast<const char*>(node->name)) {
        result.push_back(node);
    }
    for (xmlNodePtr child = node->children; child; child = child->next) {
        collectElementsByName(child, name, result);
    }
}

class XMLProcessor {
private:
    std::string fileName;
    xmlDocPtr document;

public:
    XMLProcessor(const std::string& fname)
        : fileName(fname), document(nullptr) {}

    ~XMLProcessor() {
        if (document) {
            xmlFreeDoc(document);
        }
    }

    xmlDocPtr readXml() {
        // Parse the XML file
        xmlDocPtr doc = xmlReadFile(fileName.c_str(), nullptr, 0);
        if (!doc) {
            // In Java the exception is printed to stderr; we simulate that
            std::cerr << "Error: could not parse file " << fileName << std::endl;
            return nullptr;
        }
        // Normalize the document (equivalent to normalize() in Java DOM)
        xmlNodePtr root = xmlDocGetRootElement(doc);
        if (root) {
            // There is no direct normalize() in libxml2, but we can skip whitespace etc. if needed.
            // For behavior identical to Java (which normalizes text nodes) we can do nothing extra.
        }
        document = doc;
        return document;
    }

    bool writeXml(const std::string& fileName) {
        if (fileName.empty()) {
            return false;
        }
        if (!document) {
            return false;
        }
        int result = xmlSaveFile(fileName.c_str(), document);
        if (result == -1) {
            std::cerr << "Error: could not save file " << fileName << std::endl;
            return false;
        }
        return true;
    }

    bool processXmlData(const std::string& fileName) {
        if (!document) {
            return false;
        }

        // Find all <item> elements
        std::vector<xmlNodePtr> items;
        xmlNodePtr root = xmlDocGetRootElement(document);
        collectElementsByName(root, "item", items);

        // Set text content to uppercase
        for (xmlNodePtr item : items) {
            xmlChar* content = xmlNodeGetContent(item);
            if (content) {
                std::string upper(reinterpret_cast<char*>(content));
                std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
                xmlNodeSetContent(item, reinterpret_cast<const xmlChar*>(upper.c_str()));
                xmlFree(content);
            }
        }

        // Write the modified document to the given file
        return writeXml(fileName);
    }

    std::vector<xmlNodePtr> findElement(const std::string& elementName) {
        std::vector<xmlNodePtr> result;
        if (!document) {
            return result;
        }
        xmlNodePtr root = xmlDocGetRootElement(document);
        collectElementsByName(root, elementName, result);
        return result;
    }

    xmlDocPtr getDocument() const {
        return document;
    }

    void setDocument(xmlDocPtr doc) {
        // Free the previous document if any
        if (document) {
            xmlFreeDoc(document);
        }
        document = doc;
    }
};

// The following main function is not part of the original Java class,
// but we provide it as a minimal test driver (optional).
// It can be removed if the code is used as a library.
/*
int main() {
    // Initialize libxml2 globally (once per program)
    xmlInitParser();

    XMLProcessor processor("input.xml");
    processor.readXml();
    processor.processXmlData("output.xml");

    // Cleanup
    xmlCleanupParser();
    return 0;
}
*/