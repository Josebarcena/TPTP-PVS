import sys
import re
import textwrap

functions = {}
filtered_lines = []
include_lines = []
comments_lines = []
inside_comment_block = False

pvsFile = re.sub(r'\.([^\s]+)', '', sys.argv[1]) + ".pvs" #PVS OUTPUT FILE
def DEF_PARSER(line : str) -> None: #HERE WE PARSER FUNCTION DEFINITION
    types = re.search(r'\(([^()]+)\)', line).group(1)
    aux = line[line.find(":  (") + 4:line.rfind(")")]
    aux = aux[:aux.find("(")] + "(" + types + aux[aux.find(")"):]
    aux = re.sub(r'IFF','=', aux, count = 1)
    varName = aux[:aux.find(" ")]
    if varName in functions:
        aux = aux[:aux.find(")")+1] + " : " + functions[varName] + aux[aux.find(")")+1:] + "\n"
    else:
        aux = aux + "\n"

    filtered_lines.append(aux)    

def INCLUDE_PARSER(line : str) -> None: #JUST PARSER INCLUDE INTO PVS FORMAT
    aux =  re.sub(r'\.([^\s]+)', '',line).replace("'", "") + " \n"
    aux = aux[:aux.find(" ")+1] + "\"" + aux[aux.find(" ")+1:].strip() + ".pvs\"\n"
    include_lines.append(aux)

def COMMENT_PARSER(line: str) -> None:
    aux = line
    global inside_comment_block

    if "/*" in aux:
        inside_comment_block = True
        aux =  aux.replace("/*", "")
    if "*/" in aux:
        inside_comment_block = False
        aux =  aux.replace("*/", "")

    if aux.startswith("%"):
        comments_lines.append(aux)
    else:
        aux = "%" + aux
        comments_lines.append(aux)

def DT_PARSER(line : str) -> None:
    var = re.findall(r'\[(.*?)\]', line)[0]
    varName = var[:var.find(":")]
    varOut = var[var.rfind("->")+2:]
    functions[varName] = varOut
    if "->" not in line:
        aux = var[:var.find(":")] + " : TYPE = " + var[var.find(":")+1:] + "\n"
        filtered_lines.append(aux + "\n")



with open(sys.argv[1], "r") as file:
    for line in file:


        if ": THEORY" in line or "\tEND" in line:
            aux = re.sub(r'\.([^\s]+)', '', line)
            aux = re.sub(r'[\^\*\+]', '_', aux)
            filtered_lines.append(aux)
            
        elif line.startswith("%") or "/*" in line:
            COMMENT_PARSER(line)

        elif inside_comment_block:
            COMMENT_PARSER(line)

        elif(line.startswith("!DT¡")):
            DT_PARSER(line[4:])

        elif(line.startswith("!DEF¡")):
            DEF_PARSER(line[5:])

        elif line.startswith("include '"):
            INCLUDE_PARSER(line)

        elif line.isspace():
            line.strip()
            filtered_lines.append("\n")

        else:
            filtered_lines.append(line)



with open(pvsFile, "w") as file:
    file.writelines(comments_lines)
    file.write("\n")

    file.writelines(include_lines)
    file.write("\n")

    file.writelines(filtered_lines)
