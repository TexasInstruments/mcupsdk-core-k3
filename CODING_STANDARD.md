# OneMCU Coding Standard

Source: TI Confluence — MCPI space, "OneMCU Coding Standard" (originally from the OneMCU TWiki).

## 1. Coding Standard Top 10 List

### 1. Variable Names

- All variables are CamelCase starting with a lowercase letter. Global variables must begin with their module name in CamelCase starting with a capital letter, followed by an underscore (`_`).
  - Examples: `uint16_t loopCounter;` `uint16_t ModuleName_globalVariable;`
- Type definitions must begin with their module name in CamelCase starting with a capital letter, followed by an underscore.
  - Example: `ModuleName_FruitTypes`
- Hungarian notation is not used.
- Defined constants must be in all caps and start with the module name.
  - Example: `#define MODULENAME_REGISTER_BIT (1 << 4)`

### 2. Function Names

- All functions must be of the form `ModuleName_verbNoun` where the regular expression format is: `[A-Z][a-zA-Z0-9]*_verb[Noun]`.
- Acronyms will be capital wherever they appear in the module or function name. All capitals is restricted to acronyms only.
- Common sense should be applied. For example, use `McBSP_*` instead of `Mcbsp_*` or `Int_*` instead of `NVIC_*`.
- Following the underscore, function names must be CamelCase starting with a lowercase letter and start with a verb describing the action of the function.
  - Examples: `UART_putChar();` `PWM_setPeriod();` `Timer_getValue();`

### 3. Comments

- All comments must use a C style comment delimiter (`/* */`) and be indented with the code. // Can be used only for CPP files. 

### 4. Function Prototypes

- All functions must be prototyped in a module's corresponding header file.
- All function declarations must contain the `extern` keyword. All inline functions must be `static`.
- Public API prototypes must include Doxygen comments. See the example header file in the appendix for more details.

### 5. Indentation

- Each indent level is four (4) spaces and all white space only contains spaces (no tabs).
- Continued lines must align sub-expressions with previous lines.

### 6. Bracketed statements must be in one of the following forms

```c
if(expr)
{
    stmt;
}
else
{
    stmt;
}
```

```c
do
{
    stmt;
} while(expr);
```

```c
for(expr;expr;expr)
{
    stmt;
}
```

```c
while(expr)
{
    stmt;
}
```

```c
switch(expr)
{
    case CONST_1:
        break;
    case CONST_2:
        break;
    default:
        break;
}
```

### 7. File Structure

- All software in a file must reside in one of the following sections. The sections must appear in the following order within a file: header, includes, defines, typedefs, globals, function prototypes. See the example header file in the appendix for more details.

### 8. Data Types — The following C99 data types must be used

1. `bool` for Boolean types, `char` for characters and strings.
2. `(u)int_leastX_t` (portable), `(u)int_fastX_t` (portable), and `(u)intX_t` (architecture specific), where X is 8, 16, 32, 64.
3. `float_t`, `double_t` and `long double` for floating point values.

### 9. Macro Definitions

1. Only single line macros are allowed. Inline functions must be used to optimize functions.

### 10. Not Needed :^)

## 2. Introduction

This file contains coding standards for source (`*.c` and `*.cpp`) and header files (`*.h` and `*.hpp`) in the form of portable C code, architecture-specific C code, and C++ code. It is meant to be a mechanism by which software can be created that is uniform in structure and functionality. While each programmer has their own coding style, the intent of these guidelines is to standardize the following:

1. File Conventions
2. Variable Conventions
3. Function Conventions
4. Code syntax

This coding standard should be followed for any software written for MCU, whether it is written by TI employees or by contractors. It is not absolutely required for internal-use code, though it is highly recommended since:

1. This repetition will help reinforce the use of the coding standards when writing customer-facing code.
2. Internal-use code might get turned into customer-facing code, which would require re-formatting the code so that it can be released.

All code written by contractors should follow this coding standard. The end goal for these coding standards is to make all of the software look consistent, giving the appearance that it was written by a single person.

These rules apply to software products owned by Texas Instruments. If, for example, a change or addition is being made to a piece of third-party software (such as an RTOS or a TCP/IP stack), then the coding standards (either explicit or implicit by observing the existing code) set forth by the third-party software project shall be followed for that work.

## 3. File Conventions

This section describes coding standards related to source and header files.

