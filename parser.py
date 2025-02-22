import linecache as lc
import fileinput
import os
"""
Parse_File creates functionality for opening and parsing file within a with statment block
automatically closing file at the end of the block.
Inclues: TODO
"""
class Parse_File:
    #constructor for class
    #opens sets filename to private class isntance variable
    #and initiates the file pointer to None for future assignment
    def __init__(self, fname = None):
        if fname:
            self.fname = fname # set the file name
        else:
            self.fname = None
        self.fp = None
    #with enter statement
    #sets up functionality to open file in with statement block
    #and close file at end of block
    def __enter__(self):
        self.fp = open(self.fname, 'r+') # open file and assign to fp
        return self
    #destructor for with statement, closes file at end of with block
    def __exit__(self, exc_type, exc_value, traceback):
        (self.fp).close()
    #change accessed filename
    def change_file(self, fname):
        self.fname = fname
        
    # returns the line number of the first instance of var found
    # TODO : start search from specific location in file
    def find_line_number(self, var, nextline = None):
        try:
            endloc = (self.fp).seek(0,2)
            endloc = (self.fp).tell()
            (self.fp).seek(0,0)
            prev_len = 0
            #this loop reads lines and updates the file pointer
            #location each iteration until the desired text
            #is reached. Overshoots one line, so subtract off
            #the length of the final line reached in this loop
            #after loop
            while True:
                prev = (self.fp).readline()
                if var in prev:
                    prev_len = len(prev)
                    break
                elif (self.fp).tell() == endloc:
                    print('EOF reached!!\n\n')
                    return(-1)
            #backtrack one line by length of desired text -> go up one line
            if not nextline:
                ln_num = (self.fp).tell() - prev_len
            else:
                ln_num = (self.fp).tell()
            return(ln_num)
        except IOError as whatis:
            print('File error!\n\n\n')
            print(whatis)
            return(-2)

    def file_readline(self, ln = None, searchterm = None, nextline = None):
        try:
            #(self.fp).seek(0)
            if ln:
                (self.fp).seek(ln)
            elif searchterm:
                ln = self.find_line_number(searchterm, nextline)
                (self.fp).seek(ln)
            outstring = (self.fp).readline()
            return(outstring)
        except IOError:
            print('File error!\n\n\n')
            return(-1)

    def file_seek(self, loc):
        try:
            (self.fp).seek(loc)
            return
        except IOError:
            print('File error!\n\n\n')
            return(-1)

    #set the variable name var in file to value val
    def set_config_var(self, var, val):
        try:
    #seek to the file location passed and overwrite line with {var} {val}\n
            (self.fp).seek(self.find_line_number(var))
            (self.fp).write('{:s} {:s}'.format(var, val))
            pass
        except IOError:
            print('File error!\n\n\n')
            return(-1)
        return

    def write_to_file(self, val, line_num=None):
        try:
    #if passed a line number, function will seek to the passed location
            if line_num is not None:
                (self.fp).seek(line_num)
    #else, just write to file starting from top (default)
            (self.fp).write(val)
        except IOError:
            print('File error!\n\n\n')
            return(-1)

    def delete_contents(self):
        (self.fp).seek(0) #move to top of file
        (self.fp).truncate() #truncate all data from top of file
        return


def list_keyword_and_edit(f_name):
    #streach goal: make tk gui to modify
    try:
        fp = open(f_name, 'r+') # open file for read + write
        editlist = [] #create blank array for storage of variables
    #start building array enumerated with enumerated variable number and file pointer location
        for i, ln in enumerate(fp):
            if (ln[0] == "#") or (ln[0] == "\n"):
            #if line starts with # or is blank, skip
                continue
            else:
                #add enumerated variable number and
                #file pointer location when non empty line
                #is reached
                editlist.append((i,ln))
                pass
        #display all variables to edit
        for i, var in enumerate(editlist):
    #display variable number next to actual variable entry in file
            print('VN {:d}: {:s}'.format(i+1,var[1]))
    #move fp to begining of file to begin editing and reset counters
        fp.seek(0)
        user_in = ''
        line_num = 0
        print('Enter q to quit editing here or at variable number prompt\n\n')
        while True:#start edit loop, exit on user input == 'q'
            user_in = input('Enter variable number to edit: ')
            if user_in == 'q':
                break
            line_num = int(user_in)
            if line_num > len(editlist):
                print('Out of range of list! Enter proper index.\n')
                continue
            user_in = input(editlist[line_num - 1][1] + '\nReplace with?:\n')
            #find and replace line with user text
            while not(editlist[line_num - 1][1] == fp.readline()):
                #this loop reads lines and updates the file pointer
                #location each iteration until the desired text
                #is reached (overshoots one line)
                pass
            #backtrack one line by length of desired text -> go up one line
            fp.seek(fp.tell() - len(editlist[line_num - 1][1]))
            fp.write(user_in)
            pass
        pass
    finally:
        fp.close()
    print("end of editing\n\n")

#concatenates fname2 into fname1 -> fname1
def concatenate_files(fname1, fname2, outname):
    file_list = [fname1, fname2]
    print('Writing config file...')
    with open(outname, 'r+') as file:
        if os.path.isfile(outname):
            file.seek(0)
            file.truncate()
            pass
        input_lines = fileinput.input(file_list)
        file.writelines(input_lines)
    print('Done!')
    return
