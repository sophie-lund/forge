<!--
Copyright 2025 Sophie Lund

This file is part of Forge.

Forge is free software: you can redistribute it and/or modify it under the terms of the GNU
General Public License as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

Forge is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along with Forge. If not, see
<https://www.gnu.org/licenses/>.
-->

# Language planning

!!! note

    This page is incomplete. There's a lot of language rules that are taken for granted since Forge has somewhat similar syntax to C.

## Comments

```
// This is a line comment

/* This is a block comment */
```

## Types

### Basic types

Forge has the following basic types:

| Keyword | Format  | Bit width     | Signed? | Description                                                                     |
| ------- | ------- | ------------- | ------- | ------------------------------------------------------------------------------- |
| `bool`  | Boolean | At least 1    | No      | Can be `true` or `false`                                                        |
| `i8`    | Integer | 8             | Yes     | Signed 8-bit integer                                                            |
| `i16`   | Integer | 16            | Yes     | Signed 16-bit integer                                                           |
| `i32`   | Integer | 32            | Yes     | Signed 32-bit integer                                                           |
| `i64`   | Integer | 64            | Yes     | Signed 64-bit integer                                                           |
| `u8`    | Integer | 8             | No      | Unsigned 8-bit integer                                                          |
| `u16`   | Integer | 16            | No      | Unsigned 16-bit integer                                                         |
| `u32`   | Integer | 32            | No      | Unsigned 32-bit integer                                                         |
| `u64`   | Integer | 64            | No      | Unsigned 64-bit integer                                                         |
| `f32`   | Float   | 32            | Yes     | 32-bit floating point                                                           |
| `f64`   | Float   | 64            | Yes     | 64-bit floating point                                                           |
| `isize` | Integer | Pointer width | Yes     | Signed integer with the same number of bits as the target system architecture   |
| `usize` | Integer | Pointer width | No      | Unsigned integer with the same number of bits as the target system architecture |
| `null`  | -       | -             | -       | Represents a null value                                                         |
| `never` | -       | -             | -       | Represents a value which can never exist                                        |
| `void`  | -       | -             | -       | Placeholder for functions or expressions which return nothing.                  |

### Pointer types

You can turn any type into a pointer type be prefixing it with `*`. You can do this multiple times to get a pointer to a pointer, etc.

For example `*i32` is a pointer to a 32-bit signed integer.

### Constant types

You can make a type constant by prefixing it with `const`. This means that the value of the constant cannot be changed after it is initialized.

For example `const String` is a constant string. It can be combined with pointers like so `*const i32`.

## Expressions

### Literals

#### Boolean

There are two boolean literals: `true` and `false`. They are both of type `bool`.

#### Integer

Integer literals are written as a sequence of digits. They can be written in different bases depending on prefix:

| Prefix | Base | Digit regex   |
| ------ | ---- | ------------- |
| `0b`   | 2    | `[0-1]`       |
| `0o`   | 8    | `[0-7]`       |
| `0x`   | 16   | `[0-9a-fA-F]` |

If no prefix is provided, the integer is assumed to be in base 10. Base 10 integers cannot start with `0` digits.

You can separate groups of digits with `_` characters to improve readability. Integers cannot start or end with these separators. They are ignored by the compiler.

All integer literals are of type `i32` by default, extending to `i64` if needed to contain the value. You can suffix the literal with an integer type to specify a different type.

| Example  | Valid? | Description                                                                      |
| -------- | ------ | -------------------------------------------------------------------------------- |
| `5`      | Yes    | A simple decimal value                                                           |
| `0b101`  | Yes    | A binary value                                                                   |
| `05`     | No     | A decimal value cannot start with `0`                                            |
| `0x1F`   | Yes    | A hexadecimal value                                                              |
| `1_000`  | Yes    | A decimal value with a separator                                                 |
| `_10`    | N/A    | This will be interpreted as a symbol instead of as an integer                    |
| `10_`    | No     | A `_` separator cannot be at the end of a literal                                |
| `5u8`    | Yes    | An 8-bit unsigned integer                                                        |
| `5isize` | Yes    | A signed integer the same width as the target system architecture's pointer type |

#### Float

Float literals are very similar to integer literals. They must contain a decimal point and at least one digit on either side of it. Integer type suffixes obviously cannot be used, but `f32` and `f64` can be. All float literals are `f64` by default.

| Example  | Valid? | Description                                                 |
| -------- | ------ | ----------------------------------------------------------- |
| `5.0`    | Yes    | A simple decimal value                                      |
| `5.`     | No     | A decimal point must be followed by a digit                 |
| `.5`     | No     | A decimal point must be preceded by a digit                 |
| `5.0f32` | Yes    | A 32-bit floating point                                     |
| `5.0f64` | Yes    | A 64-bit floating point                                     |
| `0x5.a`  | Yes    | A hexadecimal floating point equal to `5 + 10 / 16 = 5.625` |

