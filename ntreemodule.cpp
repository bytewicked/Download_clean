// n_tree object
#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>

// https://en.wikibooks.org/wiki/Python_Programming/Extending_with_C%2B%2B
// https://www.boost.org/doc/libs/1_61_0/libs/python/doc/html/tutorial/tutorial/exposing.html

#include <string>
#include <vector>

typedef std::vector<std::string> data_list;
struct node
{
    node();
    node(std::string name, node* pnode);
    std::string node_name;              // node name
    std::vector<node*> child_links;     // vector of child node pointers
    node* parent;                      // pointer to parent node
    data_list data;
};

node::node()
{
    this->node_name = "";
    this->parent = nullptr;
}
node::node(std::string name, node* pnode)
{
    this->node_name = name;
    this->parent = pnode;
}

class n_tree
{
private:
    node* root = nullptr;
    node* find_node(std::string search_name);
public:
    n_tree();
    ~n_tree();
    
    std::string find_name(std::string search_name);
    void add_node(std::string self_name, std::string parent_name);
    void add_data(std::string data, std::string parent_name);
};

n_tree::n_tree()
{
    this->root = new node();
}

node* n_tree::find_node(std::string search_name)
{
    std::vector<node*> t_list;
    auto cur_node = this->root;
    node* temp = nullptr;
    while (true)
    {
        if((cur_node->node_name != search_name) && (cur_node->child_links.size() > 0))
        {
            //start search at current node level
            for (size_t i = 0; i < cur_node->child_links.size(); i++)
            {
                temp = cur_node->child_links.at(i);
                if(temp->node_name == search_name)
                {//assign new node to this accessed node at i'th position
                    return(temp);
                }
                if(temp->child_links.size() > 0)
                {
                    t_list.push_back(temp);
                }  
            }
            if(t_list.size() > 0)
            {
                cur_node = t_list.back();
                t_list.pop_back();
            }
            else
            {// node not found
                return(nullptr);
            }
        }
    }
}

std::string n_tree::find_name(std::string search_name)
{
    auto temp = find_node(search_name);
    if (temp)
    {
        return temp->node_name;
    }
    else
    {
        return "";
    }
    
    
}

void n_tree::add_node(std::string self_name, std::string parent_name)
{
    //add data to new child node in currently accesed nodes child_links or is root and empty
    auto temp = this->find_node(parent_name);
    if(temp != nullptr)
    {
        auto new_node = new node(self_name, temp);
        temp->child_links.push_back(new_node);
        new_node = nullptr;
        temp = nullptr;
    }
    return;
}

void n_tree::add_data(std::string data, std::string parent_name)
{
    auto temp = this->find_node(parent_name);
    if(temp != nullptr)
    {
        temp->data.push_back(data);
    }
    return;
}

n_tree::~n_tree()
{
    std::vector<node*> t_list = std::vector<node*>();
    auto cur_node = this->root;
    node* temp = nullptr;
    while(true)
    {
        //start deletion at root node level
        for (size_t i = 0; i < cur_node->child_links.size(); i++)
        {
            temp = cur_node->child_links.at(i);
            if(temp->child_links.size() > 0)
            {
                t_list.push_back(temp);
            }
            else
            {
                delete(temp);
            }
                
        }
        if(t_list.size() > 0)
        {
            cur_node = t_list.back();
            t_list.pop_back();
        }
        else
        {// at root
            delete(this->root);
            return;
        }
        
    } 
}

using namespace boost::python;
BOOST_PYTHON_MODULE(n_tree)
{
    class_<n_tree>("n_tree")
    .def("add_node", &n_tree::add_node)
    .def("add_data", &n_tree::add_data)
    .def("find_name", &n_tree::find_name);
}