#include <iostream>
#include <cmath>
#include <numeric>
#include <limits>

const double PI = 3.14159265358979323846;

// --- 1. Trigonometry Function ---
int trigFinder() {
    int degrees;
    std::cout << "What degrees: ";
    std::cin >> degrees;

    double radians = degrees * (PI / 180.0);
    int divisor = std::gcd(degrees, 180);
    int numerator = degrees / divisor;
    int denominator = 180 / divisor;

    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }

    std::cout << "radians = " << radians << "\n";
    std::cout << "radians in terms of pi = " << numerator << "pi/" << denominator << "\n";

    double sin_val = std::sin(radians);
    double cos_val = std::cos(radians);

    if (std::abs(sin_val) < 1e-15) sin_val = 0.0;
    if (std::abs(cos_val) < 1e-15) cos_val = 0.0;

    std::cout << "sine = " << sin_val << "\n";
    std::cout << "cosine = " << cos_val << "\n";

    if (cos_val == 0.0) {
        std::cout << "tangent = undefined\n";
    } else {
        std::cout << "tangent = " << (sin_val / cos_val) << "\n";
    }

    std::cout << "Created by Aureus\n"; // Updated signature
    return 0;
}

// --- 2. Volume Calculator Function ---
int volumeFinder() {
    int shapeChoice;
    double radius = 0.0, height = 0.0, volume = 0.0, width = 0.0, length = 0.0;

    std::cout << "\n--- Volume Calculator ---\n";
    std::cout << "1. Cylinder\n";
    std::cout << "2. Cone\n";
    std::cout << "3. Sphere\n";
    std::cout << "4. Cube\n";
    std::cout << "5. Pyramid\n";
    std::cout << "Choose a shape (1-5): ";
    std::cin >> shapeChoice;

    switch (shapeChoice) {
        case 1:
            std::cout << "Enter radius: ";
            std::cin >> radius;
            std::cout << "Enter height: ";
            std::cin >> height;
            volume = PI * std::pow(radius, 2) * height;
            std::cout << "Cylinder Volume = " << volume << "\n";
            break;

        case 2:
            std::cout << "Enter radius: ";
            std::cin >> radius;
            std::cout << "Enter height: ";
            std::cin >> height;
            volume = (1.0 / 3.0) * PI * std::pow(radius, 2) * height;
            std::cout << "Cone Volume = " << volume << "\n";
            break;

        case 3:
            std::cout << "Enter radius: ";
            std::cin >> radius;
            volume = (4.0 / 3.0) * PI * std::pow(radius, 3);
            std::cout << "Sphere Volume = " << volume << "\n";
            break;

        case 5:
            std::cout << "Enter length: ";
            std::cin >> length;
            std::cout << "Enter width: ";
            std::cin >> width;
            std::cout << "Enter height: ";
            std::cin >> height;
            volume = (length * width * height) / 3.0;
            std::cout << "Pyramid Volume = " << volume << "\n";
            break;

        case 4:
            std::cout << "Enter a number....it doesnt matter its getting cubed anyway: ";
            std::cin >> length;
            volume = length * length * length;
            std::cout << "Volume = " << volume << "\n";
            break;

        default:
            std::cout << "So.........you just didn't follow directions and it crashed, you idiot\n";
            break;
    }

    std::cout << "Created by Aureus\n"; // Updated signature
    return 0;
}

// --- 3. Pythagorean Theorem Solver ---
int pythagoreanFinder() {
    int missingSideChoice;
    double a = 0.0, b = 0.0, c = 0.0;

    std::cout << "\n--- Pythagorean Theorem Solver (a^2 + b^2 = c^2) ---\n";
    std::cout << "1. Solve for hypotenuse (c)\n";
    std::cout << "2. Solve for leg (a)\n";
    std::cout << "3. Solve for leg (b)\n";
    std::cout << "Which side is missing? (1-3): ";
    std::cin >> missingSideChoice;

    switch (missingSideChoice) {
        case 1:
            std::cout << "Enter side a: ";
            std::cin >> a;
            std::cout << "Enter side b: ";
            std::cin >> b;
            c = std::sqrt(std::pow(a, 2) + std::pow(b, 2));
            std::cout << "Hypotenuse (c) = " << c << "\n";
            break;

        case 2:
            std::cout << "Enter hypotenuse (c): ";
            std::cin >> c;
            std::cout << "Enter side b: ";
            std::cin >> b;
            if (c <= b) {
                std::cout << "Error: Hypotenuse must be longer than the legs!\n";
                return 0;
            }
            a = std::sqrt(std::pow(c, 2) - std::pow(b, 2));
            std::cout << "Leg (a) = " << a << "\n";
            break;

        case 3:
            std::cout << "Enter hypotenuse (c): ";
            std::cin >> c;
            std::cout << "Enter side a: ";
            std::cin >> a;
            if (c <= a) {
                std::cout << "Error: Hypotenuse must be longer than the legs!\n";
                return 0;
            }
            b = std::sqrt(std::pow(c, 2) - std::pow(a, 2));
            std::cout << "Leg (b) = " << b << "\n";
            break;

        default:
            std::cout << "That option doesn't exist on this triangle.\n";
            return 0;
    }

    double area = 0.5 * a * b;
    double perimeter = a + b + c;

    std::cout << "Triangle Perimeter = " << perimeter << "\n";
    std::cout << "Triangle Area = " << area << "\n";
    std::cout << "Created by Aureus\n"; // Updated signature
    return 0;
}