### 3.1 General Syntax

1. U.S. English is the language of choice for variable names, function names, comments, and so on.
2. No text shall appear after column 79. If it becomes necessary to go beyond column 79 in order to format the code, it is likely that the nesting level of the code has become too deep and that the function should be re-written to be less complex (and therefore requiring less indentation).
3. If lines are continued with the `\` character at the end of the line, then the `\` character shall reside in column 79.
4. No spurious spaces shall appear at the end of lines. The last character before the end-of-line character shall be a non-space character.
5. Special characters cannot be used.
   - Examples: Tab, page break, and so on.

### 3.2 File Format

1. The basic indentation must be 4 spaces.
2. Single spaces and newlines are the only allowed white space characters.
3. Unix end-of-line character (`\n` or ASCII LF `0x0A`) will be used on all files.
4. All source files must contain a header denoting the file name. See the example header file in the appendix for more details.
5. Any reference to a file name shall match the capitalization of the actual file name. For example, if there is a `foo.h`, the `#include` for it shall be `foo.h`, not `FOO.H` (or similar). The latter will work in Windows, but will fail in Linux/MacOS. This goes for any reference, even in a text file or document where the capitalization difference won't matter (since we never know what text might be cut-and-pasted into actual C code).
6. All source and header files must contain a copyright statement attributing the files to Texas Instruments. The year in the copyright statement refers to the year in which the file was created. It is the responsibility of the release script to update the date in the released version of the file to indicate the appropriate year.
7. No random blank line pattern must exist in the code. A single blank line shall separate blocks of non-blank line(s) and no blank lines shall appear at the end of the file.
8. "e.g." shall not be used; use "for example," instead. This requirement is needed to be consistent with TI's technical publication requirements.
9. "i.e." shall not be used; use "that is," instead. This requirement is needed to be consistent with TI's technical publication requirements.
10. "etc." shall not be used; use "and so on" instead. This requirement is needed to be consistent with TI's technical publication requirements.

### 3.3 Embedded Documentation

1. All public variables, defines, type definitions and function prototypes must have Doxygen comments. See the appendix for a header file example that uses Doxygen comments.
2. PDF and HTML document generation is required.
3. Documentation will be generated with an up to date version of Doxygen and Latex.

### 3.4 Comments

1. Code shall be commented to a level that the reader can understand what is going on without looking at the actual source lines.
2. Code comments shall be conceptual, not literal. "Set the FOO bit in the BAR register" is not a valid comment (it exactly matches the code); instead describe the effect of setting that bit.
3. Comments shall use a C style comment delimiter (`/* */`).
4. Each comment shall be preceded by a blank line and an empty comment line (`//`), and followed by an empty comment line and then the accompanying code. The only exception is at the beginning of the file and before each global entity (which have a specific comment block format), and immediately following an open brace (where the blank line is omitted).
5. Comments shall be indented to the same level as a real line of code would be if it were placed where the comment resides.
6. Every line of code shall be commented. This does not mean there is a single comment for every single line of code; there can be a comment that describes several lines of code. When several lines of code are described with a single comment, those lines of code shall be blocked together without any intervening blank lines. No "block" of code shall be uncommented.
7. **MCU+ SDK specific:** multi-line comments, other than the `/* === */` banner comments used for file sections, must follow this style — the opening `/*` is alone on its own line, each following line starts with ` * `, and the closing `*/` is on its own line:

   ```c
   /*
    * Call this API to stop the booting process and spin, do that you can connect
    * debugger, load symbols and then make the 'loop' variable as 0 to continue execution
    * with debugger connected.
    */
   ```

### 3.5 Names

File names must follow the following conventions.

1. The file name must be the module name contained within the source and header files.
2. The file name must be in lower case.
3. The extension for the source file name must be `*.c` or `*.cpp` (for C or C++ respectively).
4. The extension for the header file name must be `*.h` or `*.hpp` (for C or C++ respectively).

#### 3.5.1 Header Files

1. All public functions in a source file must have function prototypes in a header file of the same file name.

### 3.6 Third-Party Files

Public-domain or open-source software can be used, provided that the code does not put TI into a compromising legal position. Here are some items to consider:

