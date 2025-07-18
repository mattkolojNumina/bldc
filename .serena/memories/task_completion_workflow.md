# VESC Firmware Task Completion Workflow

## Before Starting Development

1. **Read Contributing Guidelines**: Review the CONTRIBUTING file thoroughly
2. **Forum Discussion**: Discuss ideas on the VESC forum (http://vesc-project.com/forum) before coding
3. **Reach Consensus**: Get community feedback on scope and functionality

## Development Process

### Code Quality Requirements
1. **Compile without warnings**: Code must build cleanly
2. **Follow coding style**: Adhere to guidelines in CONTRIBUTING file
3. **Test thoroughly**: Ensure functionality works correctly
4. **Hardware compatibility**: Test across different board configurations

### Testing and Validation
```bash
# Build all hardware variants to catch compatibility issues
cd build_all && ./rebuild_all

# Run unit tests if applicable
make all_ut_run

# Test specific board build
make [your_target_board]
```

## When Task is Complete

### 1. Code Review and Cleanup
- **Review code changes**: Ensure all modifications are intentional
- **Remove debug code**: Clean up any temporary debugging code
- **Check formatting**: Verify code follows style guidelines
- **Test compilation**: Ensure `make [target]` completes without warnings

### 2. Git Commit Preparation  
- **Create clean patches**: Use `git rebase -i` to squash fix-up commits
- **Write descriptive commit messages**: Be specific about technical changes
- **Avoid generic messages**: Don't use "bug fix", "update code", etc.

### 3. Testing Commands to Run
```bash
# Ensure your target builds without warnings
make [your_target_board]

# For broad changes, test multiple hardware variants
cd build_all && ./rebuild_all

# Run relevant unit tests
make all_ut_run

# Test with verbose output to catch issues
make [your_target_board] V=1
```

### 4. Hardware Validation (if applicable)
- **Build and test on actual hardware**: If you have access to VESC hardware
- **Flash firmware**: Use `make [target]_flash` with STLink debugger
- **Test motor control**: Verify functionality with VESC Tool

### 5. Final Checks
- **All files committed**: Ensure no files are left uncommitted
- **No build artifacts**: Don't commit generated files from build/ directory
- **License headers**: Verify GPL headers are present in new files
- **Memory usage**: Check that static memory usage is reasonable

## Submission Process

### 1. Create Pull Request
- **Clean git history**: Squash commits into logical units
- **Descriptive PR description**: Explain what the change does and why
- **Reference forum discussion**: Link to relevant forum posts

### 2. Code Review Response
- **Be patient**: Benjamin may request multiple revisions
- **Don't take criticism personally**: Focus on code quality improvement
- **Address all feedback**: Respond to every review comment

### 3. Post-Merge Follow-up
- **Monitor for issues**: Watch for bug reports related to your changes
- **Be available for questions**: Help with any integration issues

## Important Notes

- **Single precision floats only**: Use `float` not `double` (performance critical)
- **Avoid dynamic allocation**: Prefer static memory allocation
- **ChibiOS compatibility**: Ensure RTOS integration is correct
- **Hardware limits**: Be careful with DISABLE_HW_LIMITS usage
- **Power management**: Consider power consumption impact of changes

## When NOT to Commit
- Build directory contents (`build/`)
- IDE configuration files (unless project-wide)
- Personal debugging code
- Temporary or experimental changes
- Code that breaks existing functionality