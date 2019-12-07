// n_tree object
#include <string>
#include <vector>

typedef std::vector<std::string> data_list;
extern struct node
{
    node();
    std::string node_name;              // node name
    std::vector<node*> child_links;     // vector of child node pointers
    node* parrent;                      // pointer to parrent node
    data_list data;
};

node::node()
{
    this->node_name = "";
    this->parrent = nullptr;
}
node::node(std::string name, node* pnode)
{
    this->node_name = name;
    this->parrent = pnode;
}

extern class n_tree
{
private:
    node* root = nullptr;
public:
    n_tree();
    ~n_tree();

    node* find_node(std::string search_name);
    void add_node(std::string parrent_name);
    void add_data(std::string data, std::string parrent);
};

n_tree::n_tree()
{
    this.root = new node;
}

node* n_tree::find_node(std::string search_name)
{
    std::vector<node*> traverse_list;
    auto cur_node = this.root;
    node* temp = nullptr;
    bool found_node = false;
    while (true)
    {
        if((cur_node->node_name != parrent_name) && (cur_node->child_links.size() > 0))
        {
            while(true)
            {
                //start search at current node level
                for (size_t i = 0; i < cur_node->child_links.size(); i++)
                {
                    temp = cur_node->child_links.at(i);
                    if(temp->node_name == parrent_name)
                    {//assign new node to this accessed node at i'th position
                        found_node = true;
                        return(temp);
                    }
                    if(temp->child_links.size() > 0)
                    {
                        transverse_list.push_back(temp);
                    }  
                }
                if(traverse_list.size() > 0)
                {
                    cur_node = traverse_list.pop_back();
                }
                else
                {// node not found
                    return(nullptr);
                }
                
            }
        }
    }
}

void n_tree::add_node(std::string self_name, std::string parrent_name)
{
    //add data to new child node in currently accesed nodes child_links or is root and empty
    auto temp = this->find_node(parrent_name);
    if(temp != nullptr)
    {
        auto new_node = new node(self_name, temp);
        temp->child_links.push_back(new_node);
        new_node = nullptr;
        temp = nullptr;
    }
    return();
}

void n_tree::add_data(std::string data, std::string parrent_name)
{
    auto temp = find_node(parrent_name);
    if(temp != nullptr)
    {
        temp->data.push_back(data);
    }
    return();
}

n_tree::~n_tree()
{
    std::vector<node*> traverse_list;
    auto cur_node = this.root;
    node* temp = nullptr;
    while(true)
            {
                //start deletion at root node level
                for (size_t i = 0; i < cur_node->child_links.size(); i++)
                {
                    temp = cur_node->child_links.at(i);
                    if(temp->child_links.size() > 0)
                    {
                        transverse_list.push_back(temp);
                    }
                    else
                    {
                        delete(temp);
                    }
                      
                }
                if(traverse_list.size() > 0)
                {
                    cur_node = traverse_list.pop_back();
                }
                else
                {// at root
                    delete(this->root);
                    return();
                }
                
            } 
}