1. If public-domain or open-source code is used, the appropriate copyright/etc. statements shall be maintained; if none exists then a comment shall be added that indicates the code origin. Non-TI code shall be maintained in separate source modules to clearly delineate between TI code and non-TI code.
2. Non-TI code that uses a viral license (for example, GPL) shall not be used.
3. The use of any public-domain or open-source code requires the approval of the Open Source Review Board.
4. The coding standard followed by the public-domain or open-source package shall be followed for any modifications/additions to that package.

## 4. Variable Conventions

This section describes coding standards related to variables.

### 4.1 Data Types

This section describes the data types for portable and architecture specific code.

#### 4.1.1 Portable

The purpose of this section is to provide a mechanism for portable software development across different processor architectures. By using portable data types, the software can be ported across architectures without modification. However, this feature does not always provide the most cycle efficient implementation.

1. The endianness of the processor is assumed to be little endian. If the processor is big endian, the complex data type definitions below must be modified.
2. The following data types must be used for developing portable code. If a data type has been defined by the C99 standard, it appears in the table.

| Type Name | Description |
|---|---|
| `bool` | A single Boolean value |
| `char` | A character |
| `int_least8_t` | A signed integer with a width of at least 8 bits |
| `uint_least8_t` | An unsigned integer with a width of at least 8 bits |
| `int_least16_t` | A signed integer with a width of at least 16 bits |
| `int_least32_t` | A signed integer with a width of at least 32 bits |
| `uint_least32_t` | An unsigned integer with a width of at least 32 bits |
| `int_least64_t` | A signed integer with a width of at least 64 bits |
| `uint_least64_t` | An unsigned integer with a width of at least 64 bits |
| `int_fast8_t` | The fastest signed integer with a width of at least 8 bits |
| `uint_fast8_t` | The fastest unsigned integer with a width of at least 8 bits |
| `int_fast16_t` | The fastest signed integer with a width of at least 16 bits |
| `uint_fast16_t` | The fastest unsigned integer with a width of at least 16 bits |
| `int_fast32_t` | The fastest signed integer with a width of at least 32 bits |
| `uint_fast32_t` | The fastest unsigned integer with a width of at least 32 bits |
| `int_fast64_t` | The fastest signed integer with a width of at least 64 bits |
| `uint_fast64_t` | The fastest unsigned integer with a width of at least 64 bits |
| `float_t` | A signed floating point number at least as wide as `float` |
| `double_t` | A signed floating point number at least as wide as `double` |
| `long double` | A signed floating point number at least as wide as `long double` |

3. The following definitions shall be used for integer complex data types, which depend on the sign of the real and imaginary components as well as the minimum bit width needed.

```c
typedef struct
{
    (u)int_leastX_t  imag;
    (u)int_leastX_t  real;
} cplx_(u)int_leastX_t;

typedef struct
{
    (u)int_fastX_t  imag;
    (u)int_fastX_t  real;
} cplx_(u)int_fastX_t;
```

Note that a compiler is free to choose appropriate sizes (bit widths) for its target hardware, subject to the restriction that a `short` and an `int` are at least 16 bits, a `long` is at least 32 bits, the number of bits in a `short` is not larger than the number of bits in an `int`, and the number of bits in an `int` is not larger than the number of bits in a `long`.

The purpose of using these data types instead of the inherent C data types is to allow for portable C code that can be migrated across multiple processor architectures and to maintain a valid memory architecture by controlling the mapping of the portable data types to the data types supported by a given target processor's compiler for the given processor architecture.

#### 4.1.2 Architecture Specific

The purpose of this section is to provide a mechanism for exact bit width representations of variables and their corresponding memory locations. This feature is important so that registers can be correctly represented in C code and to ensure the correct use of C intrinsics when optimizing software for a given target processor.

1. The endianness of the processor is assumed to be little endian. If the processor is big endian, the complex data type definitions below must be modified.
2. The following data types must be used for developing architecture-specific C code, which are all defined by the C99 standard.

| Type Name | Description |
|---|---|
| `int8_t` | A signed integer with a width of exactly 8 bits |
| `uint8_t` | An unsigned integer with a width of exactly 8 bits |
| `int16_t` | A signed integer with a width of exactly 16 bits |
| `uint16_t` | An unsigned integer with a width of exactly 16 bits |
| `int32_t` | A signed integer with a width of exactly 32 bits |
| `uint32_t` | An unsigned integer with a width of exactly 32 bits |
| `int64_t` | A signed integer with a width of exactly 64 bits |
| `uint64_t` | An unsigned integer with a width of exactly 64 bits |

