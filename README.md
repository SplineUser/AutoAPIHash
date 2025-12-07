# AutoAPIHash

**Automatic Evasive API Hashing for PE Binaries**

A component-based tool designed to minimize VirusTotal detection scores through intelligent API hashing permutations. AutoAPIHash automatically analyzes C/C++ programs, applies various API hashing techniques, and iteratively finds the optimal combination to reduce static analysis signatures.

## 🎯 Overview

AutoAPIHash is a sub-component of an APT simulation toolkit that focuses on evading static detection by removing API imports from the PE import table and replacing them with runtime-resolved hashed API calls. The tool uses an iterative optimization approach to test different API hashing combinations and automatically selects the variant with the lowest VirusTotal detection score.

## ✨ Features

- **JSON-Driven Configuration**: Define target APIs and hashing strategies through flexible JSON configuration files
- **Automatic API Detection**: Intelligently parses C/C++ source code to identify and extract API calls
- **Dynamic Stub Generation**: Automatically generates API hashing stubs with proper function signatures
- **Seamless Integration**: Integrates generated stubs into your source code via header file injection
- **Automated Compilation**: Compiles variants with configurable compiler settings
- **VirusTotal Integration**: Automatically submits compiled binaries and retrieves detection scores
- **Score Optimization**: Uses optimization algorithms to find the API hashing combination that minimizes VT detection
- **Component-Based Architecture**: Modular design following industry-standard patterns for maintainability

## 🏗️ Architecture

The tool follows a component-based design with clear separation of concerns:

```
┌─────────────────────┐
│   JSON Component    │  ← Configuration Management
├─────────────────────┤
│  Source Component   │  ← Source Code Parsing & API Renaming
├─────────────────────┤
│   Stub Component    │  ← API Hash Stub Generation
├─────────────────────┤
│ Compiler Component  │  ← Binary Compilation
├─────────────────────┤
│ VirusTotal Component│  ← VT API Integration
├─────────────────────┤
│Optimization Component│ ← Score Minimization Algorithm
└─────────────────────┘
```

## 🚀 Installation

### Prerequisites

- C++ compiler (GCC/MinGW/MSVC)
- VirusTotal API key
- MSVS for building

### Building from Source

```bash
git clone https://github.com/SplineUser/AutoAPIHash.git
cd AutoAPIHash
build via MSVS
```

### Configuration

Create a `config.json` file with your VirusTotal API key:

```json
{
  "vt_api_key": "your_api_key_here",
  "compiler_path": "/path/to/compiler",
  "optimization_iterations": 50
}
```

## 📖 Usage

### Basic Usage

```bash
   ./autoapihash.exe -i myfile.cpp -j api_list.json -s headerfile.h
```

### Advanced Options

```bash
./autoapi_hash \
   -i <input>     Specify input C/CPP File
   -j             Set path to JSON API File
   -s             Set path to source header file
   -h, --help     Show this help menu
```

### Configuration File Format

Define your target APIs in a JSON configuration file:

```json
[{
    "name": "VirtualAlloc",
    "rename": "myVirtualAlloc",
    "ReturnType": "LPVOID",
    "Parameters": ["LPVOID", "SIZE_T", "DWORD", "DWORD"],
    "ModuleName":"Kernel32.dll",
    "Hash": 53423
},

{
    "name": "VirtualFree",
    "rename": "myVirtualFree",
    "ReturnType": "BOOL",
    "Parameters": ["LPVOID", "SIZE_T", "DWORD"],
    "ModuleName":"Kernel32.dll",
    "Hash": 2344234
}]
```

## 🔧 API Hashing Algorithms Supported

- **DJB2**: Fast, simple hash function (Implemented)
- **FNV-1a**: Fowler-Noll-Vo hash function
- **CRC32**: Cyclic redundancy check
- **SDBM**: Hash function from SDBM database
- **Custom**: Define your own hashing algorithm

## 📊 Workflow

1. **Parse Configuration**: Load JSON file containing target APIs and strategies
2. **Analyze Source**: Scan C/C++ source code for API usage
3. **Generate Variants**: Create permutations of API hashing combinations
4. **Compile Binaries**: Build each variant with the integrated stubs
5. **Submit to VT**: Upload binaries to VirusTotal for analysis
6. **Collect Scores**: Retrieve and store detection results
7. **Optimize**: Use optimization algorithms to find minimal detection score
8. **Output Result**: Return the best-performing variant

## ⚙️ Components

### JSONComponent
Handles configuration file loading, validation, and API list management.

### SourceComponent
Parses C/C++ source files, identifies API calls, and performs automated renaming.

### StubComponent
Generates API hashing stubs with proper function signatures and integrates them via header files.

### CompilerComponent
Manages compilation of source variants with configurable compiler settings.

### VTComponent
Handles VirusTotal API communication, file submission, and score retrieval.

### OptimizationComponent
Implements optimization algorithms (genetic, simulated annealing, hill climbing) to minimize VT scores.

## 🛡️ Limitations & Considerations

- **Rate Limiting**: VirusTotal API has rate limits; tool includes automatic throttling
- **Network Dependency**: Requires stable internet connection for VT communication
- **Compiler Dependency**: Requires external C/C++ compiler installation
- **Detection Variance**: VT scores may vary over time as signatures are updated
- **Research Purpose**: This tool is intended for security research and red team exercises only

## 🧪 Testing

The project follows Test-Driven Development (TDD) principles with comprehensive test coverage:


Test suites cover:
- JSON parsing and validation
- Source code API detection
- Stub generation accuracy
- Compilation success rates
- VT API integration

## 🤝 Contributing

Contributions are welcome! Please follow these guidelines:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Follow XP principles: simplicity, feedback, and courage
4. Write tests for new functionality (TDD approach)
5. Ensure all tests pass
6. Submit a pull request

## 📝 Development Methodology

This project follows a hybrid software engineering approach combining:
- **Extreme Programming (XP)**: Core values of simplicity, feedback, and continuous integration
- **Test-Driven Development**: Write tests before implementation
- **Component-Based Design**: Modular architecture for maintainability
- **Iterative Development**: Continuous refinement based on feedback

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details.

## ⚠️ Disclaimer

This tool is developed for **educational and authorized security research purposes only**. Users are responsible for ensuring they have proper authorization before using this tool. The authors assume no liability for misuse or damage caused by this software.

## 🔗 Links

- [Documentation](https://github.com/SplineUser/AutoAPIHash/wiki) (Not Implemented!)
- [Issue Tracker](https://github.com/SplineUser/AutoAPIHash/issues) (Not Implemented!)
- [Changelog](CHANGELOG.md) (Not Implemented!)

## 👤 Author

**SplineUser**

- GitHub: [@SplineUser](https://github.com/SplineUser)



---

**Note**: Always use this tool responsibly and ethically. Ensure you have proper authorization before conducting any security testing.
