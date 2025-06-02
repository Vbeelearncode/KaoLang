# KaoLang (👉ﾟヮﾟ)👉 Specification
created by Bao Vuong, 6/2/2025

KaoLang (👉ﾟヮﾟ)👉 is an esoteric programming language inspired by *Brainfuck*. It is written and maintained by Bao Vuong (aka Vbee). KaoLang (👉ﾟヮﾟ)👉 exists due to the lack of kaomoji usage in esoteric languages. Don't get tricked by the naive look of KaoLang (👉ﾟヮﾟ)👉 because it forces the user to do bit twiddling instead of + or - operation from *Brainfuck*.

## Commands

| Kaomoji                  | Functionality                                              |
|--------------------------|------------------------------------------------------------|
| 👈(ﾟヮﾟ👈)                 | Shift current memory cell value **left** by 1 (multiply by 2) |
| (👉ﾟヮﾟ)👉                 | Shift current memory cell value **right** by 1 (integer divide by 2) |
| 👈(⌒▽⌒)👉                | Apply **NAND** between current memory cell and value in register; store result in current memory cell |
| (ヘ･_･)ヘ┳━┳             | Begin loop if current memory cell is **not zero**           |
| (╯°□°）╯︵ ┻━┻           | End loop — jump back to matching loop start if current cell is **not zero** |
| ✍️(◔◡◔)                  | Output the character corresponding to the current memory cell |
| (⓿_⓿)                   | Read one byte from input into the current memory cell       |
| o(( >ω<))o               | Move memory pointer **right** by 1 cell                     |
| o((>ω< ))o               | Move memory pointer **left** by 1 cell                      |
| ᕦ(ò_óˇ)ᕤ                        | Copy current memory cell value into the **register**        |

