import os,sys


ignore = ".git build".split()

def check_path(given):
    for bad in ignore: 
        print(bad,given)
        print(type(bad),type(given))
        if bad in given:
            print(" caught ")
            return False
        print(" passed ")
    return True

edited_files = [os.path.join(place[0],file) for place in os.walk(".") for file in place[2] if check_path(place[0]) ]

message = "YEEEEEESSS GOT TESSELATION"

command = "git add {}; git commit -m \"{}\"".format(" ".join(edited_files),message)

os.system(command)


