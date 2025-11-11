# Cloud-Deployment-DSL-Complier

# ☁️ Cloud Deployment DSL Compiler

A **Domain-Specific Language (DSL) Compiler** built to simplify and automate **cloud deployment configuration** using **compiler design concepts** (Lex, Yacc, AST, Optimization, and Code Generation).

---

## 🧭 Project Overview

This project implements a **custom compiler** for a **Domain-Specific Language (DSL)** that defines cloud deployment configurations in a simple and human-readable format.

Instead of manually writing complex and error-prone **JSON** or **YAML** files for cloud platforms (like AWS, Azure, or GCP), users can write deployment specifications in a concise DSL like this:

```txt
DEPLOYMENT MyApp {
    PROVIDER aws;
    REGION us-east-1;

    SERVICE web {
        IMAGE "nginx:latest";
        CPU 2;
        MEM 1024;
        REPLICAS 2;

        ENV {
            PORT = "8080";
            MODE = "production";
        };
    };

    OPTIMIZE {
        COST 500;
        LATENCY 80;
    };
};
The compiler parses this file, constructs an Abstract Syntax Tree (AST), applies basic optimization rules, and generates a JSON deployment plan automatically.

🧩 Features
✅ Custom DSL syntax for defining deployments, services, constraints, and environment variables.

⚙️ Compiler architecture: includes a lexer, parser, AST builder, optimizer, and code generator.

🧠 Automatic optimization based on cost and latency constraints.

🧾 Outputs structured JSON plans ready for use in cloud automation tools.

💡 Easily extensible to add new keywords like STORAGE, NETWORK, or SECURITY.

🧱 Demonstrates key compiler design principles (Lexical Analysis, Parsing, AST, Optimization, and Code Generation).

🧠 Project Architecture
The project follows the standard compiler pipeline:

Stage	File	Description
Lexical Analysis	lexer.l	Tokenizes the input DSL file (using Flex)
Syntax Analysis	parser.y	Defines grammar rules and builds the parse tree (using Yacc/Bison)
Abstract Syntax Tree (AST)	ast.c, ast.h	Implements structures like Deployment, Service, and Constraint
Semantic Actions & Environment Handling	ast.c	Stores and manages environment variables for each service
Optimization	optimizer.c	Adjusts resource values or replicas based on constraints
Code Generation	codegen.c	Produces a JSON deployment plan as output
Main Driver	main.c	Controls file parsing, optimization, and output generation

🧰 Technologies Used
Component	Tool / Language
Programming Language	C
Lexical Analyzer	Flex
Parser Generator	Yacc / Bison
Build Tool	Makefile
Output Format	JSON
Operating System	Linux / WSL

⚙️ Installation and Usage
🪄 Prerequisites
Make sure you have the following installed:

GCC Compiler

Flex (Fast Lexical Analyzer)

Bison/Yacc (Parser Generator)

Make

To install on Ubuntu:

bash
Copy code
sudo apt update
sudo apt install flex bison build-essential
🔧 Building the Project
Clone this repository and build it using make:

bash
Copy code
git clone https://github.com/<your-username>/Cloud-Deployment-DSL-Compiler.git
cd Cloud-Deployment-DSL-Compiler
make
This generates an executable file named:

nginx
Copy code
cloudopt
▶️ Running the Compiler
To compile and execute a DSL file:

bash
Copy code
./cloudopt sample_env.ddl > plan.json
🧾 Sample Input (sample_env.ddl)
txt
Copy code
DEPLOYMENT MyApp {
    PROVIDER aws;
    REGION us-east-1;

    SERVICE web {
        IMAGE "nginx:latest";
        CPU 2;
        MEM 1024;
        REPLICAS 2;

        ENV {
            PORT = "8080";
            MODE = "production";
        };
    };

    OPTIMIZE {
        COST 500;
        LATENCY 80;
    };
};
🧠 Sample Output (plan.json)
json
Copy code
{
  "deployment": "MyApp",
  "provider": "aws",
  "region": "us-east-1",
  "services": [
    {
      "name": "web",
      "image": "nginx:latest",
      "cpu": 2,
      "mem": 1024,
      "replicas": 2,
      "env": [
        {"PORT": "8080"},
        {"MODE": "production"}
      ]
    }
  ],
  "constraints": [
    {"cost": 500},
    {"latency": 80}
  ]
}
🔍 File Descriptions
File	Description
lexer.l	Defines all tokens (keywords like DEPLOYMENT, SERVICE, COST, etc.) and handles string, number, and identifier recognition.
parser.y	Implements grammar rules for the DSL, defines semantic actions that build the AST, and connects all components.
ast.h	Header file defining all major data structures: Deployment, Service, Constraint, and EnvVar.
ast.c	Implements creation, linking, and management of AST nodes. Also provides printing and cleanup functions.
optimizer.c	Applies simple optimization rules to services (e.g., scaling replicas or balancing cost/latency).
codegen.c	Traverses the AST and generates the final JSON deployment plan.
main.c	Entry point that manages file input, invokes parser, runs optimization, and triggers code generation.
Makefile	Automates the build process for all components using Flex, Yacc, and GCC.

🧮 Example Workflow
Write your deployment configuration in .ddl file.

Run the compiler using:

bash
Copy code
./cloudopt my_deployment.ddl > plan.json
View the generated JSON file:

bash
Copy code
cat plan.json
Integrate that JSON with cloud provisioning scripts.

💡 Motivation
Cloud deployment configurations are often long, complex, and error-prone when written manually in YAML or JSON.
This project provides a simplified language and compiler-based automation approach to make configuration:

More readable 🧾

Easier to debug 🧩

Less error-prone ⚡

More scalable 🚀

🧠 Objectives
Design and implement a DSL for cloud deployment.

Build a complete compiler pipeline using Lex and Yacc.

Represent deployment configurations using an Abstract Syntax Tree (AST).

Implement optimization rules for cost and latency.

Generate structured JSON output for automation tools.

🚧 Challenges Faced
Designing the grammar to handle nested structures like SERVICE and ENV.

Managing linked lists for environment variables and constraints.

Debugging parser conflicts and syntax errors in Yacc.

Coordinating between multiple C files for modular compilation.
🧠 1. Introduction

The Cloud Deployment DSL Compiler is a mini compiler built using Lex and Yacc (Bison) that parses and processes a Domain Specific Language (DSL) for cloud deployment descriptions.

This DSL allows developers to define deployment configurations — such as provider, region, services, and optimization constraints — in a simple readable format (like AWS CloudFormation or Terraform lite).

The compiler then:

Parses the input DSL file.

Builds an Abstract Syntax Tree (AST).

Performs simple optimization on resources.

Generates a JSON-like deployment plan as output.

🎯 2. Objectives

To design and implement a Domain-Specific Language (DSL) for describing cloud deployments.

To learn and demonstrate compiler construction techniques using Lex and Yacc.

To convert structured DSL input into machine-readable JSON output.

To practice building lexical analyzers, parsers, and ASTs.

🚀 3. Motivation

In real-world cloud platforms like AWS, Azure, or GCP, deployment scripts are verbose and complex.
This project introduces a simplified syntax for describing deployments, enabling students and developers to understand compiler design principles through a realistic use case.

⚙️ 4. Project Structure
📁 Cloud_Deployment_DSL_Compiler/
│
├── lexer.l             # Lexical Analyzer - Tokenizes DSL keywords
├── parser.y            # Yacc Grammar - Defines syntax & builds AST
├── ast.h               # AST Data Structures (Deployment, Service, Env)
├── ast.c               # AST Implementation (create, modify, print)
├── optimizer.c         # Performs optimization on resources
├── codegen.c           # Generates JSON-like output
├── main.c              # Entry point - coordinates compilation process
├── Makefile            # Automates compilation
└── sample_env.ddl      # Sample input DSL program

🧩 5. Implementation Details
🔹 Lexical Analysis (lexer.l)

Recognizes tokens like DEPLOYMENT, SERVICE, CPU, REGION, etc.

Handles strings, numbers, and special characters like {, }, ;.

Passes tokens to the parser.

🔹 Parsing (parser.y)

Defines grammar rules for the DSL.

Builds the Abstract Syntax Tree (AST) using helper functions.

Handles constructs such as:

DEPLOYMENT MyApp {
    PROVIDER aws;
    REGION us-east-1;
    SERVICE web {
        IMAGE "nginx:latest";
        CPU 2;
        MEM 1024;
        REPLICAS 2;
    }
    OPTIMIZE {
        COST 500;
        LATENCY 80;
    };
}

🔹 Abstract Syntax Tree (ast.c / ast.h)

Defines structured nodes for:

Deployment

Service

Constraints

Environment variables

Includes functions to build and print these objects neatly.

🔹 Optimizer (optimizer.c)

Adjusts resource allocations (like replicas or memory) to optimize cost and latency constraints.

🔹 Code Generator (codegen.c)

Converts the AST into structured JSON output:

{
  "deployment": "MyApp",
  "provider": "aws",
  "region": "us-east-1",
  "services": [
    {"name": "web", "cpu": 2, "mem": 1024, "replicas": 2}
  ],
  "constraints": [
    {"cost": 500},
    {"latency": 80}
  ]
}

🔹 Main Driver (main.c)

Integrates all modules.

Reads input .ddl file, runs lexer and parser, calls optimizer and codegen.

🧮 6. How to Build & Run
make clean
make
./cloudopt sample_env.ddl > plan.json
cat plan.json


✅ Output:
A deployment plan in JSON format.


🌟 Acknowledgments
Indian Institute of Information Technology, Design and Manufacturing, Kancheepuram

Course: Compiler Design

Instructor: Prof. Jagadish

Academic Year: 2025

“This project demonstrates how compiler design principles can be applied to solve real-world automation problems in cloud computing.”