3. The following definitions shall be used for complex data types:

```c
typedef struct
{
    (u)intX_t  imag;
    (u)intX_t  real;
} cplx_(u)intX_t;
```

### 4.2 Constants

1. The following values must be used for true(1) and false(0), which are the definitions found in `stdbool.h`.
2. The following values must be used for pass(1) and fail(0).

### 4.3 Names

1. Local variable names must be CamelCase, where the first letter is lowercase and the first letter of each subsequent concatenated word is capitalized.
   - Examples: `fruitType`, `vegetableType`
2. Global variables must be preceded by the module name, in CamelCase starting with a capital letter, followed by an underscore (`ModuleName_`).
   - Example: `FruitBasket_fruitType`, `VegBasket_vegetableType`
3. `#define` constant values must be in all capitals (`#define` macros are discussed in section 6).
   - Example: `#define APPLE (1)`
4. Variables must never have dual meaning within the scope of the variable.
   - Example: `i` should not be used as a loop variable in one portion of code and as an imaginary data value in another portion of code within the same scope.
5. Type names must start with a module name, in CamelCase starting with a capital letter, followed by an underscore (`ModuleName_`). The remaining type name must be mixed case starting with upper case.
   - Examples: `FruitBasket_FruitTypes`, `VegBasket_VegetableTypes`
6. Public constants must start with the module name, in all capital letters, and separated by an underscore. Constants must be all upper case using an underscore.
   - Examples: `FRUITBASKET_APPLE_COLOR`, `VEGBASKET_CUCUMBER_COLOR`
7. Object names must start with the object name (`ObjectName`), in CamelCase starting with a capital letter, and end with `_Obj`. This also applies to struct when used as objects in C.
   - Example: `FruitBasket_Obj`
8. Handle names must start with the object name (`ObjectName`), in CamelCase starting with a capital letter, and end with `_Handle`. Note, a handle is just an object pointer.
   - Example: `FruitBasket_Handle`
9. Use variable names that are descriptive and appropriate for the context.
10. Negated Boolean variables should be avoided.
    - Example: `isError` instead of `isNoError`
11. Generic variables must have the same name as their type.
    - Example: `void displayFruitType(Fruit fruit)`
12. Pointers and references must have their symbol next to the variable name instead of the data type.
    - Example: `int *apples` instead of `int * apples`
13. Enumerated constants must be prefixed with a common name. If the first element must be initialized, then all values must be initialized.
    - Example:

```c
typedef enum
{
    Fruit_Apple = 0,
    Fruit_Orange = 1
} Fruits;
```

14. Hungarian notation is not used.

## 5. Function Conventions

This section defines the coding standard for functions.

### 5.1 Names

1. Function names: the regular expression for a function name is `[A-Z][a-zA-Z0-9]*_verb[Noun]`.
   - All functions must begin with their module name followed by an underscore, a verb, and an optional noun. The verb followed by an optional noun is in CamelCase, where the first letter is lowercase and the first letter of each subsequent concatenated word is capitalized.
     - Generic examples: `FruitBasket_getFruitType()`, `FruitBasket_computeAverageAppleSize()`
     - No noun examples: `UDMA_start()`, `Widget_add()`
   - Acronyms will be capital wherever they appear in the module or function name. All capitals is restricted to acronyms only.
     - Acronym examples: `CAN_getbitTiming()`, `ADC_getClockConfig()`, `ModuleName_genDSPCode()`
   - Common sense clause: when applying the rules above, common sense should be applied.
     - Example: McBSP is widely accepted. Use `McBSP_*` instead of `MCBSP_*` or `Mcbsp_*`.
2. Abbreviations in function names should be avoided. If an abbreviation is used to reduce the function name's length, then it must have a clear, generally accepted meaning. For example, `Tx` or `Rx`.
   - Example: `computeAverage()` instead of `compAvg()`
3. `const` must be used for all constant function arguments.
   - Example: `extern void FruitBasket_displayFruitType(const Fruit fruit);`
