// n_tree object

#include <python3.7m/Python.h>

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
    printf("deleting object\n");
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

// static PyMethodDef n_tree_funcs[] = {
//     {"find_name", n_tree::find_name, METH_VARARGS, NULL},
//     {"add_node", n_tree::add_node, METH_VARARGS, NULL},
//     {"add_data", n_tree::add_data, METH_VARARGS, NULL},
//     {NULL, NULL, 0, NULL}
// };

namespace python_function
{
    n_tree* evil_pointer = nullptr;

    static PyObject* init_ntree(PyObject *self, PyObject *args)
    {
        evil_pointer = new n_tree();
        printf("instantized new object!\n");
        Py_XINCREF(NULL);
        return Py_None;
    }
    static PyObject* del_ntree(PyObject *self, PyObject *args)
    {
        delete evil_pointer;
        printf("deleted new object!\n");
        Py_XINCREF(NULL);
        return Py_None;
    }
    static PyObject* ntree_find_name(PyObject *self, PyObject *args)
    {
        printf("find name called");
        auto search_result = evil_pointer->find_name("test");
        if(search_result.compare("") == 0)
        {
            // return search_result.c_str();
            return Py_None;
        }
        Py_XINCREF(NULL);
        return Py_None;
    }
    static PyObject* ntree_add_node(PyObject *self, PyObject *args)
    {
        printf("add node called\n");
        Py_XINCREF(NULL);
        return Py_None;
    }

    static PyObject* ntree_add_data(PyObject *self, PyObject *args)
    {
        printf("add data called\n");
        Py_XINCREF(NULL);
        return Py_None;
    }
    // setup methods for passing
    static PyMethodDef ntreemethods[] =
    {
        {"__init__",    init_ntree, METH_VARARGS,       "initializer for ntree object"},
        {"__del__",     del_ntree, METH_VARARGS,        "destructor for ntree object"},
        {"add_node",    ntree_add_node, METH_VARARGS,   "add node to ntree"},
        {"add_data",    ntree_add_data, METH_VARARGS,   "add data to node in ntree"},
        {NULL, NULL, 0, NULL}        /* Sentinel */
    };

    static struct PyModuleDef ntreemodule = {
        /* name of module */
        /* module documentation, may be NULL */
        /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
        PyModuleDef_HEAD_INIT,
        "ntree", NULL, -1, ntreemethods
    };

    PyMODINIT_FUNC PyInit_ntree(void)
    {
        return PyModule_Create(&ntreemodule);
    }
} // namespace python_function


