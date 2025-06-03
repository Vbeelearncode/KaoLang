# KaoLang (👉ﾟヮﾟ)👉 Specification
created by Bao Vuong, 6/2/2025

KaoLang (👉ﾟヮﾟ)👉 is an esoteric programming language inspired by *Brainfuck*. It is written and maintained by Bao Vuong (aka Vbee). KaoLang (👉ﾟヮﾟ)👉 exists due to the lack of kaomoji usage in esoteric languages. Don't get tricked by the naive look of KaoLang (👉ﾟヮﾟ)👉 because it forces the user to do bit twiddling instead of + or - operation from *Brainfuck*.

## Commands

| Kaomoji                  | Functionality                                              |
|--------------------------|------------------------------------------------------------|
| 👈(ﾟヮﾟ👈)                 | Shift current memory cell value **left** by 1 (multiply by 2) |
| (👉ﾟヮﾟ)👉                 | Shift current memory cell value **right** by 1 (integer divide by 2) |
| 👈(⌒▽⌒)👉                | Apply **NAND** between current memory cell and value in register; store result in current memory cell; sets register value to 0 after operation |
| (ヘ･_･)ヘ┳━┳             | Begin loop if current memory cell is **not zero**           |
| (╯°□°）╯︵ ┻━┻           | End loop — jump back to matching loop start if current cell is **not zero** |
| ✍️(◔◡◔)                  | Output the character corresponding to the current memory cell |
| (⓿_⓿)                   | Read one byte from input into the current memory cell       |
| o(( >ω<))o               | Move memory pointer **right** by 1 cell                     |
| o((>ω< ))o               | Move memory pointer **left** by 1 cell                      |
| ᕦ(ò_óˇ)ᕤ                        | Copy current memory cell value into the **register**  if register value is 0, else replace memory cell value with value in register + set register value to 0    |

## Computational Class
KaoLang (👉ﾟヮﾟ)👉 is Turing complete because every command can be mapped to a *Brainfuck* command.

This table maps standard Brainfuck commands to their corresponding implementations in KaomojiLang, proving its Turing completeness.

| Brainfuck | KaoLang (👉ﾟヮﾟ)👉 Equivalent | Description |
|-----------|------------------------|-------------|
| `>`       | `o(( >ω<))o`           | Move memory pointer right |
| `<`       | `o((>ω< ))o`           | Move memory pointer left |
| `+`       | (see below)            | Increment current memory cell by 1 using NAND and shifts |
| `-`       | (see below)            | Decrement current memory cell by 1 using NAND and shifts |
| `.`       | `✍️(◔◡◔)`              | Output the character at current memory cell |
| `,`       | `(⓿_⓿)`               | Read one byte into current memory cell |
| `[`       | `(ヘ･_･)ヘ┳━┳`         | Start loop if current cell is not 0 |
| `]`       | `(╯°□°）╯︵ ┻━┻`       | Jump to matching `[` if current cell is not 0 |

---

### `+` — Increment Implementation

```
cell[0] stores a (original number); cell[1] stores b (= 1);
o(( >ω<))o                   // Move to cell[1]
👈(⌒▽⌒)👉                    // NAND with self → 255
ᕦ(ò_óˇ)ᕤ                     // Copy 255 to register
(👉ﾟヮﾟ)👉                     // Shift right → 127
👈(ﾟヮﾟ👈)                     // Shift left → 254
👈(⌒▽⌒)👉                    // NAND(255, 254) = 1; cell[1] = 1; register reset

(ヘ･_･)ヘ┳━┳                 // While b ≠ 0
o((>ω< ))o ᕦ(ò_óˇ)ᕤ         // Copy a to register
o(( >ω<))o o(( >ω<))o ᕦ(ò_óˇ)ᕤ // Paste a to cell[2]
o((>ω< ))o ᕦ(ò_óˇ)ᕤ         // Copy b
o(( >ω<))o 👈(⌒▽⌒)👉         // NAND a b; register reset
ᕦ(ò_óˇ)ᕤ                    // Copy NAND result to reg
👈(⌒▽⌒)👉                    // NAND again to get a & b; register reset

o((>ω< ))o ᕦ(ò_óˇ)ᕤ         // Copy b to reg
o(( >ω<))o o(( >ω<))o ᕦ(ò_óˇ)ᕤ // Paste b to cell[3]
ᕦ(ò_óˇ)ᕤ 👈(⌒▽⌒)👉           // ~b in cell[3]; register reset

o((>ω< ))o o((>ω< ))o o((>ω< ))o ᕦ(ò_óˇ)ᕤ  // Copy a
o(( >ω<))o o(( >ω<))o o(( >ω<))o o(( >ω<))o ᕦ(ò_óˇ)ᕤ // Paste a to cell[4]
ᕦ(ò_óˇ)ᕤ 👈(⌒▽⌒)👉           // ~a in cell[4]; register reset

o((>ω< ))o o((>ω< ))o o((>ω< ))o o((>ω< ))o ᕦ(ò_óˇ)ᕤ// Back to a, copy a
o(( >ω<))o o(( >ω<))o o(( >ω<))o  // To ~b
👈(⌒▽⌒)👉                       // cell[3] = NAND a ~b; register reset

o((>ω< ))o o((>ω< ))o ᕦ(ò_óˇ)ᕤ // Copy b
o(( >ω<))o o(( >ω<))o o(( >ω<))o // To ~a
👈(⌒▽⌒)👉                       // cell[4] = NAND b ~a; register reset

ᕦ(ò_óˇ)ᕤ o((>ω< ))o 👈(⌒▽⌒)👉 // Final XOR: (a NAND ~b) NAND (b NAND ~a); register reset

ᕦ(ò_óˇ)ᕤ o((>ω< ))o o((>ω< ))o o((>ω< ))o ᕦ(ò_óˇ)ᕤ // Paste XOR result back to cell a

o(( >ω<))o o(( >ω<))o ᕦ(ò_óˇ)ᕤ // Copy carry
o((>ω< ))o ᕦ(ò_óˇ)ᕤ            // Move to b and paste carry
👈(ﾟヮﾟ👈)                    // b = carry << 1  

(╯°□°）╯︵ ┻━┻               // End loop
```

---

### `-` — Decrement Implementation

```
cell[0] stores a (original number); cell[1] stores b (= 255);
o(( >ω<))o                   // Move to cell[1]
👈(⌒▽⌒)👉                    // NAND with self → 255

(ヘ･_･)ヘ┳━┳                 // While b ≠ 0
o((>ω< ))o ᕦ(ò_óˇ)ᕤ         // Copy a to register
o(( >ω<))o o(( >ω<))o ᕦ(ò_óˇ)ᕤ // Paste a to cell[2]
o((>ω< ))o ᕦ(ò_óˇ)ᕤ         // Copy b
o(( >ω<))o 👈(⌒▽⌒)👉         // NAND a b; register reset
ᕦ(ò_óˇ)ᕤ                    // Copy NAND result to reg
👈(⌒▽⌒)👉                    // NAND again to get a & b; register reset

o((>ω< ))o ᕦ(ò_óˇ)ᕤ         // Copy b to reg
o(( >ω<))o o(( >ω<))o ᕦ(ò_óˇ)ᕤ // Paste b to cell[3]
ᕦ(ò_óˇ)ᕤ 👈(⌒▽⌒)👉           // ~b in cell[3]; register reset

o((>ω< ))o o((>ω< ))o o((>ω< ))o ᕦ(ò_óˇ)ᕤ  // Copy a
o(( >ω<))o o(( >ω<))o o(( >ω<))o o(( >ω<))o ᕦ(ò_óˇ)ᕤ // Paste a to cell[4]
ᕦ(ò_óˇ)ᕤ 👈(⌒▽⌒)👉           // ~a in cell[4]; register reset

o((>ω< ))o o((>ω< ))o o((>ω< ))o o((>ω< ))o ᕦ(ò_óˇ)ᕤ// Back to a, copy a
o(( >ω<))o o(( >ω<))o o(( >ω<))o  // To ~b
👈(⌒▽⌒)👉                       // cell[3] = NAND a ~b; register reset

o((>ω< ))o o((>ω< ))o ᕦ(ò_óˇ)ᕤ // Copy b
o(( >ω<))o o(( >ω<))o o(( >ω<))o // To ~a
👈(⌒▽⌒)👉                       // cell[4] = NAND b ~a; register reset

ᕦ(ò_óˇ)ᕤ o((>ω< ))o 👈(⌒▽⌒)👉 // Final XOR: (a NAND ~b) NAND (b NAND ~a); register reset

ᕦ(ò_óˇ)ᕤ o((>ω< ))o o((>ω< ))o o((>ω< ))o ᕦ(ò_óˇ)ᕤ // Paste XOR result back to cell a

o(( >ω<))o o(( >ω<))o ᕦ(ò_óˇ)ᕤ // Copy carry
o((>ω< ))o ᕦ(ò_óˇ)ᕤ            // Move to b and paste carry
👈(ﾟヮﾟ👈)                    // b = carry << 1  

(╯°□°）╯︵ ┻━┻               // End loop
```