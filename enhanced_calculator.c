#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

// Define mathematical constants if not available
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif
#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880
#endif

// ANSI Color codes for better visibility
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BG_BLUE "\033[44m"
#define BG_GREEN "\033[42m"

// Function prototypes
void print_colored_banner(void);
void print_colored_menu(void);
void demo_basic_operations(void);
void demo_advanced_functions(void);
void demo_scientific_functions(void);
void interactive_calculator(void);
void clear_screen(void);
void wait_for_enter(void);

// Mathematical operation functions
double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) { return (b != 0) ? a / b : 0; }

void clear_screen(void) {
    printf("\033[2J\033[H");
}

void wait_for_enter(void) {
    printf(CYAN "\nPress Enter to continue..." RESET);
    getchar();
    getchar(); // Clear buffer
}

void print_colored_banner(void) {
    clear_screen();
    printf(BOLD BG_BLUE WHITE);
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                    ENHANCED C CALCULATOR v3.0                   ║\n");
    printf("║              Demonstrating Ubuntu GCC %d.%d.%d Capabilities        ║\n", 
           __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    printf("║                                                                  ║\n");
    printf("║    Features: Colors, Advanced Math, Performance, Interactivity  ║\n");
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
    printf(RESET "\n");
}

void print_colored_menu(void) {
    printf(BOLD CYAN "┌─────────────────────────────────────────────────────────────────┐\n");
    printf("│                        CALCULATOR MENU                         │\n");
    printf("├─────────────────────────────────────────────────────────────────┤\n" RESET);
    
    printf(GREEN "│ 1. " YELLOW "Basic Operations Demo    " WHITE "- Addition, Subtraction, etc.     │\n");
    printf(GREEN "│ 2. " YELLOW "Advanced Functions Demo  " WHITE "- Powers, Roots, Logarithms       │\n");
    printf(GREEN "│ 3. " YELLOW "Scientific Functions     " WHITE "- Trigonometry, Complex Math      │\n");
    printf(GREEN "│ 4. " YELLOW "Interactive Calculator   " WHITE "- Real-time calculations          │\n");
    printf(GREEN "│ 5. " RED "Exit                     " WHITE "- Quit the program                │\n");
    
    printf(BOLD CYAN "└─────────────────────────────────────────────────────────────────┘\n" RESET);
}

void demo_basic_operations(void) {
    clear_screen();
    printf(BOLD BG_GREEN WHITE " BASIC OPERATIONS DEMONSTRATION " RESET "\n\n");
    
    double a = 25.75, b = 8.25;
    
    printf(BLUE "Input Numbers: " BOLD "a = %.2f, b = %.2f\n\n" RESET, a, b);
    
    printf(YELLOW "➤ Addition:       " WHITE "%.2f + %.2f = " GREEN "%.2f\n", a, b, add(a, b));
    printf(YELLOW "➤ Subtraction:    " WHITE "%.2f - %.2f = " GREEN "%.2f\n", a, b, subtract(a, b));
    printf(YELLOW "➤ Multiplication: " WHITE "%.2f × %.2f = " GREEN "%.2f\n", a, b, multiply(a, b));
    printf(YELLOW "➤ Division:       " WHITE "%.2f ÷ %.2f = " GREEN "%.2f\n", a, b, divide(a, b));
    
    printf(CYAN "\n📊 Additional Information:\n");
    printf(WHITE "   Integer division: " MAGENTA "%d\n", (int)(a / b));
    printf(WHITE "   Remainder:        " MAGENTA "%.3f\n", fmod(a, b));
    printf(WHITE "   Average:          " MAGENTA "%.3f\n", (a + b) / 2);
    
    printf(RESET);
    wait_for_enter();
}

void demo_advanced_functions(void) {
    clear_screen();
    printf(BOLD BG_GREEN WHITE " ADVANCED MATHEMATICAL FUNCTIONS " RESET "\n\n");
    
    double x = 64.0, y = 3.0;
    
    printf(BLUE "Input Numbers: " BOLD "x = %.1f, y = %.1f\n\n" RESET, x, y);
    
    printf(YELLOW "➤ Square Root:    " WHITE "√%.1f = " GREEN "%.4f\n", x, sqrt(x));
    printf(YELLOW "➤ Cube Root:      " WHITE "∛%.1f = " GREEN "%.4f\n", x, cbrt(x));
    printf(YELLOW "➤ Power:          " WHITE "%.1f^%.1f = " GREEN "%.2f\n", x, y, pow(x, y));
    printf(YELLOW "➤ Natural Log:    " WHITE "ln(%.1f) = " GREEN "%.4f\n", x, log(x));
    printf(YELLOW "➤ Base-10 Log:    " WHITE "log₁₀(%.1f) = " GREEN "%.4f\n", x, log10(x));
    printf(YELLOW "➤ Base-2 Log:     " WHITE "log₂(%.1f) = " GREEN "%.4f\n", x, log2(x));
    printf(YELLOW "➤ Exponential:    " WHITE "e^%.1f = " GREEN "%.2f\n", y, exp(y));
    
    printf(CYAN "\n🔬 Mathematical Constants:\n");
    printf(WHITE "   π (Pi):       " MAGENTA "%.10f\n", M_PI);
    printf(WHITE "   e (Euler):    " MAGENTA "%.10f\n", M_E);
    printf(WHITE "   √2:           " MAGENTA "%.10f\n", M_SQRT2);
    
    printf(RESET);
    wait_for_enter();
}

void demo_scientific_functions(void) {
    clear_screen();
    printf(BOLD BG_GREEN WHITE " SCIENTIFIC & TRIGONOMETRIC FUNCTIONS " RESET "\n\n");
    
    double angle_deg = 45.0;
    double angle_rad = angle_deg * M_PI / 180.0;
    
    printf(BLUE "Angle: " BOLD "%.1f° (%.4f radians)\n\n" RESET, angle_deg, angle_rad);
    
    printf(YELLOW "➤ Sine:          " WHITE "sin(%.1f°) = " GREEN "%.6f\n", angle_deg, sin(angle_rad));
    printf(YELLOW "➤ Cosine:        " WHITE "cos(%.1f°) = " GREEN "%.6f\n", angle_deg, cos(angle_rad));
    printf(YELLOW "➤ Tangent:       " WHITE "tan(%.1f°) = " GREEN "%.6f\n", angle_deg, tan(angle_rad));
    printf(YELLOW "➤ Arcsine:       " WHITE "asin(0.707) = " GREEN "%.1f°\n", asin(0.707) * 180.0 / M_PI);
    printf(YELLOW "➤ Arccosine:     " WHITE "acos(0.707) = " GREEN "%.1f°\n", acos(0.707) * 180.0 / M_PI);
    printf(YELLOW "➤ Arctangent:    " WHITE "atan(1.0) = " GREEN "%.1f°\n", atan(1.0) * 180.0 / M_PI);
    
    printf(CYAN "\n🧮 Hyperbolic Functions:\n");
    printf(YELLOW "➤ Hyperbolic Sin: " WHITE "sinh(1.0) = " GREEN "%.6f\n", sinh(1.0));
    printf(YELLOW "➤ Hyperbolic Cos: " WHITE "cosh(1.0) = " GREEN "%.6f\n", cosh(1.0));
    printf(YELLOW "➤ Hyperbolic Tan: " WHITE "tanh(1.0) = " GREEN "%.6f\n", tanh(1.0));
    
    printf(CYAN "\n⚡ Performance Test:\n");
    clock_t start = clock();
    double sum = 0;
    for (int i = 0; i < 1000000; i++) {
        sum += sin(i * 0.001) * cos(i * 0.001);
    }
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf(WHITE "   Computed 1M trig operations in " MAGENTA "%.6f seconds\n", time_taken);
    printf(WHITE "   Result: " MAGENTA "%.6f\n", sum);
    
    printf(RESET);
    wait_for_enter();
}

void interactive_calculator(void) {
    clear_screen();
    printf(BOLD BG_GREEN WHITE " INTERACTIVE CALCULATOR MODE " RESET "\n\n");
    
    printf(CYAN "Available operations:\n");
    printf(GREEN "  +, -, *, /     " WHITE "- Basic arithmetic\n");
    printf(GREEN "  sqrt(x)        " WHITE "- Square root\n");
    printf(GREEN "  pow(x,y)       " WHITE "- x to the power of y\n");
    printf(GREEN "  sin(x), cos(x) " WHITE "- Trigonometric (degrees)\n");
    printf(GREEN "  log(x)         " WHITE "- Natural logarithm\n");
    printf(GREEN "  'quit'         " WHITE "- Exit calculator\n\n");
    
    char input[100];
    double num1, num2, result;
    char operation[20];
    
    while (1) {
        printf(BOLD YELLOW "calc> " RESET);
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "quit") == 0) {
            printf(GREEN "Goodbye!\n" RESET);
            break;
        }
        
        // Parse basic operations
        if (sscanf(input, "%lf %s %lf", &num1, operation, &num2) == 3) {
            if (strcmp(operation, "+") == 0) {
                result = num1 + num2;
                printf(GREEN "Result: %.6f\n" RESET, result);
            } else if (strcmp(operation, "-") == 0) {
                result = num1 - num2;
                printf(GREEN "Result: %.6f\n" RESET, result);
            } else if (strcmp(operation, "*") == 0) {
                result = num1 * num2;
                printf(GREEN "Result: %.6f\n" RESET, result);
            } else if (strcmp(operation, "/") == 0) {
                if (num2 != 0) {
                    result = num1 / num2;
                    printf(GREEN "Result: %.6f\n" RESET, result);
                } else {
                    printf(RED "Error: Division by zero!\n" RESET);
                }
            } else {
                printf(RED "Unknown operation: %s\n" RESET, operation);
            }
        }
        // Parse function calls
        else if (sscanf(input, "sqrt(%lf)", &num1) == 1) {
            if (num1 >= 0) {
                result = sqrt(num1);
                printf(GREEN "Result: %.6f\n" RESET, result);
            } else {
                printf(RED "Error: Cannot take square root of negative number!\n" RESET);
            }
        }
        else if (sscanf(input, "pow(%lf,%lf)", &num1, &num2) == 2) {
            result = pow(num1, num2);
            printf(GREEN "Result: %.6f\n" RESET, result);
        }
        else if (sscanf(input, "sin(%lf)", &num1) == 1) {
            result = sin(num1 * M_PI / 180.0);
            printf(GREEN "Result: %.6f\n" RESET, result);
        }
        else if (sscanf(input, "cos(%lf)", &num1) == 1) {
            result = cos(num1 * M_PI / 180.0);
            printf(GREEN "Result: %.6f\n" RESET, result);
        }
        else if (sscanf(input, "log(%lf)", &num1) == 1) {
            if (num1 > 0) {
                result = log(num1);
                printf(GREEN "Result: %.6f\n" RESET, result);
            } else {
                printf(RED "Error: Logarithm of non-positive number!\n" RESET);
            }
        }
        else {
            printf(RED "Invalid input. Try: '5 + 3' or 'sqrt(16)' or 'quit'\n" RESET);
        }
    }
}

