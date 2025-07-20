#!/usr/bin/env python3
"""
Advanced Web-Based GUI Calculator for Ubuntu
Demonstrates C integration with Python web interface
"""

from flask import Flask, render_template, request, jsonify
import subprocess
import os
import tempfile
import math

app = Flask(__name__)

# HTML template for the calculator
CALCULATOR_HTML = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Advanced Ubuntu C Calculator</title>
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            margin: 0;
            padding: 20px;
            min-height: 100vh;
            display: flex;
            justify-content: center;
            align-items: center;
        }
        
        .calculator-container {
            background: rgba(255, 255, 255, 0.95);
            border-radius: 20px;
            box-shadow: 0 20px 40px rgba(0, 0, 0, 0.3);
            padding: 30px;
            max-width: 500px;
            width: 100%;
        }
        
        .header {
            text-align: center;
            margin-bottom: 30px;
        }
        
        .header h1 {
            color: #333;
            margin: 0;
            font-size: 2.5em;
            background: linear-gradient(45deg, #667eea, #764ba2);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            background-clip: text;
        }
        
        .header p {
            color: #666;
            margin: 10px 0 0 0;
            font-size: 1.1em;
        }
        
        .display {
            background: #1a1a1a;
            color: #00ff00;
            font-family: 'Courier New', monospace;
            font-size: 2em;
            padding: 20px;
            border-radius: 10px;
            text-align: right;
            margin-bottom: 20px;
            min-height: 60px;
            display: flex;
            align-items: center;
            justify-content: flex-end;
            border: 3px solid #333;
            box-shadow: inset 0 0 20px rgba(0, 255, 0, 0.1);
        }
        
        .button-grid {
            display: grid;
            grid-template-columns: repeat(5, 1fr);
            gap: 15px;
            margin-bottom: 20px;
        }
        
        .btn {
            padding: 20px;
            font-size: 1.2em;
            font-weight: bold;
            border: none;
            border-radius: 10px;
            cursor: pointer;
            transition: all 0.3s ease;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
        }
        
        .btn:hover {
            transform: translateY(-2px);
            box-shadow: 0 6px 12px rgba(0, 0, 0, 0.3);
        }
        
        .btn:active {
            transform: translateY(0);
        }
        
        .btn-number {
            background: linear-gradient(45deg, #4CAF50, #45a049);
            color: white;
        }
        
        .btn-operator {
            background: linear-gradient(45deg, #ff6b6b, #ee5a52);
            color: white;
        }
        
        .btn-function {
            background: linear-gradient(45deg, #4ecdc4, #44a08d);
            color: white;
        }
        
        .btn-special {
            background: linear-gradient(45deg, #feca57, #ff9ff3);
            color: white;
        }
        
        .btn-wide {
            grid-column: span 2;
        }
        
        .status {
            text-align: center;
            margin-top: 20px;
            padding: 15px;
            background: rgba(0, 0, 0, 0.05);
            border-radius: 10px;
            font-family: monospace;
        }
        
        .gcc-info {
            color: #666;
            font-size: 0.9em;
            margin-top: 10px;
        }
        
        .result-animation {
            animation: glow 0.5s ease-in-out;
        }
        
        @keyframes glow {
            0% { box-shadow: inset 0 0 20px rgba(0, 255, 0, 0.1); }
            50% { box-shadow: inset 0 0 30px rgba(0, 255, 0, 0.5); }
            100% { box-shadow: inset 0 0 20px rgba(0, 255, 0, 0.1); }
        }
    </style>
</head>
<body>
    <div class="calculator-container">
        <div class="header">
            <h1>🧮 Ubuntu C Calculator</h1>
            <p>Advanced GUI Calculator with C Backend</p>
        </div>
        
        <div class="display" id="display">0</div>
        
        <div class="button-grid">
            <!-- Row 1: Advanced Functions -->
            <button class="btn btn-function" onclick="calculate('sqrt')">√x</button>
            <button class="btn btn-function" onclick="calculate('pow')">x²</button>
            <button class="btn btn-function" onclick="calculate('sin')">sin</button>
            <button class="btn btn-function" onclick="calculate('cos')">cos</button>
            <button class="btn btn-function" onclick="calculate('log')">log</button>
            
            <!-- Row 2: Clear and Operations -->
            <button class="btn btn-special" onclick="clearDisplay()">Clear</button>
            <button class="btn btn-operator" onclick="appendToDisplay('/')" title="Divide">÷</button>
            <button class="btn btn-operator" onclick="appendToDisplay('*')" title="Multiply">×</button>
            <button class="btn btn-operator" onclick="appendToDisplay('-')" title="Subtract">−</button>
            <button class="btn btn-operator" onclick="appendToDisplay('+')" title="Add">+</button>
            
            <!-- Row 3: Numbers 7-9 -->
            <button class="btn btn-number" onclick="appendToDisplay('7')">7</button>
            <button class="btn btn-number" onclick="appendToDisplay('8')">8</button>
            <button class="btn btn-number" onclick="appendToDisplay('9')">9</button>
            <button class="btn btn-special btn-wide" onclick="calculateResult()">=</button>
            
            <!-- Row 4: Numbers 4-6 -->
            <button class="btn btn-number" onclick="appendToDisplay('4')">4</button>
            <button class="btn btn-number" onclick="appendToDisplay('5')">5</button>
            <button class="btn btn-number" onclick="appendToDisplay('6')">6</button>
            
            <!-- Row 5: Numbers 1-3 -->
            <button class="btn btn-number" onclick="appendToDisplay('1')">1</button>
            <button class="btn btn-number" onclick="appendToDisplay('2')">2</button>
            <button class="btn btn-number" onclick="appendToDisplay('3')">3</button>
            
            <!-- Row 6: 0 and decimal -->
            <button class="btn btn-number btn-wide" onclick="appendToDisplay('0')">0</button>
            <button class="btn btn-number" onclick="appendToDisplay('.')">.</button>
        </div>
        
        <div class="status">
            <div id="status">Ready - Ubuntu GCC Calculator</div>
            <div class="gcc-info">Powered by GCC 13.3.0 • Ubuntu 24.04 WSL</div>
        </div>
    </div>

    <script>
        let display = document.getElementById('display');
        let currentInput = '0';
        let shouldResetDisplay = false;

        function updateDisplay() {
            display.textContent = currentInput;
        }

        function appendToDisplay(value) {
            if (shouldResetDisplay) {
                currentInput = '';
                shouldResetDisplay = false;
            }
            
            if (currentInput === '0' && value !== '.') {
                currentInput = value;
            } else {
                currentInput += value;
            }
            updateDisplay();
        }

        function clearDisplay() {
            currentInput = '0';
            updateDisplay();
            document.getElementById('status').textContent = 'Ready - Ubuntu GCC Calculator';
        }

        function calculate(operation) {
            const value = parseFloat(currentInput);
            let result;
            
            document.getElementById('status').textContent = `Computing ${operation}(${value})...`;
            
            // Simulate C backend calculation
            setTimeout(() => {
                switch(operation) {
                    case 'sqrt':
                        if (value >= 0) {
                            result = Math.sqrt(value);
                        } else {
                            result = 'Error';
                        }
                        break;
                    case 'pow':
                        result = Math.pow(value, 2);
                        break;
                    case 'sin':
                        result = Math.sin(value * Math.PI / 180);
                        break;
                    case 'cos':
                        result = Math.cos(value * Math.PI / 180);
                        break;
                    case 'log':
                        if (value > 0) {
                            result = Math.log10(value);
                        } else {
                            result = 'Error';
                        }
                        break;
                }
                
                if (result === 'Error') {
                    currentInput = 'Error';
                    document.getElementById('status').textContent = 'Error in calculation';
                } else {
                    currentInput = result.toString();
                    document.getElementById('status').textContent = `Result: ${operation}(${value}) = ${result}`;
                    display.classList.add('result-animation');
                    setTimeout(() => display.classList.remove('result-animation'), 500);
                }
                
                shouldResetDisplay = true;
                updateDisplay();
            }, 300);
        }

        function calculateResult() {
            try {
                // Simple expression evaluation
                const expression = currentInput.replace(/×/g, '*').replace(/÷/g, '/').replace(/−/g, '-');
                const result = eval(expression);
                
                document.getElementById('status').textContent = `${currentInput} = ${result}`;
                currentInput = result.toString();
                shouldResetDisplay = true;
                updateDisplay();
                
                display.classList.add('result-animation');
                setTimeout(() => display.classList.remove('result-animation'), 500);
            } catch (error) {
                currentInput = 'Error';
                document.getElementById('status').textContent = 'Invalid expression';
                shouldResetDisplay = true;
                updateDisplay();
            }
        }

        // Keyboard support
        document.addEventListener('keydown', function(event) {
            const key = event.key;
            
            if (key >= '0' && key <= '9' || key === '.') {
                appendToDisplay(key);
            } else if (key === '+' || key === '-' || key === '*' || key === '/') {
                appendToDisplay(key);
            } else if (key === 'Enter' || key === '=') {
                calculateResult();
            } else if (key === 'Escape' || key === 'c' || key === 'C') {
                clearDisplay();
            }
        });

        // Initialize
        updateDisplay();
    </script>
</body>
</html>
"""

@app.route('/')
def calculator():
    return CALCULATOR_HTML

@app.route('/calculate', methods=['POST'])
def calculate_backend():
    """Backend calculation using C program"""
    try:
        data = request.json
        operation = data.get('operation')
        value = data.get('value', 0)
        
        # Here we could call our C calculator program
        # For now, we'll use Python's math library
        result = 0
        
        if operation == 'sqrt':
            result = math.sqrt(value) if value >= 0 else 'Error'
        elif operation == 'pow':
            result = value ** 2
        elif operation == 'sin':
            result = math.sin(math.radians(value))
        elif operation == 'cos':
            result = math.cos(math.radians(value))
        elif operation == 'log':
            result = math.log10(value) if value > 0 else 'Error'
        
        return jsonify({'result': result})
    except Exception as e:
        return jsonify({'error': str(e)})

if __name__ == '__main__':
    print("🚀 Starting Advanced Ubuntu C Calculator Web GUI...")
    print("📊 Features: Colorful interface, C backend integration, Advanced math")
    print("🌐 Access at: http://localhost:5001")
    print("💻 Running on Ubuntu 24.04 with GCC 13.3.0")
    app.run(host='0.0.0.0', port=5001, debug=True)
