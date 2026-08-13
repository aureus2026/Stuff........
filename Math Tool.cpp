#include <iostream>
#include <cmath>
#include <numeric>
#include <limits>
#include <iomanip>

const double PI = 3.14159265358979323846;

// --- 1. Trigonometry Function ---
int trigFinder() {
    int degrees;
    std::cout << "What degrees: ";
    std::cin >> degrees;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice.\n";
        return 0;
    }

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

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice.\n";
        return 0;
    }

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

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice.\n";
        return 0;
    }

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

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid numeric input.\n";
        return 0;
    }

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

    return 0;
}

// --- 5. Basic Calculator ---
int basicCalculator() {
    double num1, num2;
    char op;

    std::cout << "\n--- Basic Calculator ---\n";
    std::cout << "Enter expression (e.g., 5 + 3 or 10 / 2): ";
    std::cin >> num1 >> op >> num2;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid math expression input.\n";
        return 0;
    }

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

    return 0;
}

// --- 6. Linear System Solver (Algebra) ---
int linearSystemSolver() {
    double a1, b1, c1, a2, b2, c2;
    std::cout << "\n--- 2x2 Linear System Solver ---\n";
    std::cout << "Equation 1: a1*x + b1*y = c1\n";
    std::cout << "Equation 2: a2*x + b2*y = c2\n";
    std::cout << "Enter a1 b1 c1: ";
    std::cin >> a1 >> b1 >> c1;
    std::cout << "Enter a2 b2 c2: ";
    std::cin >> a2 >> b2 >> c2;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid parameters.\n";
        return 0;
    }

    double determinant = a1 * b2 - a2 * b1;
    if (std::abs(determinant) < 1e-12) {
        double detX = c1 * b2 - c2 * b1;
        double detY = a1 * c2 - a2 * c1;
        if (std::abs(detX) < 1e-12 && std::abs(detY) < 1e-12) {
            std::cout << "The linear system has infinitely many solutions (dependent lines).\n";
        } else {
            std::cout << "The linear system has no solution (parallel/inconsistent lines).\n";
        }
    } else {
        double x = (c1 * b2 - c2 * b1) / determinant;
        double y = (a1 * c2 - a2 * c1) / determinant;
        std::cout << "Solutions:\n";
        std::cout << "x = " << x << "\n";
        std::cout << "y = " << y << "\n";
    }

    return 0;
}

// --- 7. Sequences Solver (Algebra) ---
int sequenceSolver() {
    int typeChoice;
    std::cout << "\n--- Sequence Term & Sum Solver ---\n";
    std::cout << "1. Arithmetic Sequence\n";
    std::cout << "2. Geometric Sequence\n";
    std::cout << "Choose sequence type (1-2): ";
    std::cin >> typeChoice;

    if (std::cin.fail() || (typeChoice != 1 && typeChoice != 2)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid selection.\n";
        return 0;
    }

    double a = 0.0;
    int n = 0;
    std::cout << "Enter the first term (a): ";
    std::cin >> a;
    std::cout << "Enter the target term index (n): ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Error: Term index must be a positive integer.\n";
        return 0;
    }

    if (typeChoice == 1) {
        double d = 0.0;
        std::cout << "Enter common difference (d): ";
        std::cin >> d;

        double nthTerm = a + (n - 1) * d;
        double sequenceSum = (n / 2.0) * (2.0 * a + (n - 1) * d);

        std::cout << "Value of term " << n << " = " << nthTerm << "\n";
        std::cout << "Sum of first " << n << " terms = " << sequenceSum << "\n";
    } else {
        double r = 0.0;
        std::cout << "Enter common ratio (r): ";
        std::cin >> r;

        double nthTerm = a * std::pow(r, n - 1);
        double sequenceSum = 0.0;
        if (std::abs(r - 1.0) < 1e-12) {
            sequenceSum = a * n;
        } else {
            sequenceSum = a * (1.0 - std::pow(r, n)) / (1.0 - r);
        }

        std::cout << "Value of term " << n << " = " << nthTerm << "\n";
        std::cout << "Sum of first " << n << " terms = " << sequenceSum << "\n";
    }

    return 0;
}

