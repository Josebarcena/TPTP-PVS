# TPTP to PVS Translator

Este proyecto implementa un sistema de traducción automática de fórmulas lógicas escritas en formato [TPTP (THF)](http://www.tptp.org/) al lenguaje formal utilizado por el entorno de verificación asistida [PVS](https://pvs.csl.sri.com/).

Su objetivo es facilitar la reutilización de especificaciones existentes en herramientas automáticas dentro de entornos más expresivos e interactivos.

---

## 🚀 Instalación y ejecución

### Requisitos

- Linux (se recomienda entorno WSL si se usa desde Windows)
- `flex` y `bison`
- `gcc` y `make`
- `python3` (≥ 3.10)
- Entorno PVS (v7.1 o compatible)

### Instrucciones de uso

```bash
# Clonar el repositorio
git clone https://github.com/Josebarcena/TPTP-PVS.git
cd TPTP-PVS

# Compilar el frontend
make

# Ejecutar el traductor sobre un archivo .p
./translator tests/ejemplo1.p
