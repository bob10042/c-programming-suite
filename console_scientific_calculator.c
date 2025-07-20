#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <ctype.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

// Function prototypes
void display_menu(void);
void basic_calculator(void);
void scientific_calculator(void);
double get_number(const char *prompt);
void clear_input_buffer(void);

int main(void) {
    int choice;
    
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║              SCIENTIFIC CALCULATOR                       ║\n");
    printf("║                Advanced C Calculator                     ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    while (1) {
        display_menu();
        printf("Enter your choice (1-3): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        
        switch (choice) {
            case 1:
                basic_calculator();
                break;
            case 2:
                scientific_calculator();
                break;
            case 3:
                printf("Thank you for using the Scientific Calculator!\n");
                return 0;
            default:
                printf("Invalid choice! Please select 1, 2, or 3.\n");
                break;
        }
        
        printf("\nPress Enter to continue...");
        clear_input_buffer();
        getchar();
    }
    
    return 0;
}

void display_menu(void) {
    printf("\n┌─────────────────────────────────────────────────────────┐\n");
    printf("│                    MAIN MENU                           │\n");
    printf("├─────────────────────────────────────────────────────────┤\n");
    printf("│  1. Basic Calculator (+, -, *, /, ^)                   │\n");
    printf("│  2. Scientific Calculator (sin, cos, log, sqrt, etc.)  │\n");
    printf("│  3. Exit                                                │\n");
    printf("└─────────────────────────────────────────────────────────┘\n");
}

void basic_calculator(void) {
    double num1, num2, result;
    char operation;
    
    printf("\n🔢 BASIC CALCULATOR\n");
    printf("Available operations: +, -, *, /, ^ (power)\n");
    printf("Example: 5 + 3 or 2 ^ 3\n\n");
    
    num1 = get_number("Enter first number: ");
    
    printf("Enter operation (+, -, *, /, ^): ");
    scanf(" %c", &operation);
    
    num2 = get_number("Enter second number: ");
    
    switch (operation) {
        case '+':
            result = num1 + num2;
            printf("%.6g + %.6g = %.6g\n", num1, num2, result);
            break;
        case '-':
            result = num1 - num2;
            printf("%.6g - %.6g = %.6g\n", num1, num2, result);
            break;
        case '*':
            result = num1 * num2;
            printf("%.6g × %.6g = %.6g\n", num1, num2, result);
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("%.6g ÷ %.6g = %.6g\n", num1, num2, result);
            } else {
                printf("Error: Division by zero!\n");
            }
            break;
        case '^':
            result = pow(num1, num2);
            printf("%.6g ^ %.6g = %.6g\n", num1, num2, result);
            break;
        default:
            printf("Invalid operation!\n");
            break;
    }
}

void scientific_calculator(void) {
    int choice;
    double num, result;
    
    printf("\n🧮 SCIENTIFIC CALCULATOR\n");
    printf("┌─────────────────────────────────────────────────────────┐\n");
    printf("│  1. sin(x)     │  2. cos(x)     │  3. tan(x)           │\n");
    printf("│  4. log₁₀(x)   │  5. ln(x)      │  6. sqrt(x)          │\n");
    printf("│  7. x²         │  8. 1/x        │  9. |x|              │\n");
    printf("│ 10. x!         │ 11. e^x        │ 12. 10^x             │\n");
    printf("│ 13. π          │ 14. e          │ 15. deg↔rad          │\n");
    printf("│ 16. Back to main menu                                   │\n");
    printf("└─────────────────────────────────────────────────────────┘\n");
    
    while (1) {
        printf("\nEnter your choice (1-16): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        
        if (choice == 16) {
            break;
        }
        
        if (choice == 13) {
            printf("π = %.10g\n", M_PI);
            continue;
        }
        
        if (choice == 14) {
            printf("e = %.10g\n", M_E);
            continue;
        }
        
        if (choice == 15) {
            double angle = get_number("Enter angle: ");
            printf("%.6g degrees = %.6g radians\n", angle, angle * M_PI / 180.0);
            printf("%.6g radians = %.6g degrees\n", angle, angle * 180.0 / M_PI);
            continue;
        }
        
        num = get_number("Enter number: ");
        
        switch (choice) {
            case 1:
                result = sin(num * M_PI / 180.0);
                printf("sin(%.6g°) = %.6g\n", num, result);
                break;
            case 2:
                result = cos(num * M_PI / 180.0);
                printf("cos(%.6g°) = %.6g\n", num, result);
                break;
            case 3:
                result = tan(num * M_PI / 180.0);
                printf("tan(%.6g°) = %.6g\n", num, result);
                break;
            case 4:
                if (num > 0) {
                    result = log10(num);
                    printf("log₁₀(%.6g) = %.6g\n", num, result);
                } else {
                    printf("Error: Logarithm of non-positive number!\n");
                }
                break;
            case 5:
                if (num > 0) {
                    result = log(num);
                    printf("ln(%.6g) = %.6g\n", num, result);
                } else {
                    printf("Error: Logarithm of non-positive number!\n");
                }
                break;
            case 6:
                if (num >= 0) {
                    result = sqrt(num);
                    printf("√(%.6g) = %.6g\n", num, result);
                } else {
                    printf("Error: Square root of negative number!\n");
                }
                break;
            case 7:
                result = num * num;
                printf("(%.6g)² = %.6g\n", num, result);
                break;
            case 8:
                if (num != 0) {
                    result = 1.0 / num;
                    printf("1/(%.6g) = %.6g\n", num, result);
                } else {
                    printf("Error: Division by zero!\n");
                }
                break;
            case 9:
                result = fabs(num);
                printf("|%.6g| = %.6g\n", num, result);
                break;
            case 10:
                if (num >= 0 && num == floor(num) && num <= 170) {
                    result = 1;
                    for (int i = 2; i <= (int)num; i++) {
                        result *= i;
                    }
                    printf("%.0f! = %.6g\n", num, result);
                } else {
                    printf("Error: Factorial only for non-negative integers ≤ 170!\n");
                }
                break;
            case 11:
                result = exp(num);
                printf("e^(%.6g) = %.6g\n", num, result);
                break;
            case 12:
                result = pow(10, num);
                printf("10^(%.6g) = %.6g\n", num, result);
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    }
}

double get_number(const char *prompt) {
    double num;
    printf("%s", prompt);
    while (scanf("%lf", &num) != 1) {
        printf("Invalid input! Please enter a valid number: ");
        clear_input_buffer();
    }
    return num;
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Clear the input buffer
    }
}