// --- 8. Numerical Derivative Finder (Calculus) ---
int derivativeFinder() {
    double a, b, c, d, x;
    std::cout << "\n--- Numerical Derivative Finder ---\n";
    std::cout << "Function template: f(x) = a*x^3 + b*x^2 + c*x + d\n";
    std::cout << "Enter coefficient a: ";
    std::cin >> a;
    std::cout << "Enter coefficient b: ";
    std::cin >> b;
    std::cout << "Enter coefficient c: ";
    std::cin >> c;
    std::cout << "Enter constant d: ";
    std::cin >> d;
    std::cout << "Enter point x to evaluate f'(x): ";
    std::cin >> x;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid numeric parameters.\n";
        return 0;
    }

    double h = 1e-5; 
    auto f = [=](double val) { return a * std::pow(val, 3) + b * std::pow(val, 2) + c * val + d; };

    double derivativeApprox = (f(x + h) - f(x - h)) / (2.0 * h);
    double exactAnalytical = 3.0 * a * std::pow(x, 2) + 2.0 * b * x + c;

    std::cout << "Symmetric Difference Approximation f'(" << x << ") ~ " << derivativeApprox << "\n";
    std::cout << "Exact Analytical Derivative f'(" << x << ") = " << exactAnalytical << "\n";
    return 0;
}

// --- 9. Numerical Definite Integral Solver (Calculus) ---
int integralSolver() {
    double a, b, c, d, lowerLim, upperLim;
    int intervals;

    std::cout << "\n--- Numerical Definite Integral Solver ---\n";
    std::cout << "Function template: f(x) = a*x^3 + b*x^2 + c*x + d\n";
    std::cout << "Enter coefficient a: ";
    std::cin >> a;
    std::cout << "Enter coefficient b: ";
    std::cin >> b;
    std::cout << "Enter coefficient c: ";
    std::cin >> c;
    std::cout << "Enter constant d: ";
    std::cin >> d;
    std::cout << "Enter integration lower bound: ";
    std::cin >> lowerLim;
    std::cout << "Enter integration upper bound: ";
    std::cin >> upperLim;
    std::cout << "Enter partitioning intervals (e.g., 10000): ";
    std::cin >> intervals;

    if (std::cin.fail() || intervals <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid interval partitioning constraints.\n";
        return 0;
    }

    double h = (upperLim - lowerLim) / intervals;
    auto f = [=](double val) { return a * std::pow(val, 3) + b * std::pow(val, 2) + c * val + d; };

    double integralSum = 0.5 * (f(lowerLim) + f(upperLim));
    for (int i = 1; i < intervals; ++i) {
        integralSum += f(lowerLim + i * h);
    }
    double totalArea = integralSum * h;

    std::cout << "Definite Integral evaluated over [" << lowerLim << ", " << upperLim << "] ~ " << totalArea << "\n";
    return 0;
}

// --- Main Menu System ---
int main() {
    int modeChoice = 0;
    bool running = true;

    std::cout << std::fixed << std::setprecision(6);

    while (running) {
        std::cout << "\n=== Ultimate Math Tool ===\n";
        std::cout << "Copyright 2026\n";
        std::cout << "1. Trigonometry Finder\n";
        std::cout << "2. 3D Shape Volume Finder\n";
        std::cout << "3. Pythagorean Theorem Solver (+ Area/Perimeter)\n";
        std::cout << "4. Quadratic Formula Solver\n";
        std::cout << "5. Basic Calculator\n";
        std::cout << "6. Algebra: 2x2 Linear System Solver\n";
        std::cout << "7. Algebra: Arithmetic & Geometric Sequences\n";
        std::cout << "8. Calculus: Numerical Derivative Finder\n";
        std::cout << "9. Calculus: Definite Integral Solver\n";
        std::cout << "10. Exit Application\n";
        std::cout << "Choose an option (1-10): ";
        std::cin >> modeChoice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid menu item choice. Please input an integer from 1 to 10.\n";
            continue;
        }

        switch (modeChoice) {
            case 1: trigFinder(); break;
            case 2: volumeFinder(); break;
            case 3: pythagoreanFinder(); break;
            case 4: quadraticFinder(); break;
            case 5: basicCalculator(); break;
            case 6: linearSystemSolver(); break;
            case 7: sequenceSolver(); break;
            case 8: derivativeFinder(); break;
            case 9: integralSolver(); break;
            case 10:
                std::cout << "Thank you for utilizing the Ultimate Math Tool. Goodbye!\n";
                running = false;
                break;
            default:
                std::cout << "Option not recognized. Please choose from options 1-10.\n";
                break;
        }
    }
    return 0;
}
