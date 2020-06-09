// [x86data.js]
// X86/X64 instruction-set data.
//
// [License]
// Public Domain.


// This file can be parsed as pure JSON, locate ${JSON:BEGIN} and ${JSON:END}
// marks and strip everything outside, a sample JS function that would do the job:
//
// function strip(s) {
//   return s.replace(/(^.*\$\{JSON:BEGIN\}\s+)|(\/\/\s*\$\{JSON:END\}\s*.*$)/g, "");
// }


// INSTRUCTIONS
// ============
//
// Each instruction definition consists of 5 strings:
//
//   [0] - Instruction name.
//   [1] - Instruction operands.
//   [2] - Instruction encoding.
//   [3] - Instruction opcode.
//   [4] - Instruction metadata - CPU features, FLAGS (read/write), and other metadata.
//
// The definition tries to match Intel and AMD instruction set manuals, but there
// are small differences to make the definition more informative and compact.


// OPERANDS
// ========
//
//   * "op"    - Explicit operand, must always be part of the instruction. If a fixed
//               register (like "cl") is used, it means that the instruction uses this
//               register implicitly, but it must be specified anyway.
//
//   * "<op>"  - Implicit operand - some assemblers allow implicit operands the be passed
//               explicitly for documenting purposes. And some assemblers like AsmJit's
//               Compiler infrastructure requires implicit operands to be passed explicitly
//               for register allocation purposes.
//
//   * "{op}"  - Optional operand. Mostly used by AVX_512:
//
//               - {k} mask selector.
//               - {z} zeroing.
//               - {1tox} broadcast.
//               - {er} embedded-rounding.
//               - {sae} suppress-all-exceptions.
//
//   * "?:Op"  - Each operand can provide metadata that can be used to describe which
//               operands are used as a destination, and which operands are source-only.
//               Each instruction in general assumes that the first operand is always
//               read/write and all following operands are read-only. However, this is
//               not correct for all instructions, thus, instructions that don't match
//               this assumption must provide additional information:
//
//               - "R:Op" - The operand is read-only.
//               - "w:Op" - The operand is write-only (does not zero-extend).
//               - "W:Op" - The operand is write-only (implicit zero-extend).
//               - "x:Op" - The operand is read/write (does not zero-extend).
//               - "X:Op" - The operand is read/write (implicit zero-extend).
//
//   * Op[A:B] - Optional bit-range that describes which bits are read and written.
//
//   * "~Op"   - Operand is commutative with other operands prefixed by "~". Commutativity
//               means that all operands marked by '~' can be swapped and the result of the
//               instruction would be the same.

// WHAT IS MISSING
// ===============
//
// Here is a list of missing instructions to keep track of it:
//
// [ ] call/jmp/ret (far)
// [ ] xlat/xlatb