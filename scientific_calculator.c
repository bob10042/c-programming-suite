#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <gtk/gtk.h>

// Calculator structure to hold GUI elements and state
typedef struct {
    GtkWidget *window;
    GtkWidget *display;
    GtkWidget *grid;
    char current_input[256];
    double result;
    char operation;
    double operand;
    gboolean new_number;
} Calculator;

// Function prototypes
void on_number_clicked(GtkButton *button, Calculator *calc);
void on_operation_clicked(GtkButton *button, Calculator *calc);
void on_equals_clicked(GtkButton *button, Calculator *calc);
void on_clear_clicked(GtkButton *button, Calculator *calc);
void on_scientific_clicked(GtkButton *button, Calculator *calc);
void update_display(Calculator *calc);
double calculate(double operand1, double operand2, char operation);

// Update the display with current input
void update_display(Calculator *calc) {
    gtk_entry_set_text(GTK_ENTRY(calc->display), calc->current_input);
}

// Handle number button clicks
void on_number_clicked(GtkButton *button, Calculator *calc) {
    const char *label = gtk_button_get_label(button);
    
    if (calc->new_number) {
        strcpy(calc->current_input, label);
        calc->new_number = FALSE;
    } else {
        if (strlen(calc->current_input) < 255) {
            strcat(calc->current_input, label);
        }
    }
    update_display(calc);
}

// Handle operation button clicks (+, -, *, /)
void on_operation_clicked(GtkButton *button, Calculator *calc) {
    const char *label = gtk_button_get_label(button);
    
    if (calc->operation != 0) {
        // Calculate previous operation first
        double current_value = atof(calc->current_input);
        calc->result = calculate(calc->operand, current_value, calc->operation);
        snprintf(calc->current_input, sizeof(calc->current_input), "%.10g", calc->result);
        update_display(calc);
    } else {
        calc->result = atof(calc->current_input);
    }
    
    calc->operand = calc->result;
    calc->operation = label[0];
    calc->new_number = TRUE;
}

// Handle equals button click
void on_equals_clicked(GtkButton *button, Calculator *calc) {
    if (calc->operation != 0) {
        double current_value = atof(calc->current_input);
        calc->result = calculate(calc->operand, current_value, calc->operation);
        snprintf(calc->current_input, sizeof(calc->current_input), "%.10g", calc->result);
        update_display(calc);
        calc->operation = 0;
        calc->new_number = TRUE;
    }
}

// Handle clear button click
void on_clear_clicked(GtkButton *button, Calculator *calc) {
    strcpy(calc->current_input, "0");
    calc->result = 0;
    calc->operand = 0;
    calc->operation = 0;
    calc->new_number = TRUE;
    update_display(calc);
}

// Handle scientific function buttons
void on_scientific_clicked(GtkButton *button, Calculator *calc) {
    const char *label = gtk_button_get_label(button);
    double value = atof(calc->current_input);
    double result = 0;
    
    if (strcmp(label, "sin") == 0) {
        result = sin(value * M_PI / 180.0); // Convert to radians
    } else if (strcmp(label, "cos") == 0) {
        result = cos(value * M_PI / 180.0);
    } else if (strcmp(label, "tan") == 0) {
        result = tan(value * M_PI / 180.0);
    } else if (strcmp(label, "log") == 0) {
        result = log10(value);
    } else if (strcmp(label, "ln") == 0) {
        result = log(value);
    } else if (strcmp(label, "sqrt") == 0) {
        result = sqrt(value);
    } else if (strcmp(label, "x²") == 0) {
        result = value * value;
    } else if (strcmp(label, "1/x") == 0) {
        result = 1.0 / value;
    } else if (strcmp(label, "π") == 0) {
        result = M_PI;
    } else if (strcmp(label, "e") == 0) {
        result = M_E;
    }
    
    snprintf(calc->current_input, sizeof(calc->current_input), "%.10g", result);
    update_display(calc);
    calc->new_number = TRUE;
}

// Perform calculation
double calculate(double operand1, double operand2, char operation) {
    switch (operation) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand2 != 0 ? operand1 / operand2 : 0;
        default: return operand2;
    }
}

// Create a button and add it to the grid
GtkWidget* create_button(const char *label, Calculator *calc, 
                        GCallback callback, int left, int top, int width, int height) {
    GtkWidget *button = gtk_button_new_with_label(label);
    gtk_widget_set_size_request(button, 80, 60);
    gtk_grid_attach(GTK_GRID(calc->grid), button, left, top, width, height);
    g_signal_connect(button, "clicked", callback, calc);
    return button;
}