### Operators

| Operator                                                                                                                        | Description               | Typing                                                                                                                                                 |
| ------------------------------------------------------------------------------------------------------------------------------- | ------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `!a`                                                                                                                            | Boolean negation          | The operand must be a `bool` and the result is a `bool`.                                                                                               |
| `a && b`                                                                                                                        | Boolean and               | Both operands must be `bool` and the result is a `bool`.                                                                                               |
| <code>a &#124;&#124; b</code>                                                                                                   | Boolean or                | Both operands must be `bool` and the result is a `bool`.                                                                                               |
| `~a`                                                                                                                            | Bitwise not               | The operand must be an integer and the result is an integer of that same type.                                                                         |
| `a & b`                                                                                                                         | Bitwise and               | Both operands must be integers with the same signedness and the result is an integer of that same signedness with the max bit width of `a` and `b`.    |
| <code>a &#124; b</code>                                                                                                         | Bitwise or                | Both operands must be integers with the same signedness and the result is an integer of that same signedness with the max bit width of `a` and `b`.    |
| `a ^ b`                                                                                                                         | Bitwise xor               | Both operands must be integers with the same signedness and the result is an integer of that same signedness with the max bit width of `a` and `b`.    |
| `a << b`                                                                                                                        | Bitwise shift left        | `a` must be an integer and `b` must be an unsigned integer. The result is an integer of the same type as `a`.                                          |
| `a >> b`                                                                                                                        | Bitwise shift right       | `a` must be an integer and `b` must be an unsigned integer. The result is an integer of the same type as `a`.                                          |
| `-a`                                                                                                                            | Arithmetic negation       | The operand must be a signed numeric type and the result follows [arithmetic containing type](#arithmetic-containing-types) logic.                     |
| `a + b`                                                                                                                         | Arithmetic addition       | Both operands must be numeric types and the result follows [arithmetic containing type](#arithmetic-containing-types) logic.                           |
| `a - b`                                                                                                                         | Arithmetic subtraction    | Both operands must be numeric types and the result follows [arithmetic containing type](#arithmetic-containing-types) logic.                           |
| `a * b`                                                                                                                         | Arithmetic multiplication | Both operands must be numeric types and the result follows [arithmetic containing type](#arithmetic-containing-types) logic.                           |
| `a / b`                                                                                                                         | Arithmetic division       | Both operands must be numeric types and the result follows [arithmetic containing type](#arithmetic-containing-types) logic.                           |
| `a % b`                                                                                                                         | Arithmetic modulus        | Both operands must be numeric types and the result follows [arithmetic containing type](#arithmetic-containing-types) logic.                           |
| `a ** b`                                                                                                                        | Exponentiation            | Both operands must be numeric types and the result follows [arithmetic containing type](#arithmetic-containing-types) logic.                           |
| `a == b`                                                                                                                        | Equality                  | Both operands must be numeric types and the result is a `bool`.                                                                                        |
| `a != b`                                                                                                                        | Inequality                | Both operands must be numeric types and the result is a `bool`.                                                                                        |
| `a < b`                                                                                                                         | Less than                 | Both operands must be numeric types and the result is a `bool`.                                                                                        |
| `a <= b`                                                                                                                        | Less than or equal        | Both operands must be numeric types and the result is a `bool`.                                                                                        |
| `a > b`                                                                                                                         | Greater than              | Both operands must be numeric types and the result is a `bool`.                                                                                        |
| `a >= b`                                                                                                                        | Greater than or equal     | Both operands must be numeric types and the result is a `bool`.                                                                                        |
| `a = b`                                                                                                                         | Assignment                | The type of `b` must be [implicitly castable](#implicit-casting) to the type of `a`. The result of `void`.                                             |
| `a &= b`, <code>a &#124;= b</code>, `a ^= b`, `a <<= b`, `a >>= b`, `a += b`, `a -= b`, `a *= b`, `a /= b`, `a %= b`, `a **= b` | Compound assignment       | The type of `b` must be [implicitly castable](#implicit-casting) to the type of `a`. The result of `void`.                                             |
| `*a`                                                                                                                            | Pointer dereference       | `a` must be a pointer type. The result is the type pointed to by `a`.                                                                                  |
| `&a`                                                                                                                            | Address of                | The result is a pointer to `a`.                                                                                                                        |
| `f(a, b, c, ...)`                                                                                                               | Function call             | `f` must be a function and the arguments must be [implicitly castable](#implicit-casting) to the expected types. The result is the return type of `f`. |
| `a[b]`                                                                                                                          | Index                     | `a` must be indexable and `b` must be of the expected index type.                                                                                      |
| `a.b`                                                                                                                           | Member access             | `a` must be a structured type `b` must be an identifier. The result is the type of `b`.                                                                |
| `a as T`                                                                                                                        | Casting                   | `a` must be castable to `T`. The result is of type `T`.                                                                                                |

#### Arithmetic containing types

If two operands are combined arithmetically, you want the result to be stored in a type granular enough to contain that result without loss of precision. The following rules are used to determine the type of the result:

- If all operands are the same type, then the result will be that type.
- If one or more of the operands is a float, then the result will be a float.
- If one or more of the operands is signed, then the result will be signed.
- The result will be the maximum of the operands' bit widths.

#### Precedence

Higher values of precedence mean the operators bind more tightly.

| Operators                                                                                                                                | Precedence | Group name         |
| ---------------------------------------------------------------------------------------------------------------------------------------- | ---------- | ------------------ |
| `a.b`, `a[b]`                                                                                                                            | 1          | Paths              |
| `f(a, b, c, ...)`                                                                                                                        | 1          | Function calls     |
| `*a`, `&a`, `-a`, `+a`, `~a`, `!a`                                                                                                       | 1          | Unary              |
| `a ** b`                                                                                                                                 | 3          | Exponentiation     |
| `a * b`, `a / b`, `a % b`                                                                                                                | 4          | Multiplicative     |
| `a + b`, `a - b`                                                                                                                         | 5          | Additive           |
| `a << b`, `a >> b`                                                                                                                       | 6          | Bit shifts         |
| `a & b`, `a ^ b`                                                                                                                         | 9          | Binary conjunctive |
| <code>a &#124; b</code>                                                                                                                  | 11         | Binary disjunctive |
| `a == b`, `a != b`, `a < b`, `a <= b`, `a > b`, `a >= b`                                                                                 | 7          | Comparative        |
| `a && b`                                                                                                                                 | 12         | Boolean and        |
| <code>a &#124;&#124; b</code>                                                                                                            | 13         | Boolean or         |
| `a as T`                                                                                                                                 | 2          | Casts              |
| `a = b`, `a &= b`, <code>a &#124;= b</code>, `a ^= b`, `a <<= b`, `a >>= b`, `a += b`, `a -= b`, `a *= b`, `a /= b`, `a %= b`, `a **= b` | 15         | Assignments        |

### Casting

Explicit casting is done using the `as` operator.

#### Implicit casting

!!! todo

    This section is incomplete.

## Statements

### Return statements

```
return;

return 5;
```

### If statements

```
if a {
    // ...
} else if b {
    // ...
} else {
    // ...
}
```

### While loops

```
while a {
    // ...
}

do {
    // ...
} while a;
```

### For-each loops

```
for i in a {
    // ...
}
```

### Match statements

```
match a {
    1 -> {
        // ...
    }
    2 -> {
        // ...
    }
    default {
        // ...
    }
}
```

### Break and continue

```
break;
continue;
```

## Declarations

### Variables

```
// x's type is automatically detected from the initial value
let x = 5;

// x's type is explicitly set and 5 is implicitly cast to an i64
let x: i64 = 5;

// x is a constant
const x = 5;

// this is equivalent to
let x: const i32 = 5;
```

### Functions

```
// f is a function that takes no arguments and returns nothing
func f() -> void {
    // ...
}

// f is a function that takes two i32 arguments and returns an i32
func f(a: i32, b: i32) -> i32 {
    // ...
}
```

### Structs

```
struct Point {
    x: f64;
    y: f64;

    func distance() -> f64 {
        return sqrt(self.x ** 2 + self.y ** 2);
    }
}

struct Box extends Point {
    w: f64;
    h: f64;

    func area() -> f64 {
        return self.w * self.h;
    }

    func bottom_right_corner() -> Point {
        return { x: self.x + self.w, y: self.y + self.h };
    }
}
```

### Unions

!!! todo

    I hate this - ideally structs could be powerful enough to handle this instead of syntax sugar.

```
union IntOrFloat {
    i -> i32;
    f -> f32;
}

let x: IntOrFloat = { i: 5 };

x == 5;
x.variant == IntOrFloatType.i;
```

### Interfaces

```
interface Locatable {
    x: f64;
    y: f64;

    func distance() -> f64;
}

struct Point extends Locatable {
    x: f64;
    y: f64;

    func distance() -> f64 {
        return sqrt(self.x ** 2 + self.y ** 2);
    }
}
```

### Type aliases

```
// MyInt and i32 are implicitly castable
type MyInt = i32;

// MyInt and i32 are NOT implicitly castable
explicit type MyInt = i64;
```

### Namespaces

```
namespace x {
    // ...
}
```