4. Approved verbs include:
   - The verbs *get/put* are used when a function accesses an entity directly.
   - The verb *compute* is used when a function computes an entity.
   - The verb *find* is used when a function searches for an entity.
   - The verb *is* is used for Boolean functions.
   - The verb *init* is used when a function initializes an entity and must return a handle to an entity.
   - The verb *setup* is used when a function configures an entity for operation.
   - The verb *run* is used when a function runs an entity.
   - The verb *gen* is used when a function generates an entity.
   - The verb *enable/disable* must be used when a function turns on/off an entity.
   - The verb *set/clear* must be used when a function sets or clears an entity's state.

## 6. Code Syntax

1. Majik (magic) variables are not allowed. Comparisons using define and enumeration values should not involve their numerical equivalents. Instead, use define and enumeration variables.
   - Example: `if(fruit == Fruit_Apple)` instead of `if(fruit == 0)`
2. Loop test variables must be initialized immediately before the loop.
3. No spaces shall exist between unary or primary operators (`->`, `.`, `[]`, `()`, `sizeof`, etc.).
   - Examples: `i++`, `(char *)p`, `*p`, `-17`, `sizeof(uint16_t)`, `a[i]`, `s.member`, `p->member`
4. One space shall exist between the comma and the next argument in a function definition and a function call.
   - Example: `f(x, y)`
5. One space shall exist between other operators and their operands.
   - Examples: `x = f(y) * (z + 2);`, `(p = NULL) && (p->member == -1)`
6. There shall be no spaces around parentheses, except when the space separates the parenthesis from an operator. This implies no spaces between an `if`, `while`, `return`, and so on, and the accompanying parentheses.
7. There shall not be spaces after unary operators, such as `*`, `!`, `~`, etc.
8. There shall be spaces around all binary and tertiary operators, such as `+`, `*`, `?`, `:`, `==`, `=`, etc.
9. Parentheses are to be used to improve clarity of expressions with several precedence levels.
   - Nested operations will always use parentheses to define operation order.
     - Example: `(x < y) & mask`
10. Expressions with side effects are not to be used in function calls.
    - Example:

      ```c
      t = min(x, y);
      x++;
      ```

      instead of

      ```c
      t = min(x++, y);
      ```

11. When an expression spans multiple lines, the beginning of each new line must be aligned within the scope of the previous line.
    - Example:

      ```c
      if(!ModuleName_variableName == (MODULENAME_CONST_1 || MODULENAME_CONST_2 ||
                                      MODULENAME_CONST_3))
      {
          /* Do Something */
      }
      ```

12. When an expression spans multiple lines, complete sub-expressions shall exist on each line, with the operator connecting them appearing at the end of the previous line. For example, `((a && b) &&` on one line and `(c && d))` on another.
    - Example:

      ```c
      if((a && b) &&
         (c && d))
      {
          /* Do Something */
      }
      ```

13. When an expression spans multiple lines, subsequent lines are aligned with the matching level of sub-expression on the previous line. For example, if the first line is `((a && b) ||` and the second is `(c && d))`, then the open parenthesis on the second line shall line up with the second open parenthesis on the first line.
    - Example:

      ```c
      if((a && b) ||
         (c && d))
      {
          /* Do Something */
      }
      ```

14. Parentheses shall surround an entire expression that spans multiple lines. For example, if `(a && b) ||` were placed on one line and `(c && d)` on the next, parentheses need to be placed around the entire expression, making it `((a && b) ||` and `(c && d))`.
15. One statement can exist per line. Note that a `for` statement contains three expressions, which can all be on the same line.
16. Left braces will follow the statement which opens a subordinate clause while right braces will be left justified with the statement that opened the subordinate clause.
    - Example:

      ```c
      if(variable == MODULENAME_CONST)
      {
          /* Do Something */
      }
      ```

17. Left and right braces which open and close a function will be fully left justified with both braces on their own line.
    - Example:

      ```c
      void Foo_getBar(void)
      {
          /* Do Something */
          return;
      }
      ```

18. Braces must be used for one or more lines of conditionally blocked code.
19. Left and right braces must be column aligned according to indentation rules.
20. The indentation inside of braces shall be 4 spaces.
21. When returning a value from a function, the value must be surrounded by parentheses and no space is allowed between the `return` keyword and the open parenthesis. Using a `return` keyword at the end of a `void` function is allowed but not required.
    - Example: `return(value);`
22. All public or externally callable functions (API functions) shall be `extern`'ed and prototyped in a header file corresponding to the function's module name.
    - Example: `extern void Foo_getBar(void);`
