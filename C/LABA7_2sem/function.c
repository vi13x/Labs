#include "function.h"
void set_color(int color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
}
void printMenu() {
    system("cls");
    set_color(COL_MENU);
    printf("╔════════════════════════════════════════════╗\n");
    printf("║           УПРАВЛЕНИЕ БИНАРНЫМ ДЕРЕВОМ      ║\n");
    printf("╠════════════════════════════════════════════╣\n");
    printf("║ 1. Создать новое дерево                    ║\n");
    printf("║ 2. Добавить узлы в дерево                  ║\n");
    printf("║ 3. Удалить узел из дерева                  ║\n");
    printf("║ 4. Найти несбалансированные узлы           ║\n");
    printf("║ 5. Визуализировать дерево                  ║\n");
    printf("║ 6. Выход из программы                      ║\n");
    printf("╚════════════════════════════════════════════╝");
    set_color(COL_RESET);
    printf("\n \033[1;32m>\033[0m Выберите действие: ");

}

void printAddMenu() {
    set_color(COL_MENU);
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║        ДОБАВЛЕНИЕ НОВЫХ УЗЛОВ              ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    set_color(COL_RESET);
}

void printDeleteMenu() {
    set_color(COL_MENU);
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║           УДАЛЕНИЕ УЗЛА                    ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    set_color(COL_RESET);
}

void printTreeHeader() {
    set_color(COL_MENU);
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║         ВИЗУАЛИЗАЦИЯ ДЕРЕВА                ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    set_color(COL_RESET);
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

Node* minValueNode(Node* node) {
    while (node && node->left != NULL)
        node = node->left;
    return node;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int height(Node* node) {
    if (node == NULL) return 0;
    int leftH = height(node->left);
    int rightH = height(node->right);
    return (leftH > rightH ? leftH : rightH) + 1;
}

void findUnbalancedNodes(Node* root) {
    if (root == NULL) return;
    int leftH = height(root->left);
    int rightH = height(root->right);
    if (leftH != rightH)
        printf("%d ", root->data);
    findUnbalancedNodes(root->left);
    findUnbalancedNodes(root->right);
}

void printTree(Node* root, int space) {
    if (root == NULL) return;
    space += 5;
    printTree(root->right, space);
    printf("\n");
    for (int i = 5; i < space; i++) printf(" ");
    printf("%d\n", root->data);
    printTree(root->left, space);
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int readInt(int *value) {
    char input[50];
    if (fgets(input, sizeof(input), stdin) == NULL) return 0;
    char *endptr;
    *value = strtol(input, &endptr, 10);
    while (*endptr != '\0' && isspace(*endptr)) endptr++;
    return *endptr == '\0' ? 1 : 0;
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addNodes(Node** root) {
    int value;
    printf("Вводите числа (0 для выхода):\n");
    while (1) {
        printf("> ");
        if (!readInt(&value)) {
            printf("Ошибка! Повторите ввод.\n");
            clearBuffer();
            continue;
        }
        if (value == 0) break;
        *root = insert(*root, value);
    }
}
void createNewTree(Node** root) {
    set_color(COL_MENU);
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║        СОЗДАНИЕ НОВОГО ДЕРЕВА              ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    set_color(COL_RESET);

    int value;
    while(1) {
        printf("Введите значение корня: ");
        if(readInt(&value)) {
            *root = createNode(value);
            break;
        } else {
            set_color(COL_WARNING);
            printf("Ошибка! Введите целое число.\n");
            set_color(COL_RESET);
            clearBuffer();
        }
    }
}

void binaryTree(){
    Node* root = NULL;
    int choice, data;

    do {
        printMenu();

        if (!readInt(&choice)) {
            printf("Ошибка ввода!\n");
            clearBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                freeTree(root);
                createNewTree(&root);
                break;

            case 2:
                printAddMenu();
                addNodes(&root);
                break;

            case 3:
                if (!root) {
                    set_color(COL_WARNING);
                    printf("\n╔════════════════════════════════════════════╗\n");
                    printf("║          ДЕРЕВО ПУСТОЕ!                    ║\n");
                    printf("╚════════════════════════════════════════════╝\n");
                    set_color(COL_RESET);
                    Sleep(1500);
                    break;
                }
                printDeleteMenu();
                printf("Введите значение для удаления: ");
                if (!readInt(&data)) {
                    printf("Ошибка ввода!\n");
                    clearBuffer();
                    break;
                }
                root = deleteNode(root, data);
                break;

            case 4:
                if (!root) {
                    set_color(COL_WARNING);
                    printf("\n╔════════════════════════════════════════════╗\n");
                    printf("║          ДЕРЕВО ПУСТОЕ!                    ║\n");
                    printf("╚════════════════════════════════════════════╝\n");
                    set_color(COL_RESET);
                    Sleep(1500);
                    break;
                }
                set_color(COL_MENU);
                printf("\n╔════════════════════════════════════════════╗\n");
                printf("║      НЕСБАЛАНСИРОВАННЫЕ УЗЛЫ:              ║\n");
                printf("╠════════════════════════════════════════════╣\n");
                printf("║ ");
                findUnbalancedNodes(root);
                printf("\n╚════════════════════════════════════════════╝\n");
                set_color(COL_RESET);
                Sleep(3000);
                break;

            case 5:
                printTreeHeader();
                printf("\n");
                printTree(root, 0);
                printf("\nНажмите Enter для продолжения...");
                clearBuffer();
                getchar();
                break;

            case 6:
                freeTree(root);
                set_color(COL_MENU);
                printf("\n╔════════════════════════════════════════════╗\n");
                printf("║    ПРОГРАММА УСПЕШНО ЗАВЕРШЕНА!            ║\n");
                printf("╚════════════════════════════════════════════╝\n");
                set_color(COL_RESET);
                return ;

            default:
                set_color(COL_WARNING);
                printf("\n╔════════════════════════════════════════════╗\n");
                printf("║      НЕКОРРЕКТНЫЙ ВЫБОР! ПОВТОРИТЕ!        ║\n");
                printf("╚════════════════════════════════════════════╝\n");
                set_color(COL_RESET);
                Sleep(1500);
        }
    } while (1);
}