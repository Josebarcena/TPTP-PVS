# 🧠 TPTP to PVS Translator

Este proyecto implementa un traductor automático de especificaciones lógicas escritas en formato [TPTP](http://www.tptp.org/) (especialmente THF) hacia el lenguaje del entorno de verificación asistida [PVS](https://pvs.csl.sri.com/).

Su propósito es servir de puente entre herramientas de demostración automática y sistemas formales asistidos, permitiendo reutilizar problemas existentes en contextos donde se requiere trazabilidad y control experto.

---

## ⚙️ Características

- Análisis léxico y sintáctico del lenguaje TPTP mediante **Flex** y **Bison**.
- Generación semántica de especificaciones válidas en PVS usando **Python**.
- Soporte para tipos de orden superior (`$i`, `ttype`) y traducción modular.
- **Paralelización del proceso de traducción** mediante múltiples hilos.
- Sistema de trazabilidad y log de errores.
- Cabecera automática con marca temporal en los archivos generados.

---

## 📦 Requisitos

- Linux o WSL (Windows Subsystem for Linux)
- `flex` y `bison`
- `gcc` y `make`
- `python3` (versión ≥ 3.10)
- Entorno PVS instalado (recomendado: versión 7.1)

---

## 🚀 Instrucciones de uso

### Clonar el repositorio y compilar el frontend

```bash
git clone https://github.com/Josebarcena/TPTP-PVS.git
cd TPTP-PVS
make
```
Ejecutar el traductor sobre un archivo individual
```
./translator tests/ejemplo1.p

```
Esto generará un archivo output/ejemplo1.pvs con la traducción resultante.

Procesamiento concurrente (carpetas)
Puedes traducir todos los archivos .p de una carpeta (por ejemplo tests/) utilizando ejecución en paralelo con múltiples hilos:

```bash
python3 parser.py tests/ -h 20
```

El sistema dividirá la carga entre los hilos disponibles para procesar los archivos en paralelo. Se generará una salida para cada archivo en la carpeta output/.

📁 Estructura del repositorio

.
├── parser.l          # Análisis léxico con Flex
├── parser.y          # Análisis sintáctico con Bison
├── structs.{h,c}     # Definiciones de estructuras intermedias
├── parser.py         # Backend semántico y sistema concurrente
├── output/           # Carpeta de salida para traducciones PVS
├── tests/            # Carpeta con archivos TPTP de prueba
├── Makefile          # Compilación automática del sistema
└── LICENSE           # Licencia Creative Commons BY-SA 4.0

📄 Licencia
Este proyecto está publicado bajo licencia Creative Commons Atribución-CompartirIgual 4.0 Internacional (CC BY-SA 4.0).
Puedes reutilizar, modificar o distribuir este trabajo siempre que se cite al autor original y se mantenga la misma licencia.

👨‍💻 Autor
José Bárcena
Trabajo de Fin de Grado – Universidad de A Coruña
Contacto: [josebarcena98@gmail.com]

🔗 Enlaces útiles
TPTP Problem Library
PVS: Prototype Verification System
