#include <pugixml.hpp>
#include <vector>
#include <cctype>
#include <algorithm>
#include <string>

class XMLProcessor {
private:
    std::string file_name;
    pugi::xml_document doc;

public:
    XMLProcessor(const std::string& file_name) : file_name(file_name) {}

    pugi::xml_node read_xml() {
        pugi::xml_document temp;
        pugi::xml_parse_result result = temp.load_file(file_name.c_str());
        if (result) {
            doc = std::move(temp);
            return doc.root();
        }
        return pugi::xml_node(); // null node
    }

    bool write_xml(const std::string& file_name) {
        return doc.save_file(file_name.c_str());
    }

    bool process_xml_data(const std::string& file_name) {
        pugi::xpath_node_set nodes = doc.select_nodes("//item");
        for (pugi::xpath_node xpath_node : nodes) {
            pugi::xml_node node = xpath_node.node();
            std::string text = node.text().get();
            std::transform(text.begin(), text.end(), text.begin(), 
                [](unsigned char c) { return std::toupper(c); });
            node.text().set(text.c_str());
        }
        return write_xml(file_name);
    }

    std::vector<pugi::xml_node> find_element(const std::string& element_name) {
        std::vector<pugi::xml_node> result;
        pugi::xml_node root = doc.root();
        if (root) {
            for (pugi::xml_node child : root.children(element_name.c_str())) {
                result.push_back(child);
            }
        }
        return result;
    }
};