// Initialize the calculator GUI
void create_calculator(Calculator *calc) {
    // Create main window
    calc->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(calc->window), "Scientific Calculator");
    gtk_window_set_default_size(GTK_WINDOW(calc->window), 400, 500);
    gtk_window_set_resizable(GTK_WINDOW(calc->window), FALSE);
    
    // Create main container
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(calc->window), vbox);
    
    // Create display
    calc->display = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(calc->display), "0");
    gtk_entry_set_alignment(GTK_ENTRY(calc->display), 1.0); // Right align
    gtk_editable_set_editable(GTK_EDITABLE(calc->display), FALSE);
    gtk_widget_set_size_request(calc->display, -1, 50);
    gtk_box_pack_start(GTK_BOX(vbox), calc->display, FALSE, FALSE, 5);
    
    // Create button grid
    calc->grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(calc->grid), 2);
    gtk_grid_set_column_spacing(GTK_GRID(calc->grid), 2);
    gtk_box_pack_start(GTK_BOX(vbox), calc->grid, TRUE, TRUE, 5);
    
    // Scientific function buttons (Row 0)
    create_button("sin", calc, G_CALLBACK(on_scientific_clicked), 0, 0, 1, 1);
    create_button("cos", calc, G_CALLBACK(on_scientific_clicked), 1, 0, 1, 1);
    create_button("tan", calc, G_CALLBACK(on_scientific_clicked), 2, 0, 1, 1);
    create_button("log", calc, G_CALLBACK(on_scientific_clicked), 3, 0, 1, 1);
    create_button("ln", calc, G_CALLBACK(on_scientific_clicked), 4, 0, 1, 1);
    
    // More scientific functions (Row 1)
    create_button("sqrt", calc, G_CALLBACK(on_scientific_clicked), 0, 1, 1, 1);
    create_button("x²", calc, G_CALLBACK(on_scientific_clicked), 1, 1, 1, 1);
    create_button("1/x", calc, G_CALLBACK(on_scientific_clicked), 2, 1, 1, 1);
    create_button("π", calc, G_CALLBACK(on_scientific_clicked), 3, 1, 1, 1);
    create_button("e", calc, G_CALLBACK(on_scientific_clicked), 4, 1, 1, 1);
    
    // Clear and operations (Row 2)
    create_button("C", calc, G_CALLBACK(on_clear_clicked), 0, 2, 1, 1);
    create_button("(", calc, G_CALLBACK(on_number_clicked), 1, 2, 1, 1);
    create_button(")", calc, G_CALLBACK(on_number_clicked), 2, 2, 1, 1);
    create_button("/", calc, G_CALLBACK(on_operation_clicked), 3, 2, 1, 1);
    create_button("*", calc, G_CALLBACK(on_operation_clicked), 4, 2, 1, 1);
    
    // Number buttons and operations (Rows 3-6)
    create_button("7", calc, G_CALLBACK(on_number_clicked), 0, 3, 1, 1);
    create_button("8", calc, G_CALLBACK(on_number_clicked), 1, 3, 1, 1);
    create_button("9", calc, G_CALLBACK(on_number_clicked), 2, 3, 1, 1);
    create_button("-", calc, G_CALLBACK(on_operation_clicked), 3, 3, 1, 1);
    
    create_button("4", calc, G_CALLBACK(on_number_clicked), 0, 4, 1, 1);
    create_button("5", calc, G_CALLBACK(on_number_clicked), 1, 4, 1, 1);
    create_button("6", calc, G_CALLBACK(on_number_clicked), 2, 4, 1, 1);
    create_button("+", calc, G_CALLBACK(on_operation_clicked), 3, 4, 1, 1);
    
    create_button("1", calc, G_CALLBACK(on_number_clicked), 0, 5, 1, 1);
    create_button("2", calc, G_CALLBACK(on_number_clicked), 1, 5, 1, 1);
    create_button("3", calc, G_CALLBACK(on_number_clicked), 2, 5, 1, 1);
    create_button("=", calc, G_CALLBACK(on_equals_clicked), 3, 5, 1, 2);
    
    create_button("0", calc, G_CALLBACK(on_number_clicked), 0, 6, 2, 1);
    create_button(".", calc, G_CALLBACK(on_number_clicked), 2, 6, 1, 1);
    
    // Connect window close signal
    g_signal_connect(calc->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

int main(int argc, char *argv[]) {
    Calculator calc;
    
    // Initialize calculator state
    strcpy(calc.current_input, "0");
    calc.result = 0;
    calc.operand = 0;
    calc.operation = 0;
    calc.new_number = TRUE;
    
    // Initialize GTK
    gtk_init(&argc, &argv);
    
    // Create calculator interface
    create_calculator(&calc);
    
    // Show all widgets
    gtk_widget_show_all(calc.window);
    
    // Start GTK main loop
    gtk_main();
    
    return 0;
}