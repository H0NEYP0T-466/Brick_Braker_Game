# 🤝 Contributing to Brick Braker Game

First off, thank you for considering contributing to Brick Braker Game! 🎉 It's people like you that make this project a great tool for everyone.

## 📋 Table of Contents

- [🔄 How to Contribute](#-how-to-contribute)
- [🍴 Getting Started](#-getting-started)
- [💻 Development Setup](#-development-setup)
- [📝 Code Style Guidelines](#-code-style-guidelines)
- [🐛 Reporting Bugs](#-reporting-bugs)
- [✨ Suggesting Features](#-suggesting-features)
- [🧪 Testing](#-testing)
- [📖 Documentation](#-documentation)
- [🎯 Pull Request Process](#-pull-request-process)

## 🔄 How to Contribute

There are many ways to contribute to this project:

- 🐛 **Report bugs** and help us improve the game
- ✨ **Suggest new features** or enhancements
- 💻 **Submit code** improvements and fixes
- 📖 **Improve documentation** and help others understand the project
- 🎨 **Enhance graphics** and visual elements
- 🧪 **Write tests** to ensure code quality

## 🍴 Getting Started

1. **Fork the repository** on GitHub
2. **Clone your fork** locally:
   ```bash
   git clone https://github.com/YOUR_USERNAME/Brick_Braker_Game.git
   cd Brick_Braker_Game
   ```
3. **Create a feature branch**:
   ```bash
   git checkout -b feature/your-feature-name
   ```
4. **Make your changes** and commit them
5. **Push to your fork** and submit a pull request

## 💻 Development Setup

### Prerequisites

- **Windows OS** (required for current implementation)
- **C++ Compiler** (GCC, MinGW, or Visual Studio)
- **Git** for version control

### Building the Project

```bash
# Clone and navigate to project
git clone https://github.com/H0NEYP0T-466/Brick_Braker_Game.git
cd Brick_Braker_Game

# Compile the game
g++ -o brick_breaker game.cpp

# Test the build
./brick_breaker.exe
```

## 📝 Code Style Guidelines

### C++ Coding Standards

- **Indentation**: Use 4 spaces (no tabs)
- **Naming Conventions**:
  - Variables: `camelCase` (e.g., `playerScore`, `ballSpeed`)
  - Functions: `camelCase` (e.g., `movePlayer()`, `checkCollision()`)
  - Classes: `PascalCase` (e.g., `Ball`, `Paddle`)
  - Constants: `UPPER_CASE` (e.g., `SCREEN_WIDTH`, `MAX_LIVES`)

### Code Structure

- **Comments**: Use clear, descriptive comments for complex logic
- **Functions**: Keep functions focused and under 50 lines when possible
- **Error Handling**: Include proper error checking for file operations
- **Memory Management**: Ensure proper resource cleanup

### Example Code Style

```cpp
// Good: Clear function with proper naming
void movePlayer(int direction) {
    if (direction == LEFT && paddle.x > 0) {
        paddle.x -= paddle.speed;
    }
}

// Good: Descriptive variable names
int playerCurrentScore = 0;
bool gameIsRunning = true;
```

## 🐛 Reporting Bugs

When reporting bugs, please include:

### Bug Report Template

```markdown
**Bug Description**
A clear and concise description of what the bug is.

**Steps to Reproduce**
1. Go to '...'
2. Click on '....'
3. Scroll down to '....'
4. See error

**Expected Behavior**
What you expected to happen.

**Screenshots**
If applicable, add screenshots to help explain your problem.

**Environment:**
 - OS: [e.g. Windows 10]
 - Compiler: [e.g. GCC 9.3.0]
 - Game Version: [e.g. latest commit hash]

**Additional Context**
Add any other context about the problem here.
```

## ✨ Suggesting Features

We love feature suggestions! When suggesting a new feature:

### Feature Request Template

```markdown
**Feature Description**
A clear and concise description of what you want to happen.

**Problem Statement**
What problem does this feature solve?

**Proposed Solution**
Describe the solution you'd like to see.

**Alternative Solutions**
Describe any alternative solutions you've considered.

**Additional Context**
Add any other context, mockups, or examples about the feature.
```

## 🧪 Testing

### Manual Testing

Before submitting a pull request, please test:

- ✅ **Game starts** without errors
- ✅ **All menus** work correctly
- ✅ **Gameplay mechanics** function properly
- ✅ **Score saving/loading** works
- ✅ **Leaderboard** displays correctly
- ✅ **Settings** apply correctly

### Test Cases to Consider

1. **Game Flow**: Start game → Play → Game over → Save score
2. **Controls**: Test both WASD and arrow keys
3. **Levels**: Complete a level and progress to next
4. **Edge Cases**: Ball going off-screen, paddle at boundaries
5. **File Operations**: Save/load player data

## 📖 Documentation

### Documentation Standards

- **Code Comments**: Explain complex algorithms and game logic
- **README Updates**: Update README.md if adding new features
- **Inline Documentation**: Use clear variable and function names
- **Architecture Notes**: Document major structural changes

### Documentation Checklist

- [ ] Updated README.md if applicable
- [ ] Added comments for new functions
- [ ] Updated feature list if adding functionality
- [ ] Documented any new dependencies

## 🎯 Pull Request Process

### Before Submitting

1. ✅ **Test your changes** thoroughly
2. ✅ **Update documentation** if needed
3. ✅ **Follow code style** guidelines
4. ✅ **Write clear commit messages**

### Pull Request Template

```markdown
**Description**
Brief description of changes made.

**Type of Change**
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

**Testing**
- [ ] Tested on Windows
- [ ] Manual testing completed
- [ ] No new bugs introduced

**Checklist**
- [ ] Code follows style guidelines
- [ ] Self-review completed
- [ ] Documentation updated
- [ ] Tested thoroughly
```

### Commit Message Format

```
type(scope): description

Examples:
feat(gameplay): add power-up system
fix(collision): resolve ball sticking to paddle
docs(readme): update installation instructions
style(formatting): fix indentation in game.cpp
```

## 🏷️ Issue Labels

We use the following labels to organize issues:

- `bug` 🐛 - Something isn't working
- `enhancement` ✨ - New feature or request
- `documentation` 📖 - Improvements or additions to documentation
- `good first issue` 👋 - Good for newcomers
- `help wanted` 🆘 - Extra attention is needed
- `question` ❓ - Further information is requested

## 🌟 Recognition

Contributors will be recognized in:

- 🏆 **README acknowledgements** section
- 📝 **Git commit history**
- 🎉 **Release notes** for major contributions

## 📞 Getting Help

- 📧 **GitHub Issues**: For bugs and feature requests
- 💬 **Discussions**: For general questions and ideas
- 📖 **Documentation**: Check README.md for setup help

## 📋 Code of Conduct

### Our Standards

- ✅ **Be respectful** and inclusive
- ✅ **Provide constructive feedback**
- ✅ **Focus on the code**, not the person
- ✅ **Help others** learn and grow

### Unacceptable Behavior

- ❌ Harassment or discrimination
- ❌ Trolling or insulting comments
- ❌ Publishing private information
- ❌ Unprofessional conduct

---

## 🙏 Thank You!

Thank you for taking the time to contribute! Every contribution helps make Brick Braker Game better for everyone. 

Happy coding! 🎮✨