import os,sys,re,jinja2

loader = jinja2.FileSystemLoader(searchpath="{}".format(os.getcwd()))
fname = "vanilla_exec_lib"## the simplest form of inheritance that this can take


#the environment is crucial for passing the data to the template from the loader

env = jinja2.Environment(loader= loader)

template = env.get_template(fname)

## now do the regular expression looking through the present directory for the cpp files

cpp_files = [ele for ele in os.listdir() if ".cpp" in ele]
prefixes = [ele.split(".")[0] for ele in cpp_files]

print(template.render({"cpp_list":prefixes}))

