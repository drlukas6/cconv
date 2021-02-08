#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HEX_LEN 6

static const char *HEX_VALUES = "0123456789ABCDEF";

short validateRGBInput(char const * input[]) {

   for(int i = 1; i < 4; ++i)  {

       int value = atoi(input[i]);

       if (value < 0 || value > 255) {
           return 0;
       }
   }

   return 1;
}

short validateHEXInput(char const * input) {

    if (strlen(input) != HEX_LEN) {
        return 0;
    }

    for(int i = 0; i < HEX_LEN; ++i) {
        if (!strchr(HEX_VALUES, toupper(input[i]))) {
            return 0;
        }
    }

    return 1;
}

void RGBtoHEX(char const * input[], char *output) {

    for(int i = 0; i < 3; ++i) {

        const float inputColor = atof(input[i]);

        float division = inputColor / 16.;

        int whole = (int)division;
        int coef = (division - whole) * 16;

        output[i * 2] = HEX_VALUES[whole];
        output[i * 2 + 1] = HEX_VALUES[coef];
    }
}

void HEXtoRGB(char const * input, int *output) {

    for(int i = 0; i < 3; ++i) {

        char leading = input[i * 2];
        char trailing = input[i * 2 + 1];

        int leadingIndex = (int)(strchr(HEX_VALUES, leading) - HEX_VALUES);
        int trailingIndex = (int)(strchr(HEX_VALUES, trailing) - HEX_VALUES);

        output[i] = leadingIndex * 16 + trailingIndex;
    }
}

void printRGB(int const * input) {

    printf("R: %d, G: %d, B:%d\n", input[0], input[1], input[2]);
}

void printHEX(char const * input) {

    printf("HEX: #");

    for(int i = 0; i < 6; ++i) {
        printf("%c", input[i]);
    }

    printf("\n");
}

void charArrToIntArr(char const * input[], int* output, int len) {

    for(int i = 0; i < len; ++i) {
        output[i] = atoi(input[i]);
    }
}

void stringToCharArr(char const * input, char *output, int len) {

    for(int i = 0; i < len; ++i) {
        output[i] = toupper(input[i]);
    }
}

int main(int argc, char *argv[]) {

    int rgbValues[3];
    char hexOutput[HEX_LEN];

    switch (argc - 1) {
        case 1:

            if (!validateHEXInput(argv[1])) {

                perror("HEX input invalid");

                return 1;
            }

            stringToCharArr(argv[1], hexOutput, HEX_LEN);

            HEXtoRGB(hexOutput, rgbValues);

            break;
        case 3:

            if (!validateRGBInput(argv)) {

                perror("RGB input invalid");

                return 1;
            }

            char *input[3] = {argv[1], argv[2], argv[3]};

            charArrToIntArr(input, rgbValues, 3);

            RGBtoHEX(input, hexOutput);

            break;
        default:

            perror("Invalid input. Valid inputs: eg. A24FA3 for HEX to RGB or 123 33 75 for RGB to HEX");

            return 2;
    }

    printRGB(rgbValues);
    printHEX(hexOutput);

    return 0;
}

