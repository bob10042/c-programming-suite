#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
void print_banner(void);
void demo_basic_math(void);
void demo_advanced_math(void);
void demo_compiler_info(void);

void print_banner(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║              ADVANCED C CALCULATOR DEMO                 ║\n");
    printf("║          Demonstrating GCC %d.%d.%d Capabilities          ║\n", 
           __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    printf("║                                                          ║\n");
    printf("║  Features: Math Library, Structures, Function Pointers  ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

void demo_compiler_info(void) {
    printf("🔧 Compiler Information:\n");
    printf("   GCC Version: %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    printf("   Compiled on: %s at %s\n", __DATE__, __TIME__);
    printf("   C Standard: ");
    #if __STDC_VERSION__ >= 201710L
        printf("C18\n");
    #elif __STDC_VERSION__ >= 201112L
        printf("C11\n");
    #elif __STDC_VERSION__ >= 199901L
        printf("C99\n");
    #else
        printf("C90\n");
    #endif
    printf("\n");
}

void demo_basic_math(void) {
    double a = 15.75, b = 4.25;
    
    printf("📊 Basic Mathematical Operations:\n");
    printf("   Numbers: a = %.2f, b = %.2f\n", a, b);
    printf("   Addition:       %.2f + %.2f = %.2f\n", a, b, a + b);
    printf("   Subtraction:    %.2f - %.2f = %.2f\n", a, b, a - b);
    printf("   Multiplication: %.2f × %.2f = %.2f\n", a, b, a * b);
    printf("   Division:       %.2f ÷ %.2f = %.2f\n", a, b, a / b);
    printf("\n");
}

void demo_advanced_math(void) {
    double x = 16.0, y = 2.5;
    
    printf("🧮 Advanced Mathematical Functions:\n");
    printf("   Numbers: x = %.2f, y = %.2f\n", x, y);
    printf("   Square root:    √%.2f = %.4f\n", x, sqrt(x));
    printf("   Power:          %.2f^%.2f = %.4f\n", x, y, pow(x, y));
    printf("   Natural log:    ln(%.2f) = %.4f\n", x, log(x));
    printf("   Base-10 log:    log₁₀(%.2f) = %.4f\n", x, log10(x));
    printf("   Sine:           sin(%.2f) = %.4f\n", y, sin(y));
    printf("   Cosine:         cos(%.2f) = %.4f\n", y, cos(y));
    printf("   Ceiling:        ⌈%.2f⌉ = %.0f\n", y, ceil(y));
    printf("   Floor:          ⌊%.2f⌋ = %.0f\n", y, floor(y));
    printf("\n");
}

// Structure to demonstrate advanced C features
typedef struct {
    char name[50];
    double (*operation)(double, double);
    char symbol[5];
} MathOperation;

double add_func(double a, double b) { return a + b; }
double mul_func(double a, double b) { return a * b; }
double pow_func(double a, double b) { return pow(a, b); }

void demo_function_pointers(void) {
    MathOperation ops[] = {
        {"Addition", add_func, "+"},
        {"Multiplication", mul_func, "×"},
        {"Power", pow_func, "^"}
    };
    
    double x = 8.0, y = 3.0;
    int num_ops = sizeof(ops) / sizeof(ops[0]);
    
    printf("🎯 Function Pointers & Structures Demo:\n");
    printf("   Using x = %.1f, y = %.1f\n", x, y);
    
    for (int i = 0; i < num_ops; i++) {
        double result = ops[i].operation(x, y);
        printf("   %-15s: %.1f %s %.1f = %.4f\n", 
               ops[i].name, x, ops[i].symbol, y, result);
    }
    printf("\n");
}

void demo_memory_and_performance(void) {
    clock_t start, end;
    double cpu_time_used;
    
    printf("⚡ Performance & Memory Demo:\n");
    
    // Measure computation time
    start = clock();
    
    // Perform some calculations
    double sum = 0;
    for (int i = 0; i < 1000000; i++) {
        sum += sqrt(i) * sin(i * 0.001);
    }
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("   Computed 1M sqrt/sin operations\n");
    printf("   Result: %.6f\n", sum);
    printf("   Time taken: %.6f seconds\n", cpu_time_used);
    printf("   Memory usage: ~%zu bytes for operations array\n", 
           sizeof(MathOperation) * 3);
    printf("\n");
}

int main(void) {
    // Seed random number generator
    srand((unsigned int)time(NULL));
    
    print_banner();
    
    printf("🚀 Welcome to the Advanced C Calculator Demo!\n");
    printf("This program demonstrates sophisticated C programming features:\n");
    printf("• Mathematical computations using math.h library\n");
    printf("• Function pointers and structures\n");
    printf("• Performance measurement\n");
    printf("• Modern C standards compliance\n");
    printf("• Unicode output support\n\n");
    
    demo_compiler_info();
    demo_basic_math();
    demo_advanced_math();
    demo_function_pointers();
    demo_memory_and_performance();
    
    printf("✅ All demonstrations completed successfully!\n");
    printf("🎉 GCC %d.%d.%d compilation and execution verified!\n", 
           __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    
    return EXIT_SUCCESS;
}
