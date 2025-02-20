import sys
import re
import textwrap

functions = {}
filtered_lines = []
include_lines = []
comments_lines = []
pvsFile = re.sub(r'\.([^\s]+)', '', sys.argv[1]) + ".pvs"

with open(sys.argv[1], "r") as file:
    for line in file:
        if ": THEORY" in line or "\tEND" in line:
            aux = re.sub(r'\.([^\s]+)', '', line)
            filtered_lines.append(aux)

        elif line.startswith("%"):
            comments_lines.append(line)

        elif "->" in line:
            pos = line.find(":")
            defType = line[pos+1:]
            if "TYPE" in line:
                defType = defType[5:]
            else:
                defType = defType[defType.rfind("->")+3:]
            vars = [var.strip() for var in re.split(",", line[:pos])] 
            for var in vars:
                functions[var] = defType

        elif(line.startswith("DT")):
            var = re.search(r'\[(.*?)\]', line).group(1)
            if var in functions:
                aux = line[3:line.find("[")+1] + functions[var].strip() + line[line.find("]"):]
                filtered_lines.append(aux)

        elif(line.startswith("DEF")):
            aux = line[line.find(":")+3:]
            var = aux[:aux.find(" ")]
            if var in functions:
                aux = aux[:aux.find("=")] + ": " + functions[var].strip()+ " " + aux[aux.find("="):]
                print(aux)
                filtered_lines.append(aux)

        elif line.startswith("include '"):
            aux =  re.sub(r'\.([^\s]+)', '',line).replace("'", "") + " \n"
            aux = aux[:aux.find(" ")+1] + "\"" + aux[aux.find(" ")+1:].strip() + ".pvs\"\n"
            include_lines.append(aux)

        else:
            aux = re.sub(r'\s=\s', ' IFF ', line)
            filtered_lines.append(aux)

with open(pvsFile, "w") as file:
    file.writelines(comments_lines)
    file.write("\n")
    file.writelines(include_lines)
    file.write("\n")
    file.writelines(filtered_lines)
