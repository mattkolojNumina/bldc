# VESC Firmware Coding Style and Conventions

## Indentation and Formatting
- **Use tabs for indentation** (NOT spaces)
- **Tab width**: 4 characters
- **Never use spaces before tabs**
- **Line length**: Keep below 90 characters when possible (not strict)
- **Source files must end with a newline**
- **Avoid more than one consecutive empty line**

## Braces and Control Structures
- **Opening brace on same line** as function/control statement:
  ```c
  int main(void) {
  
  if (send_func) {
  ```
- **Always use braces** even for single-line blocks:
  ```c
  if (send_func) {
      send_func(data, len);
  }
  ```
- **else on same line** as braces:
  ```c
  } else {
  ```

## Comments
- **Use C99-style single-line comments**: `// comment` (NOT `/* comment */`)
- **Function comments**: Use Doxygen-style when writing function documentation
- **File headers**: Include GPL v3 license header in all source files

## Data Types and Operations
- **Use single precision floats**: `float` instead of `double` (STM32F4 FPU is 32-bit only)
- **Use math functions with 'f' suffix**: `sinf()`, `cosf()`, `powf()`, `fabsf()` etc.
- **Avoid double precision**: Can be 50x slower on STM32F4

## Memory Management
- **Avoid dynamic memory allocation** when possible
- **Prefer static allocation** for predictable RAM usage
- **Use memory pools** when dynamic allocation is necessary

## Naming Conventions
- **Functions**: lowercase with underscores `mc_interface_get_rpm()`
- **Variables**: lowercase with underscores `fault_vec_write`
- **Constants/Defines**: UPPERCASE with underscores `FAULT_VEC_LEN`
- **Struct types**: lowercase with underscores, end with `_struct`

## Compiler Directives
- **Optimization pragma**: Use `#pragma GCC optimize ("Os")` for size optimization
- **Section placement**: Use `__attribute__((section(".text2")))` for specific memory placement

## Error Handling and Safety
- **Compile without warnings**: Code must compile cleanly
- **Use ChibiOS state checker** for debugging random crashes
- **Hardware limits**: Check DISABLE_HW_LIMITS usage carefully