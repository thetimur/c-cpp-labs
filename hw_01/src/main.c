#include "bmp.h"

int main(int argc, char** argv) {
    assert(argc == 8);

    //We <3 constants
    const char* input_filename = argv[2];
    const char* output_filename = argv[3];
    const int X = atoi(argv[4]);
    const int Y = atoi(argv[5]);
    const int W = atoi(argv[6]);
    const int H = atoi(argv[7]);

    BMP_t image;

    FILE* in = fopen(input_filename, "rb");
    FILE* out = fopen(output_filename, "wb");

    if (in == NULL || out == NULL) {
        printf("File %s not found!\n", input_filename);
        return -1;
    }

    if (load_bmp(in, &image)) {
        printf("Memory allocation error!\n");
        free(image.data);
        return -1;    
    }

    if (X < 0 || W <= 0 || X + W > image.DIB.width) {
        free(image.data);
        printf("(W=%d) should be > 0 or (X=%d) + (W=%d) is out of range\n", W, X, W);
        return -1;
    }
    if (Y < 0 || H <= 0 || Y + H > image.DIB.height) {
        printf("(H=%d) should be > 0 or (Y=%d) + (H=%d) is out of range\n", H, Y, H);
        free(image.data);
        return -1;
    }

    int status = 0;
    BMP_t result = crop(&image, &status, X, Y, W, H);

    if (status) {
        printf("Memory allocation error!\n");
        free(result.data);
        return -1;
    }

    result = rotate(&result, &status);

    if (status) {
        printf("Memory allocation error!\n");
        free(result.data);
        return -1;
    }

    if (save_bmp(out, &result)) {
        printf("Memory allocation error!\n");
        free(image.data);
        return -1;   
    }

    free(result.data);

    return 0;
}