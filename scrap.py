import os,sys

edited_files =[ele for ele in os.listdir(".") if not os.path.isdir(ele)]

message = "need to check opengl version, tesselation problems"

command = "git add {}; git commit -m \"{}\"".format(" ".join(edited_files),message)

os.system(command)


