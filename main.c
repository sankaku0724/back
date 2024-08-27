/*
  *   コマンドラインから与えられた文字列を逆順にして出力するプログラム back
  *   使い方： ./back [オプション]［文字列］
  *   例： ./back -h hellO   worlD
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>

// ヘルプメッセージを表示する関数
void print_help(char *prog_name) {
    printf("Usage: %s [-h] [-l] [-s] \"string\"\n", prog_name);
    printf("Options:\n");
    printf("  -h    Show this help message\n");
    printf("  -l    Convert the string to uppercase and reverse it\n");
    printf("  -s    Convert the string to lowercase and reverse it\n");
}

// 文字列を逆順にする関数
void reverseString(char *str) {
    int length = strlen(str);  // 文字列の長さを取得
    for (int i = 0; i < length / 2; i++) {
        // 文字列の先頭と末尾の文字を交換
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

// 文字列を全て大文字に変換する関数
void toUpperCase(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);  // 現在の文字を大文字に変換
        str++;
    }
}

// 文字列を全て小文字に変換する関数
void toLowerCase(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);  // 現在の文字を小文字に変換
        str++;
    }
}

int main(int argc, char *argv[]) {
    int opt;  // getopt関数からのオプションを格納
    int lflag = 0, sflag = 0, hflag = 0;  // 各オプションのフラグを初期化
    
    // コマンドライン引数を解析
    while ((opt = getopt(argc, argv, "hls")) != -1) {
        switch (opt) {
            case 'h':  // ヘルプオプション
                hflag = 1;
                break;
            case 'l':  // 大文字変換オプション
                lflag = 1;
                break;
            case 's':  // 小文字変換オプション
                sflag = 1;
                break;
            default:  // 存在しないオプション
                print_help(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // ヘルプフラグが立っている場合はヘルプを表示して終了
    if (hflag) {
        print_help(argv[0]);
        exit(EXIT_SUCCESS);
    }

    // オプションの後に文字列が渡されていない場合はエラーを表示
    if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    // 残りの引数を一つの文字列に連結
    int inputLength = 0;
    for (int i = optind; i < argc; i++) {
        inputLength += strlen(argv[i]) + 1;  // 空白や終端文字の分を追加
    }

    // 入力文字列のためのメモリを動的に割り当て
    char *inputString = (char *)malloc(inputLength * sizeof(char));
    inputString[0] = '\0';  // 空文字で初期化

    // 引数を連結して一つの文字列にする
    for (int i = optind; i < argc; i++) {
        strcat(inputString, argv[i]);
        if (i < argc - 1) {
            strcat(inputString, " ");
        }
    }

    // 入力文字列のコピーを作成
    char *resultString = strdup(inputString);

    // フラグに応じて文字列を大文字または小文字に変換
    if (lflag) {
        toUpperCase(resultString);
    } else if (sflag) {
        toLowerCase(resultString);
    }

    // 文字列を逆順にする
    reverseString(resultString);

    // 結果を出力
    printf("%s\n", resultString);
    
    // 動的に割り当てたメモリを解放
    free(resultString);
    free(inputString);
    return 0;
}
