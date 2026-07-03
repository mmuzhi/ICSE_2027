#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include "tinyxml2.h"

class XMLProcessor {
private:
    std::string file_name;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* root;

    void find_elements_recursive(tinyxml2::XMLElement* parent, const std::string& name,
                                 std::vector<tinyxml2::XMLElement*>& results) {
        for (tinyxml2::XMLElement* child = parent->FirstChildElement();
             child != nullptr; child = child->NextSiblingElement()) {
            if (std::string(child->Name()) == name) {
                results.push_back(child);
            }
            find_elements_recursive(child, name, results);
        }
    }

public:
    XMLProcessor(const std::string& file_name)
        : file_name(file_name), root(nullptr) {}

    tinyxml2::XMLElement* read_xml() {
        if (doc.LoadFile(file_name.c_str()) != tinyxml2::XML_SUCCESS) {
            root = nullptr;
            return nullptr;
        }
        root = doc.RootElement();
        return root;
    }

    bool write_xml(const std::string& out_file_name) {
        if (root == nullptr) {
            return false;
        }
        return doc.SaveFile(out_file_name.c_str()) == tinyxml2::XML_SUCCESS;
    }

    bool process_xml_data(const std::string& out_file_name) {
        if (root == nullptr) {
            return false;
        }
        std::vector<tinyxml2::XMLElement*> items;
        find_elements_recursive(root, "item", items);
        for (auto* element : items) {
            const char* text = element->GetText();
            if (text) {
                std::string upper_text(text);
                std::transform(upper_text.begin(), upper_text.end(),
                               upper_text.begin(), [](unsigned char c) { return std::toupper(c); });
                element->SetText(upper_text.c_str());
            }
        }
        return write_xml(out_file_name);
    }

    std::vector<tinyxml2::XMLElement*> find_element(const std::string& element_name) {
        std::vector<tinyxml2::XMLElement*> elements;
        if (root == nullptr) {
            return elements;
        }
        for (tinyxml2::XMLElement* child = root->FirstChildElement(element_name.c_str());
             child != nullptr;
             child = child->NextSiblingElement(element_name.c_str())) {
            elements.push_back(child);
        }
        return elements;
    }
};