// --- 4. Quadratic Formula Solver ---
int quadraticFinder() {
    double a, b, c;
    std::cout << "\n--- Quadratic Formula Solver (ax^2 + bx + c = 0) ---\n";
    std::cout << "Enter a: ";
    std::cin >> a;
    std::cout << "Enter b: ";
    std::cin >> b;
    std::cout << "Enter c: ";
    std::cin >> c;

    if (a == 0) {
        std::cout << "Error: 'a' cannot be 0 in a quadratic equation.\n";
        return 0;
    }

    double discriminant = std::pow(b, 2) - (4.0 * a * c);

    if (discriminant > 0) {
        double root1 = (-b + std::sqrt(discriminant)) / (2.0 * a);
        double root2 = (-b - std::sqrt(discriminant)) / (2.0 * a);
        std::cout << "Two real roots:\n";
        std::cout << "x1 = " << root1 << "\n";
        std::cout << "x2 = " << root2 << "\n";
    }
    else if (discriminant == 0) {
        double root = -b / (2.0 * a);
        std::cout << "One real root:\n";
        std::cout << "x = " << root << "\n";
    }
    else {
        double realPart = -b / (2.0 * a);
        double imaginaryPart = std::sqrt(-discriminant) / (2.0 * a);
        std::cout << "Two complex roots:\n";
        std::cout << "x1 = " << realPart << " + " << imaginaryPart << "i\n";
        std::cout << "x2 = " << realPart << " - " << imaginaryPart << "i\n";
    }

    std::cout << "Created by Aureus\n"; // Updated signature
    return 0;
}

// --- 5. Basic Calculator ---
int basicCalculator() {
    double num1, num2;
    char op;

    std::cout << "\n--- Basic Calculator ---\n";
    std::cout << "Enter expression (e.g., 5 + 3 or 10 / 2): ";
    std::cin >> num1 >> op >> num2;

    switch (op) {
        case '+':
            std::cout << "Result = " << (num1 + num2) << "\n";
            break;
        case '-':
            std::cout << "Result = " << (num1 - num2) << "\n";
            break;
        case '*':
            std::cout << "Result = " << (num1 * num2) << "\n";
            break;
        case '/':
            if (num2 == 0) {
                std::cout << "Error: Cannot divide by zero!\n";
            } else {
                std::cout << "Result = " << (num1 / num2) << "\n";
            }
            break;
        default:
            std::cout << "Invalid operator! Use +, -, *, or /.\n";
            break;
    }

    std::cout << "Created by Aureus\n"; // Updated signature
    return 0;
}

// --- Main Menu System ---
int main() {
    int modeChoice = 0;
    bool running = true;

    while (running) {
        std::cout << "\n=== Aureus' Ultimate Math Tool ===\n";
        std::cout << "Copyright 2026\n";
        std::cout << "1. Trigonometry Finder\n";
        std::cout << "2. 3D Shape Volume Finder\n";
        std::cout << "3. Pythagorean Theorem Solver (+ Area/Perimeter)\n";
        std::cout << "4. Quadratic Formula Solver\n";
        std::cout << "5. Basic Calculator\n";
        std::cout << "6. Exit Program\n";
        std::cout << "Select a mode (1-6): ";
        
        if (!(std::cin >> modeChoice)) {
            std::cout << "Invalid input! Please enter a valid menu number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (modeChoice) {
            case 1:
                trigFinder();
                break;
            case 2:
                volumeFinder();
                break;
            case 3:
                pythagoreanFinder();
                break;
            case 4:
                quadraticFinder();
                break;
            case 5:
                basicCalculator();
                break;
            case 6:
                std::cout << "Exiting Aureus' Ultimate Math Tool. Goodbye!\n";
                running = false;
                break;
            default:
                std::cout << "Option out of range. Choose a setting between 1 and 6.\n";
                break;
        }
    }
    return 0;
}


