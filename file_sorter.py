#directory organizer
import os
import parser

def check_string(string):
    try:
        str(string)
        return(True)
    except ValueError:
        return(False)

class n_tree:
    def __init__(self):
        self.tree = None

class sha_hashmap:
    def __init__(self):
        self.cache_file_name = '.cache.dat'
        self.file_map = dict()
        self.fp = None
        if os.stat(self.cache_file_name).st_size > 0:
            for line in fp.change_file(self.cache_file_name):
                temp = fp.read_line().split(' ')
                self.file_map.update(temp[0], temp[1])
        else:
            self.scan_directory()
        print('Initialized\n')

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

        #begin building directory hash


    def hash_file(self, file):
        pass