23. Function declarations shall follow the single space after comma rule.
    - Example: `extern uint16_t Foo_getValue(const uint8_t oldValue_1, const int32_t oldValue_2);`
24. Macro definitions must follow one of the following forms:
    - Single token:
      - Example: `#define Que_enqueue Que_put`
    - Function or macro call:
      - Example: `#define C62_enableGie(mask) Hwi_restore(mask)`
    - Enclosed in parentheses:
      - Example: `#define C62_mask(devId) ((uint16_t)(1 << (devId) 1))`
    - Macro function definitions are not allowed. Inline functions must be used instead.
    - Macro arguments shall always appear inside dedicated parentheses in the macro expansion.
      - Example: `#define Foo(a, b) ((a) && (b))`
25. Inline functions should be `static`.
    - Example:

      ```c
      static inline void Foo_getBar(void)
      {
          /* Do Something */
          return;
      }
      ```

26. Inline functions can be used to better enable optimized functions.

## 7. Additional Conventions for C++ (Under Construction)

The following coding standards for C++ are in addition to the coding standards for C, which have been discussed previously.

### 7.1 Variable Conventions

1. Private class variables must have an underscore suffix.
   - Examples: `numApples_`, `numCucumbers_`
2. Template names must be a single upper case letter.
   - Example: `Template`
3. The name of the object must not be part of the method name.
   - Example: `apple.getColor()` instead of `apple.getAppleColor()`

#### 7.1.1 Classes

1. A class must be declared in a header file and defined in a source file.
2. Class names must be mixed case starting with upper case.
   - Examples: `FruitClass`, `VegetableClass`

### 7.2 File Conventions

#### 7.2.1 Names

File names must follow the function naming conventions.

1. The extension for the source file name must be `*.cpp`.
2. The extension for the header file name must be `*.hpp`.

## 8. References

1. *Programming languages — C*, International Standard ISO/IEC 9899:1999(E), Second Edition, December 1, 1999.

## 9. Appendix

### 9.1 Example Header File

> Note: A standard header file example is still under construction.

This section provides a standard header file, whose structure should be followed by each module. Portions of this example should be modified to represent the specific module. For example, replace `MODULENAME` and `ModuleName` with the appropriate module name.

```c
/*
 * Copyright (C) 2026 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * \defgroup ModuleName
 *
 * \ingroup ModuleName
 * @{
 */

/**
 *  \file modulename.h
 *
 *  \brief Module description
 */
#ifndef MODULENAME_H_
#define MODULENAME_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <drivers/hw_include/cslr.h>

#ifdef __cplusplus
extern "C" {
#endif


/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/*! \brief Description of this define */
#define MODULENAME_REGISTERNAME_BITFIELDNAME (1 << 4)

/*! \brief Description of this define */
#define ModuleName_clearState    Standard_clear

/*! \brief Description of this define */
#define ModuleName_putData(data)    Uart_putData(data)

/*! \brief Description of this define */
#define ModuleName_maskData(data)    ((data >> 8) & 0x00FF)

/*! \brief Description of this enumeration */
typedef enum
{
    ModuleName_enumeration_name1_1 = 0,    /*!< Denotes enumeration state 1 */
    ModuleName_enumeration_name1_2 = 1,    /*!< Denotes enumeration state 2 */
    ModuleName_enumeration_name1_3 = 2     /*!< Denotes enumeration state 3 */
} ModuleName_enumeration_name1;

/*! \brief Description of this enumeration */
typedef enum
{
    ModuleName_enumeration_name2_1 = (1 << 0),      /*!< Denotes interrupt number 1 */
    ModuleName_enumeration_name2_2 = (1 << 1),      /*!< Denotes interrupt number 2 */
    ModuleName_enumeration_name2_3 = (1 << 2),      /*!< Denotes interrupt number 3 */
    ModuleName_enumeration_name2_4 = (1 << 3),      /*!< Denotes interrupt number 4 */
    ModuleName_enumeration_name2_5 = (1 << 4),      /*!< Denotes interrupt number 5 */
    ModuleName_enumeration_name2_6 = (1 << 5),      /*!< Denotes interrupt number 6 */
    ModuleName_enumeration_name2_7 = (1 << 6),      /*!< Denotes interrupt number 7 */
    ModuleName_enumeration_name2_8 = (1 << 7),      /*!< Denotes interrupt number 8 */
} ModuleName_enumeration_name2;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/*! \brief Defines the module (ModuleName) object */
typedef struct ModuleName_Obj_
{
    uint8_t   tmp;   /*!< a filler value for the object */
} ModuleName_Obj;

/*! \brief Defines the module (ModuleName) handle */
typedef struct ModuleName_Obj * ModuleName_Handle;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/*! \brief Defines the ModuleName object */
extern ModuleName_Obj ModuleName_objectName;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*!
 *  \brief         Does something which is described here
 *  \param[in] handle  The module (ModuleName) handle
 */
extern void ModuleName_doSomething(ModuleName_Handle handle);

/*!
 *  \brief          Initializes the module (ModuleName) object handle
 *  \param[in] pMemory    A pointer to the memory for the module (ModuleName) object
 *  \param[in] numBytes   The number of bytes allocated for the module (ModuleName) object, bytes
 *  \return       The module (ModuleName) handle
 */
extern ModuleName_Handle ModuleName_init(void *pMemory, const size_t numBytes);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/*!
 *  \brief          Gets data from an object
 *  \param[in] handle  The module (ModuleName) handle
 *  \return        The data value
 */
static inline uint8_t ModuleName_getData(ModuleName_Handle handle)
{
    ModuleName_Obj *obj = (ModuleName_Obj *)handle;
    return (obj->tmp);
} /* end of ModuleName_getData() function */

/*!
 *  \brief          Sets data in an object
 *  \param[in] handle  The module (ModuleName) handle
 *  \param[in] data      The desired data value
 */
static inline void ModuleName_setData(ModuleName_Handle handle, const uint8_t data)
{
    ModuleName_Obj *obj = (ModuleName_Obj *)handle;
    /* set the data value */
    obj->tmp = data;
    return;
} /* end of ModuleName_setData() function */

#ifdef __cplusplus
}
#endif /* extern "C" */

/*@}*/  /* ingroup */

#endif  /* end of MODULENAME_H_ definition */
```