int main(void) {
    int choice;
    
    while (1) {
        print_colored_banner();
        
        printf(BOLD WHITE "🚀 Welcome to the Enhanced Ubuntu C Calculator!\n");
        printf("This program demonstrates:\n");
        printf(GREEN "• " WHITE "Colorized terminal output with ANSI codes\n");
        printf(GREEN "• " WHITE "Advanced mathematical functions\n");
        printf(GREEN "• " WHITE "Interactive calculation mode\n");
        printf(GREEN "• " WHITE "Performance benchmarking\n");
        printf(GREEN "• " WHITE "Unicode symbols and formatting\n");
        printf(GREEN "• " WHITE "GCC %d.%d.%d compilation on Ubuntu 24.04\n\n" RESET, 
               __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
        
        print_colored_menu();
        
        printf(BOLD CYAN "\nEnter your choice (1-5): " RESET);
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                demo_basic_operations();
                break;
            case 2:
                demo_advanced_functions();
                break;
            case 3:
                demo_scientific_functions();
                break;
            case 4:
                interactive_calculator();
                break;
            case 5:
                clear_screen();
                printf(BOLD GREEN "🎉 Thank you for using Enhanced C Calculator!\n");
                printf(WHITE "Compiled with GCC %d.%d.%d on %s at %s\n", 
                       __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__, __DATE__, __TIME__);
                printf("✨ Ubuntu WSL environment successfully demonstrated!\n" RESET);
                return 0;
            default:
                printf(RED "Invalid choice! Please enter 1-5.\n" RESET);
                wait_for_enter();
        }
    }
    
    return 0;
}
