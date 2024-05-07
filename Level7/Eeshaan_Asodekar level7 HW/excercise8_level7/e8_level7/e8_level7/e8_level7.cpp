import mediator; // all orchestration occurs here

int main() {
    Mediator::run();
    return 0;
}

/*
Advantages of Using C++ Modules:
(1) Modular Design and Single Responsibility Principle (SRP):
Modular Design: modularity makes the code more organized and maintainable.
Single Responsibility Principle: simplifies understanding, testing, and maintaining the code; 
each module can be indpenedently implemented and validated

(2) C++ Modules and Header Files Living Side by Side: Modules can coexist with traditional C++ header files,
allowing gradual migration of legacy code to modern module-based structures. This compatibility
helps in transitioning existing projects without rewriting entire codebases.

(3) Support for Information Hiding: reduces the risk of unintended interactions between different parts of a program.

(4) Less Dependencies Than Using Header Files: Modules significantly reduce the dependencies typically introduced by header files.
By compiling modules independently, unnecessary recompilation of unrelated parts of a program due to minor changes is avoided,
which can lead to improved compilation times and reduced build complexity.
*/