### 9.2 API Deprecation

This section describes the method which should be used to deprecate any API. This method is the same one used in the LM3S StellarisWare package.

1. Either:
   - a) Remove the source for the deprecated function and define a macro which maps the old function to its replacement, using default values for any new parameters.

     OR

   - b) Add `#ifndef DEPRECATED`/`#endif` around the function if no replacement is being offered. When a macro is defined it must operate exactly as the deprecated function did.
2. Put the macro or original function prototype and any deprecated label definitions into a section of the public header separated using `#ifndef DEPRECATED`/`#endif`.
3. Document the change in release notes and in the documentation for the replacement function.
4. For internal builds, ensure that `-DDEPRECATED` is used so that all deprecated functions and labels are effectively removed from the headers. This makes sure that we are never calling any deprecated functions or using deprecated labels in our examples or in calls between modules. Customer builds won't have this label defined and will still build and run as before.

The following examples (from the StellarisWare versions of `timer.h` and `flash.h`) use the StellarisWare coding standard, not the OneMCU standard defined here. They are for example purposes only.

```c
/*
 * TimerQuiesce() has been deprecated.  SysCtlPeripheralReset() should be used
 * instead to return the timer to its reset state.
 */
#ifndef DEPRECATED
extern void TimerQuiesce(unsigned long ulBase);
#endif


/*
 * These values for TimerConfigure have been deprecated.
 */
#ifndef DEPRECATED
#define TIMER_CFG_32_BIT_OS        0x00000021  /* 32-bit one-shot timer */
#define TIMER_CFG_32_BIT_OS_UP     0x00000031  /* 32-bit one-shot up-count timer */
#define TIMER_CFG_32_BIT_PER       0x00000022  /* 32-bit periodic timer */
#define TIMER_CFG_32_BIT_PER_UP    0x00000032  /* 32-bit periodic up-count timer */
#define TIMER_CFG_32_RTC           0x01000000  /* 32-bit RTC timer */
#define TIMER_CFG_16_BIT_PAIR      0x04000000  /* Two 16-bit timers */
#endif


/*
 * Deprecated function names.  These definitions ensure backwards compatibility
 * but new code should avoid using deprecated function names since these will
 * be removed at some point in the future.
 */
#ifndef DEPRECATED
#define FlashIntGetStatus       FlashIntStatus
#endif
```
