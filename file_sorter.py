#directory organizer
import os
import parser
import ntree

def check_string(string):
    try:
        str(string)
        return(True)
    except ValueError:
        return(False)

class sorting_hat:
    def __init__(self):
        self.cache_file_name = '.cache.dat'
        self.data_tree = ntree.__init__()
        self.fp = None

        if os.stat(self.cache_file_name).st_size > 0:
            for line in self.fp.change_file(self.cache_file_name):
                temp = self.fp.read_line().split(' ')
                # self.file_map.update(temp[0], temp[1])
        else:
            self.scan_directory()
        print('Initialized\n')
    def __del__(self):
        self.data_tree.__del__()

    def scan_directory(self):
        cur_dir = '' 
        while True:
            cur_dir = input('Enter directory to start scan')
            if check_string(cur_dir) and os.path.isdir(cur_dir):
                break
            else:
                print('Invalid!\n')
                continue
        os.chdir(cur_dir)
        root = cur_dir

        #begin building directory tree
        while True:
            #list sub-directorys and files at current location
            temp_list = os.listdir(cur_dir)
            for item in temp_list:
                #somefunction that tells me waht the damn filetype is
                if os.path.isdir(cur_dir + item) is not True:
                    #add data to current node
                    self.data_tree.add_data(item, cur_dir)
                else:
                    #add subdirectory to current node
                    self.data_tree.add_node(item, cur_dir)
                    temp_list.append(cur_dir + item)
            if len(temp_list) > 0:
                # update current dirrectory with subdirectory of current location
                cur_dir = temp_list.pop()
            else:
                # exit tree building when list is empty, representing no more subdirectories to scan
                break

