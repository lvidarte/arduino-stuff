#include <stdio.h>

int main(int argc, char **argv) {
    char s[] = "s,-20,1000s,50,-123";
    char *p = s;
    char c;
    int sig = 1;
    int n = -1;
    int last;
    while (*p != '\0') {

        if (*p == 's') {
            p++;
            while (*p != 's' && *p != '\0') {
                switch (*p) {
                    case ',':
                        if (n != -1) {
                            printf("%d\n", n * sig);
                        }
                        n = 0;
                        last = 0;
                        sig = 1;
                        break;
                    case '-':
                        sig = -1;
                        break;
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        c = *p - '0';
                        n = (last * 10) + c;
                        last = c;
                        break;
                }
                p++;
            }
        }

    }
    return 0;
}
