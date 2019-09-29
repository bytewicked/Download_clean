import os
import shutil

Audio_EXT = ['.aif', '.cda', '.mid', '.midi', '.mp3', '.mpa', '.ogg',
             '.wav', '.mwa', '.wpl']

Documents_EXT = ['.doc', '.docx', '.odt', '.pdf', '.rtf', '.tex', '.txt',
                 '.wks', '.wps', '.wpd', '.ods', '.xlr', '.xls', '.xlsx', '.key', '.odp',
                 '.pps', '.ppt', '.pptx', '.csv', '.dat', '.db', '.dbf', '.log', '.mdb',
                 '.sav', '.sql', '.tar', '.xml', '.html']

Picture_EXT = ['.ai', '.bmp', '.gif', '.ico', '.jpeg', '.jpg', '.png',
               '.ps', '.psd', '.svg', '.tif', '.tiff']

Video_EXT = ['.3g2', '.3gp', '.avi', '.flv', '.h264', '.m4v', '.mkv',
             '.mov', '.mp4', '.mpg', '.mpeg', '.rm', '.swf', '.vob', '.wmv']

Program_EXT = ['.apk', '.bat', '.bin', '.cgi', '.pl', '.com', '.exe',
               '.gadget', '.jar', '.py', '.wsf', '.iso','.zip']

print("DFC")
print("current Directory:  {}".format(os.getcwd()))
print()

files = os.listdir('.')

DIRS = ['MUSIC', 'FILES', 'FOLDERS','IMAGES', 'VIDEOS', 'PROGRAMS', 'OTHER']

exceptions = ['./MUSIC', './FILES', './IMAGES', './VIDEOS', './PROGRAMS', './OTHER', 'DFC.py']

for d in DIRS:
    if not os.path.exists(d):
        os.makedirs(d)

print("Directories Created Successfully")

for f in files:
    name, exstention = os.path.splitext(f)

    if exstention in Audio_EXT:
        shutil.move(f, './MUSIC/{}'.format(f))
    
    elif exstention in Documents_EXT:
        shutil.move(f, './FILES/{}'.format(f))

    elif exstention in Picture_EXT:
        shutil.move(f, './IMAGES/{}'.format(f))

    elif exstention in Video_EXT:
        shutil.move(f, './VIDEOS/{}'.format(f))

    elif exstention in Program_EXT:
        shutil.move(f, './PROGRAMS/{}'.format(f))

    elif:
        if os.path.isdir(name):
            if name not in DIRS:
                shutil.move(f, './FOLDERS/{}'.format(f))

    else:
        if f != 'DFC.py':
            shutil.move(f, './OTHER/{}'.format(f))

print('Sorting complete')
