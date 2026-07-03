#include <libxml++++/document.h>
#include <libxml++++/node.h>
#include <string>
#include <vector>

class XMLProcessor {
private:
    std::string file_name;
    Glib::RefPtr<xmlpp::Document> doc;

public:
    XMLProcessor(const std::string& file_name);
    ~XMLProcessor();

    xmlpp::Node::Pointer read_xml();
    bool write_xml(const std::string& file_name);
    bool process_xml_data(const std::string& file_name);
    std::vector<xmlpp::Node::Pointer> find_element(const std::string& element_name);
};

XMLProcessor::XMLProcessor(const std::string& file_name)
    : file_name(file_name), doc() {}

XMLProcessor::~XMLProcessor() = default;

xmlpp::Node::Pointer XMLProcessor::read_xml() {
    try {
        doc = xmlpp::parse(file_name);
        return doc->root_element();
    } catch (...) {
        return nullptr;
    }
}

bool XMLProcessor::write_xml(const std::string& file_name) {
    try {
        doc->write_to_file(file_name);
        return true;
    } catch (...) {
        return false;
    }
}

bool XMLProcessor::process_xml_data(const std::string& file_name) {
    if (!doc) {
        return false;
    }

    xmlpp::Node::Pointer root = doc->root_element();
    if (!root) {
        return false;
    }

    std::vector<xmlpp::Node::Pointer> items = root->find_descendants("item");
    for (auto& item : items) {
        std::string text = item->get_content();
        item->set_content(text.empty() ? "" : text);
    }

    return write_xml(file_name);
}

std::vector<xmlpp::Node::Pointer> XMLProcessor::find_element(const std::string& element_name) {
    if (!doc) {
        return std::vector<xmlpp::Node::Pointer>();
    }

    xmlpp::Node::Pointer root = doc->root_element();
    if (!root) {
        return std::vector<xmlpp::Node::Pointer>();
    }

    return root->find_descendants(element_name);
}