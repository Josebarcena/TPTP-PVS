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
    pos = line.find(":")
    pos1 = line.find("=")
    if(pos < pos1 or pos1 == -1):  #DEFINITION WITH : FORM
        aux = line[pos +3:] #TAKE THE TYPE OF xxx
        var = aux[:aux.find(" ")] # UNTIL NEXT SPACE
    else:
        var = line[:pos1] #DEFINITION WITH = FORM

    if var in functions:
        auxType = functions[var]
        auxType = auxType[auxType.rfind("->") + 3:]
        aux1 = aux[:aux.find("=")]
        aux1 = aux1 + ": " + auxType.strip()
        aux = aux1 + " " + aux[aux.find("="):]
        filtered_lines.append(aux)

def INCLUDE_PARSER(line : str) -> None: #JUST PARSER INCLUDE INTO PVS FORMAT
    aux =  re.sub(r'\.([^\s]+)', '',line).replace("'", "") + " \n"
    aux = aux[:aux.find(" ")+1] + "\"" + aux[aux.find(" ")+1:].strip() + ".pvs\"\n"
    include_lines.append(aux)

def VARS_PARSER(line : str) -> None: # WE CHECK IF VAR IS A FUNCTION  
    if "->" in line:
        pos = line.find(":")
        defType = line[pos+1:]
        if "TYPE" in line:
            defType = defType[5:]
        else:
            defType = defType[5:]
            vars = [var.strip() for var in re.split(",", line[:pos])] 
            for var in vars:
                functions[var] = defType
    else: # IF VAR IS NOT A FUNCTION, WE ADD IT
        filtered_lines.append(line)

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

    if var in functions:
        aux = line[:line.find("[")+1]
        aux = aux + functions[var].strip()
        pos = aux.rfind("->", 0, aux.rfind("->"))
        if pos != -1:
            aux = aux[:pos+2] + "[" + aux[pos+2:] + "]"
        aux = aux + line[line.find("]"):]
        filtered_lines.append(aux)



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

        elif line.startswith("!VARS!"):
            VARS_PARSER(line[7:])

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
            aux = re.sub(r'\s=\s', ' IFF ', line)
            filtered_lines.append(aux)


with open(pvsFile, "w") as file:
    file.writelines(comments_lines)
    file.write("\n")

    file.writelines(include_lines)
    file.write("\n")

    file.writelines(filtered_lines)
