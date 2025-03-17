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
    typed = line[line.find("("):line.find(")")+ 1]
    pos = line.find(") :") + 5
    pos1 = line.find("=")
    
    if(pos < pos1 or pos1 == -1):  #DEFINITION WITH : FORM
        aux = line[pos:pos1] #TAKE THE TYPE OF xxx
        var = aux[:aux.find(" ")] # UNTIL NEXT SPACE

    else:
        var = line[:pos1] #DEFINITION WITH = FORM
    if var in functions:
        aux = line[pos:pos1 - 1] +" : " + functions[var] + " " + line[pos1:]
        aux=re.sub(r'\(.*?\)',typed, aux,count = 1)
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
    varType = var[var.rfind("->")+2:]
    functions[varName] = varType

    var = re.sub(r":\s*(.*)", r": [\1]", var)
    aux = var[var.find(":") + 2:]
    pos = aux.find("->")

    while (pos != -1):
        pos1 = aux.find("->", pos+3)
        if pos1 == -1:
            break
        aux = "[" + aux[:pos] + aux[pos:pos1 - 1] + "]" + aux[pos1:]
        pos = aux.find("->", pos+3)

    aux = var[:var.find(":") + 2] + aux + "\n"
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
            aux = re.sub(r'\s->\s', ' > ', line)
            filtered_lines.append(aux)


with open(pvsFile, "w") as file:
    file.writelines(comments_lines)
    file.write("\n")

    file.writelines(include_lines)
    file.write("\n")

    file.writelines(filtered_lines)
