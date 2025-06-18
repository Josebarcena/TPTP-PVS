# 🧠 TPTP to PVS Translator

This project implements an automatic translator for logical specifications written in [TPTP](http://www.tptp.org/) format (especially THF) into the language of the [PVS](https://pvs.csl.sri.com/) interactive verification system.

Its purpose is to serve as a bridge between automated theorem provers and formal specification environments, enabling the reuse of existing problems in contexts where traceability and expert control are essential.

---

## ⚙️ Features

- Lexical and syntactic analysis of the TPTP language using **Flex** and **Bison**.
- Semantic generation of valid PVS specifications using **Python**.
- Support for higher-order types (`$i`, `ttype`) and modular translation logic.
- **Parallel translation processing** via multithreading.
- Error tracing and logging system.
- Automatic header with timestamp in every translated file.

---

## 📦 Requirements

- Linux or WSL (Windows Subsystem for Linux)
- `flex` and `bison`
- `gcc` and `make`
- `python3` (version ≥ 3.10)
- PVS environment installed (recommended: version 7.1)

---

## 🚀 Usage Instructions

### Clone the repository and compile the frontend

```bash
git clone https://github.com/Josebarcena/TPTP-PVS.git
cd TPTP-PVS
make
```
Translate a single .p file
```bash
./translator tests/ejemplo1.p
```
This will generate an output file output/ejemplo1.pvs with the translated specification.

Concurrent processing (folder translation)
You can translate all .p files in a folder (e.g., tests/) using parallel execution with multiple threads:

```bash
python3 parser.py tests/ -h 20
```

The system will distribute the workload among available threads to process the files in parallel. Each result will be written into the output/ directory.

## 📁 Repository Structure
```bash
.
├── parser.l          # Lexical analyzer (Flex)
├── parser.y          # Syntax analyzer (Bison)
├── structs.{h,c}     # Intermediate data structures
├── parser.py         # Semantic backend and concurrent execution
├── output/           # Output directory for translated PVS files
├── tests/            # Sample TPTP input files
├── Makefile          # Automated build system
└── LICENSE           # Creative Commons BY-SA 4.0 license
```

## 📄 License
This project is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License (CC BY-SA 4.0).

You are free to reuse, modify, and distribute this work as long as you credit the original author and maintain the same license.

---

## 👨‍💻 Author
-José Bárcena

-Bachelor's Thesis – University of A Coruña  

-Contact: [josebarcena98@gmail.com](mailto:josebarcena98@gmail.com)

---

##🔗 Useful Links
[TPTP Problem Library](http://www.tptp.org/)

[PVS: Prototype Verification System](https://pvs.csl.sri.com/)
