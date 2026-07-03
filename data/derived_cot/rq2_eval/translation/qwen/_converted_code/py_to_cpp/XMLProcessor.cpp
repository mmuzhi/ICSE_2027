#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string>
#include <vector>
#include <algorithm>

class XMLProcessor {
private:
    std::string file_name;
    xmlDocPtr doc;

public:
    XMLProcessor(const std::string& file_name) : file_name(file_name), doc(nullptr) {}

    ~XMLProcessor() {
        if (doc != nullptr) {
            xmlFreeDoc(doc);
        }
    }

    xmlNodePtr read_xml() {
        doc = xmlParseFile(file_name.c_str());
        if (doc == nullptr) {
            return nullptr;
        }

        xmlNodePtr root_node = xmlDocGetRootElement(doc);
        if (root_node == nullptr) {
            xmlFreeDoc(doc);
            doc = nullptr;
            return nullptr;
        }

        return root_node;
    }

    bool write_xml(const std::string& file_name) {
        if (doc == nullptr) {
            return false;
        }

        if (xmlSaveFile(file_name.c_str(), doc) == -1) {
            return false;
        }
        return true;
    }

    bool process_xml_data(const std::string& file_name) {
        if (doc == nullptr) {
            return false;
        }

        xmlXPathContextPtr context = xmlXPathNewContext(doc);
        if (context == nullptr) {
            return false;
        }

        xmlXPathObjectPtr result = xmlXPathEvalExpression((const xmlChar*)"//item", context);
        if (result == nullptr) {
            xmlXPathFreeContext(context);
            return false;
        }

        xmlNodePtr *nodes = (xmlNodePtr *)result->nodesetval->nodevec;
        int count = result->nodesetval->nodeNr;

        for (int i = 0; i < count; i++) {
            xmlNodePtr node = nodes[i];
            if (node->type != XML_ELEMENT_NODE) {
                continue;
            }

            xmlChar* text = xmlNodeListGetString(node, node->children, 1);
            if (text == nullptr) {
                continue;
            }

            // Convert to uppercase
            std::string text_str(reinterpret_cast<char*>(text));
            std::transform(text_str.begin(), text_str.end(), text_str.begin(),
                [](unsigned char c) {
                    if (c >= 'a' && c <= 'z') {
                        return 'A' + (c - 'a');
                    }
                    return c;
                });

            xmlFree(text);

            xmlNodePtr text_node = xmlNewText(BAD_CAST text_str.c_str());
            xmlAddChild(node, text_node);
            xmlClearNode(node);
        }

        xmlXPathFreeContext(context);
        xmlXPathFreeObject(result);

        return write_xml(file_name);
    }

    std::vector<xmlNodePtr> find_element(const std::string& element_name) {
        if (doc == nullptr) {
            return {};
        }

        xmlXPathContextPtr context = xmlXPathNewContext(doc);
        if (context == nullptr) {
            return {};
        }

        std::string xpath = "//" + element_name;
        xmlXPathObjectPtr result = xmlXPathEvalExpression((const xmlChar*)xpath.c_str(), context);

        if (result == nullptr) {
            xmlXPathFreeContext(context);
            return {};
        }

        std::vector<xmlNodePtr> elements;
        for (int i = 0; i < result->nodesetval->nodeNr; i++) {
            xmlNodePtr node = result->nodesetval->nodevec[i];
            if (node->type == XML_ELEMENT_NODE) {
                elements.push_back(node);
            }
        }

        xmlXPathFreeContext(context);
        xmlXPathFreeObject(result);

        return elements;
    }
};