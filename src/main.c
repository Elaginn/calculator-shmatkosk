#include "calculator.h"

int main(int argc, char* argv[]) {
    parse_args(argc, argv);

    char expression[MAX];
    if (!fgets(expression, MAX, stdin))
        return 1;

    double result = evaluateExpression(expression);
    if (float_mode) {
        printf("%lf\n", result);
    } else {
        printf("%d\n", (int)result);
    }
    return 0;
}
