# Lexical Analyzer ✨

This repository contains a simple lexical analyzer implemented using Flex. The analyzer identifies tokens such as keywords, identifiers, constants, brackets, and special symbols in a given input file. 🔠

## Prerequisites 🔧
Before running the code, ensure you have the following tools installed:

1. **Flex** - a lexical analyser generator.
2. **Bison** - a parser generator (optional for this project).
3. **MinGW** (or any GCC-compatible compiler) - to compile the generated C code.

## Files 📂
- `lexer.l`: The Flex file containing the lexical analyzer code.
- `input.c`: A sample input file to be analyzed.

## Steps to Run 🚀
1. **Clone the Repository**:
   - Fork this repository and clone it to your local machine to encourage open contributions. 💡

   ```bash
   git clone <your-forked-repo-url>
   ```

2. **Navigate to the Project Directory**:
   ```bash
   cd <repository-name>
   ```

3. **Install Flex and MinGW** (if not already installed):
   - On Windows, install MinGW and add it to your PATH.
   - Install Flex through your package manager or download it directly from its official source.

4. **Generate the Lexical Analyzer**:
   ```bash
   flex lexer.l
   ```
   This command generates a `lex.yy.c` file. 🔄

5. **Compile the Code**:
   ```bash
   gcc lex.yy.c -o lexer
   ```

6. **Run the Lexical Analyzer**:
   - For **Lexer 1.0**:
     ```bash
     lexer1.exe < input.c
     ```
     - Replace `lexer.exe` with `./lexer` if you are on Linux or macOS.
     - The analyzer processes the `input.c` file and outputs the tokenized result. 🌟

   - For **Lexer 2.0**:
     ```bash
     lexer2.exe
     ```
     - Enter the code directly in the command window.
     - Type `END` (case-insensitive) on a new line to mark the end of input and process the output.
   - For **Lexer 3.0**:
     ```bash
     lexer3.exe
     ```
     - Detailed classification of tokens.
     - Summary lists of keywords, identifiers, constants, etc.

7. **Output**:
   The output lists tokens with the following details:
   - Token number
   - Line number
   - Token type (e.g., keyword, identifier, constant)
   - Lexeme

   Additionally, Lexer 2.0 displays a summary of:
   - Total keywords
   - Total identifiers
   - Total constants
   - Total brackets
   - Total special characters

## Future Enhancements 😎 (Done ✅)
### Lexer 3.0
- Enhanced output will include:
  - Detailed classification of tokens.
  - Summary lists of keywords, identifiers, constants, etc.

## Contribution 📚
We welcome contributions to this project. Feel free to fork this repository and submit pull requests. Join us in shaping the next iterations of this lexical analyzer! 🚀

Made with ❤️ by Nishant Sheoran







